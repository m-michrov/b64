#pragma once

#ifndef B64_BASE64_H
#define B64_BASE64_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>

unsigned char * base64_encode(
        unsigned const char * input_string,
        unsigned int input_length);

unsigned char * base64_encode_with_separators(
        unsigned const char * input_string,
        unsigned int input_length,
        unsigned long long * encoded_counter,
        unsigned int separate);

unsigned char * base64_decode(
        unsigned const char * input_string,
        unsigned int input_length,
        const int * decode_table);

int * base64_makeDecodeTable();

void encode(
        int argc,
        char * argv[]);

void decode(
        const char * in,
        const char * out);

void decode_ignore_non_base64(
        const char *in,
        const char *out);

#endif
