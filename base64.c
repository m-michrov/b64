#include "definitions.h"
#include "base64.h"

static unsigned char * base64_encode_with_separators(
        unsigned const char * input_string,
        unsigned const int input_length,
        unsigned long long * encoded_counter,
        unsigned const int separate)
{
    if (!separate) ACCESS_ERROR;

    unsigned char * output_string = (unsigned char *)malloc(4 * (input_length + 2) / 3 + 4 * (input_length + 2) / 3 / separate + 1);

    if (output_string == NULL) MEM_ERROR;

    static unsigned const char encoding_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    static unsigned const int rest_table[] = {0, 2, 1};

    int triple = 0,
        index = 0,
        rest = 0;

    for (int i = 0; i < input_length; triple = 0) {
        for (int k = 2; k >= 0; k--)
            triple += (i < input_length ? input_string[i++] : (unsigned char) 0 & rest++) << 8 * k;

        for (int k = 3; k >= rest; k--) {
            output_string[index++] = encoding_table[(triple >> k * 6) & 0x3F];

            if (++(* encoded_counter) % separate == 0)
                output_string[index++] = '\n';
        }
    }

    for (int i = 0; i < rest_table[input_length % 3]; i++) {
        output_string[index++] = '=';

        if (++(* encoded_counter) % separate == 0)
            output_string[index++] = '\n';
    }

    output_string[index] = '\0';

    return output_string;
}

static unsigned char * base64_encode(
        unsigned const char * input_string,
        unsigned int input_length)
{
    static unsigned char output_string[BLOCK_SIZE + 1];

    static unsigned const char encoding_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    int triple = 0,
        index = 0,
        i = 0;

    for (i = 0; i < input_length - input_length % 3; triple = 0) {
        triple += input_string[i++] << 16;
        triple += input_string[i++] << 8;
        triple += input_string[i++];

        output_string[index++] = encoding_table[(triple >> 18) & 0x3F];
        output_string[index++] = encoding_table[(triple >> 12) & 0x3F];
        output_string[index++] = encoding_table[(triple >> 6) & 0x3F];
        output_string[index++] = encoding_table[(triple) & 0x3F];
    }

    triple = 0;

    switch (input_length % 3) {
        case 2:
            triple += input_string[i++] << 16;
            triple += input_string[i] << 8;

            output_string[index++] = encoding_table[(triple >> 18) & 0x3F];
            output_string[index++] = encoding_table[(triple >> 12) & 0x3F];
            output_string[index++] = encoding_table[(triple >> 6) & 0x3F];
            output_string[index++] = '=';
            break;
        case 1:
            triple += input_string[i] << 16;

            output_string[index++] = encoding_table[(triple >> 18) & 0x3F];
            output_string[index++] = encoding_table[(triple >> 12) & 0x3F];
            output_string[index++] = '=';
            output_string[index++] = '=';
            break;
        default:
            ;
    }

    output_string[index] = '\0';

    return output_string;
}

static unsigned char * base64_decode_ignore_non_base64(
        unsigned const char * input_string,
        unsigned const int input_length,
        const int * decode_table)
{
    unsigned char * output_string = (unsigned char *)malloc(input_length / 4 * 3 + 1);

    if (output_string == NULL) MEM_ERROR;

    int quad = 0,
        num = 0,
        index = 0;

    for (int i = 0; i < input_length; quad = 0) {

        for (int k = 3; k >= 0 && i < input_length; k--) {
            num = input_string[i] == '=' ? 0 & i++ : decode_table[(unsigned int)input_string[i++]];

            if (num < 0) {
                k++;
                continue;
            }

            quad += (num << (k * 6));
        }

        for (int k = 2; k >= 0 && index < input_length / 4 * 3; k--)
            output_string[index++] = (unsigned char) ((quad >> 8 * k) & 0xFF);
    }

    output_string[index] = '\0';

    return output_string;
}

static unsigned char * base64_decode(
        unsigned const char * input_string,
        unsigned const int input_length,
        const int * decode_table)
{
    unsigned char * output_string = (unsigned char *)malloc(input_length / 4 * 3 + 1);

    if (output_string == NULL) MEM_ERROR;

    int quad = 0,
            num = 0,
            index = 0;

    for (int i = 0; i < input_length; quad = 0) {

        for (int k = 3; k >= 0 && i < input_length; k--) {
            num = input_string[i] == '=' ? 0 & i++ : decode_table[(unsigned int)input_string[i++]];

            if (num < 0) BASE64_ERROR;

            quad += (num << (k * 6));
        }

        for (int k = 2; k >= 0 && index < input_length / 4 * 3; k--)
            output_string[index++] = (unsigned char) ((quad >> 8 * k) & 0xFF);
    }

    output_string[index] = '\0';

    return output_string;
}

static int * base64_makeDecodeTable()
{
    int * decode_table = malloc(sizeof(int) * 128);

    unsigned const char encode_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    for (int i = 0; i < 128; i++)
        decode_table[i] = -1;

    for (int k = 0; k < 64; k++)
        decode_table[(unsigned int)encode_table[k]] = k;

    decode_table['='] = 0;

    return decode_table;
}

void encode(
        const int argc,
        char * argv[])
{
    FILE * input,
         * output;

    unsigned char input_buff[BLOCK_SIZE],
                * output_buff;
    unsigned int len = 0;
    unsigned long long int encoded_counter = 0;

    char * endptr;
    long int separate = 0;

    if (argc != 4 && argc != 6) CMD_ARGUMENTS_ERROR;

    if (argc == 6) {
        separate = strtol(argv[3], &endptr, 10);

        if (*endptr != '\0') CMD_ARGUMENTS_ERROR;
    }

    input = fopen(argv[argc - 2], "rb");
    output = fopen(argv[argc - 1], "wb");
    fclose(output);
    output = fopen(argv[argc - 1], "ab");

    if (input == NULL)
    SOURCE_FILE_ERROR;
    if (output == NULL)
    TARGET_FILE_ERROR;

    clock_t start = clock();

    switch (separate) {
        case 0:
            while ((len = fread(input_buff, 1, BLOCK_SIZE, input))) {
                output_buff = base64_encode(input_buff, len);

                fwrite(output_buff, 1, strlen((char *)output_buff), output);
            }
            break;
        default:
            while ((len = fread(input_buff, 1, BLOCK_SIZE, input))) {
                output_buff = base64_encode_with_separators(input_buff, len, &encoded_counter, (unsigned int)separate);

                fwrite(output_buff, 1, strlen((char *)output_buff), output);
                free(output_buff);
            }
    }

    clock_t end = clock();

    printf("Successfully encoded %s to %s in %.2lf s", argv[argc - 2], argv[argc - 1], (double)(end - start) / 1000);

    fclose(input);
    fclose(output);
};

void decode(
        const char * in,
        const char * out)
{

    FILE * input,
         * output;

    unsigned char input_buff[BLOCK_SIZE],
            * output_buff;

    unsigned int len = 0;

    int * decode_table = base64_makeDecodeTable();

    input = fopen(in, "rt");
    output = fopen(out, "wb");
    fclose(output);
    output = fopen(out, "ab");

    if (input == NULL) SOURCE_FILE_ERROR;
    if (output == NULL) TARGET_FILE_ERROR;

    clock_t start = clock();

    while ((len = fread(input_buff, 1, BLOCK_SIZE, input))) {
        output_buff = base64_decode(input_buff, len, decode_table);

        fwrite(output_buff, 1, len / 4 * 3, output);
        free(output_buff);
    }

    clock_t end = clock();

    printf("Successfully decoded %s to %s in %.2lf s", in, out, (double)(end - start) / 1000);

    fclose(input);
    fclose(output);
};


void decode_ignore_non_base64(
        const char *in,
        const char *out)
{
    FILE * input,
         * output;

    unsigned char input_buff[BLOCK_SIZE],
                * output_buff;

    int char_buff = 0;
    int * decode_table = base64_makeDecodeTable();
    unsigned int len = 0;

    unsigned int nonBase64 = 0;

    input = fopen(in, "rt");
    output = fopen(out, "wb");
    fclose(output);
    output = fopen(out, "ab");

    if (input == NULL) SOURCE_FILE_ERROR;
    if (output == NULL) TARGET_FILE_ERROR;

    clock_t start  = clock();

    for ( ; (len = fread(input_buff, 1, BLOCK_SIZE - 4, input)); nonBase64 = 0) {

        for (int k = 0; k < len; k++)
            nonBase64 += decode_table[input_buff[k]] < 0 ? 1 : 0;

        for (int d = 0; d < (len - nonBase64) % 4 && (char_buff = fgetc(input)) != EOF; d += decode_table[char_buff] < 0 ? 0 : 1 & len++)
            input_buff[len] = (unsigned char) char_buff;

        if (((len - nonBase64) % 4) && char_buff == EOF) BASE64_ERROR;

        output_buff = base64_decode_ignore_non_base64(input_buff, len, decode_table);

        fwrite(output_buff, 1, (len - nonBase64) / 4 * 3, output);
        free(output_buff);
    }

    clock_t end = clock();

    printf("Successfully decoded %s to %s in %.2lf s", in, out, (double)(end - start) / 1000);

    fclose(input);
    fclose(output);
};
