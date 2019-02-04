#pragma once

#ifndef B64_DEFINITIONS_H
#define B64_DEFINITIONS_H

#define BLOCK_SIZE 4092

#define BASE64_ERROR {puts("Error: input file is not Base64-encoded"); exit(EXIT_SUCCESS);};
#define SOURCE_FILE_ERROR {puts("Error: cannot access input file"); exit(EXIT_SUCCESS);};
#define MEM_ERROR {puts("Error: unable to allocate memory"); exit(EXIT_SUCCESS);};
#define TARGET_FILE_ERROR {puts("Error: cannot access output file"); exit(EXIT_SUCCESS);};
#define CMD_ARGUMENTS_ERROR {puts("Error: invalid combination of parameters. Usage:\nNAME\n\tb64 - Base64-encode/decode files\nSYNOPSIS\n\tb64 {-e|-d} [-i] [-f N] <inputfilename> <outputfilename>\nDESCRIPTION\n\tEncode/decode INPUTFILENAME to TARGETFILENAME\n\n\tOptions:\n\t\t-e\tencode\n\t\t-d\tdecode\n\t\t-i\tignore non-Base64 symbols (decode-only)\n\t\t-f N\tinsert newline every N symbols (encode-only)"); exit(EXIT_SUCCESS);};

#endif
