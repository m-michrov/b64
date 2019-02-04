#include "definitions.h"
#include "base64.h"

int main(int argc, char * argv[]) {
    if (argc < 3) CMD_ARGUMENTS_ERROR;

    if (!strcmp(argv[1], "-e"))
        encode(argc, argv);

    else if (!strcmp(argv[1], "-d"))
        switch (!strcmp(argv[2], "-i") ? 1 : 0) {
            case 1:
                decode_ignore_non_base64(argv[argc - 2], argv[argc - 1]);
                break;
            default:
                decode(argv[argc - 2], argv[argc - 1]);
        }

    else CMD_ARGUMENTS_ERROR;

    return 0;
}