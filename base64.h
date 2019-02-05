#pragma once

#ifndef B64_BASE64_H
#define B64_BASE64_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <time.h>

void base64_encode(
        unsigned const char * input_string,
        unsigned char * output_string,
        unsigned int input_length);

void base64_encode_with_separators(
        unsigned const char * input_string,
        unsigned char * output_string,
        unsigned int input_length,
        unsigned long long * encoded_counter,
        unsigned int separate);

static unsigned char * base64_decode(
        unsigned const char * input_string,
        unsigned int input_length,
        const int * decode_table);

static unsigned char * base64_decode_ignore_non_base64(
        unsigned const char * input_string,
        unsigned int input_length,
        const int * decode_table);

static int * base64_makeDecodeTable();

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
