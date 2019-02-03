#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>

#define BLOCK_SIZE 1020

#define BASE64_ERROR {puts("Error: source file is not Base64-encoded"); exit(EXIT_SUCCESS);};
#define SOURCE_FILE_ERROR {puts("Error: cannot access source file"); exit(EXIT_SUCCESS);};
#define MEM_ERROR {puts("Error: unable to allocate memory"); exit(EXIT_SUCCESS);};
#define TARGET_FILE_ERROR {puts("Error: cannot access target file"); exit(EXIT_SUCCESS);};
#define CMD_ARGUMENTS_ERROR {puts("Error: invalid combination of parameters. Usage:\nNAME\n\tb64 - Base64-encode/decode files\nSYNOPSIS\n\tb64 {-e|-d} [-i] [-f N] <sourcefilename> <targetfilename>\nDESCRIPTION\n\tEncode/decode SOURCEFILENAME to TARGETFILENAME\n\n\tOptions:\n\t\t-e\tencode\n\t\t-d\tdecode\n\t\t-i\tignore non-Base64 symbols (decode-only)\n\t\t-f N\tinsert newline every N symbols (encode-only)"); exit(EXIT_SUCCESS);};

unsigned char * base64_encode(
        unsigned const char * input_string,
        unsigned const int input_length,
        unsigned long long * encoded_counter,
        unsigned const int separate)
{
    unsigned char * output_string = (unsigned char *)malloc(4 * (input_length + 2) / 3 + 1 + (separate ? input_length / separate : 0));

    if (output_string == NULL)
    MEM_ERROR;

    //printf("%d %d\n", input_length,  4 * (input_length + 2) / 3 + 1 + input_length / (separate ? separate : input_length + 1));

    static unsigned const char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    static unsigned const int rest_table[] = {0, 2, 1};

    int triple = 0,
            j = 0,
            r = 0;

    for (int i = 0; i < input_length; triple = 0) {
        for (int k = 2; k >= 0; k--) {
            triple += (i < input_length ? input_string[i++] : (unsigned char) 0 & r++) << 8 * k;
        }
        for (int k = 3; k >= r; k--) {
            output_string[j++] = alpha[(triple >> k * 6) & 0x3F];

            (* encoded_counter)++;

            if (separate && * encoded_counter % separate == 0)
                output_string[j++] = '\n';
        }
    }

    for (int i = 0; i < rest_table[input_length % 3]; i++) {
        output_string[j++] = '=';

        (* encoded_counter)++;

        if (separate && * encoded_counter % separate == 0)
            output_string[j++] = '\n';
    }

    output_string[j] = '\0';

    return output_string;
}

unsigned char * base64_decode(
        unsigned const char * input_string,
        unsigned const int input_length,
        const int * decode_table)
{
    unsigned char * output_string = (unsigned char *)malloc(input_length / 4 * 3 + 1);

    if (output_string == NULL)
    MEM_ERROR;

    int quad = 0,
        num = 0;

    unsigned int j = 0,
                 non_Base64_count = 0;

    for (int i = 0; i < input_length; ) {
        quad = 0;

        for (int k = 3; k >= 0 && i < input_length; k--) {
            num = input_string[i] == '=' ? 0 & i++ : decode_table[(unsigned int)input_string[i++]];
            if (num < 0) {
                printf("\n%c %d\n", input_string[i - 1], input_string[i - 1]);
                BASE64_ERROR;
            }
            quad += (num << (k * 6));
        }

        for (int k = 2; k >= 0 && j < (input_length - non_Base64_count) / 4 * 3; k--)
            output_string[j++] = (unsigned char) ((quad >> 8 * k) & 0xFF);
    }

    output_string[j] = '\0';

    return output_string;
}

int * base64_makeDecodeTable()
{
    int * decode_table = malloc(sizeof(int) * 128);

    static unsigned const char encode_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    for (int i = 0; i < 128; i++)
        decode_table[i] = -1;

    for (int k = 0; k < 64; k++)
        decode_table[(unsigned int)encode_table[k]] = k;

    decode_table['='] = 0;

    return decode_table;
}

int main(int argc, char * argv[]) {
    if (argc < 3)
    CMD_ARGUMENTS_ERROR;

    FILE * source,
         * target;

    unsigned char input_buff[BLOCK_SIZE],
                  * output_buff;
    unsigned int len = 0;

    if (!strcmp(argv[1], "-e")) {
        if (argc != 4 && argc != 6)
        CMD_ARGUMENTS_ERROR;

        long int separate = 0;
        unsigned long long int encoded_counter = 0;
        char * endptr;

        if (argc == 6) {
            separate = strtol(argv[3], &endptr, 10);

            if (*endptr != '\0') CMD_ARGUMENTS_ERROR;
        }

        source = fopen(argv[argc - 2], "rb");
        target = fopen(argv[argc - 1], "wb");
        fclose(target);
        target = fopen(argv[argc - 1], "ab");

        if (source == NULL)
        SOURCE_FILE_ERROR;
        if (target == NULL)
        TARGET_FILE_ERROR;

        clock_t start = clock();

        while ((len = fread(input_buff, 1, BLOCK_SIZE, source))) {
            output_buff = base64_encode(input_buff, len, &encoded_counter, (unsigned int)separate);

            fwrite(output_buff, 1, strlen((char *)output_buff), target);
            free(output_buff);
        }

        clock_t end = clock();

        printf("Successfully encoded %s to %s in %.2lf s", argv[argc - 2], argv[argc - 1], (double)(end - start) / 1000);
    }
    else if (!strcmp(argv[1], "-d")) {
        int char_buff = 0;
        unsigned int read_count = 0;

        source = fopen(argv[argc - 2], "rb");
        target = fopen(argv[argc - 1], "wb");
        fclose(target);
        target = fopen(argv[argc - 1], "ab");

        if (source == NULL) SOURCE_FILE_ERROR;
        if (target == NULL) TARGET_FILE_ERROR;

        int * decode_table = base64_makeDecodeTable();

        clock_t start;

        switch (!strcmp(argv[2], "-i") ? 1 : 0) {
            case 1:
                start = clock();

                while (char_buff != EOF) {
                    while (read_count < BLOCK_SIZE && (char_buff = fgetc(source)) != EOF)
                        if (decode_table[char_buff] >= 0)
                            input_buff[read_count++] = (unsigned char) char_buff;

                    if (!(read_count % 4)) {
                        output_buff = base64_decode(input_buff, read_count, decode_table);

                        fwrite(output_buff, 1, read_count / 4 * 3, target);
                        free(output_buff);

                        read_count = 0;
                    } else
                        BASE64_ERROR;
                }
                break;

            default:
                start = clock();

                while ((len = fread(input_buff, 1, BLOCK_SIZE, source))) {
                    output_buff = base64_decode(input_buff, len, decode_table);

                    fwrite(output_buff, 1, len / 4 * 3, target);
                    free(output_buff);
                }
                break;
        }

        clock_t end = clock();

        printf("Successfully decoded %s to %s in %.2lf s", argv[argc - 2], argv[argc - 1], (double)(end - start) / 1000);

    }
    else
    CMD_ARGUMENTS_ERROR;

    return 0;
}