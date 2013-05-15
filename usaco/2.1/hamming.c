/*
ID: baikaiz1
PROG: hamming
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file hamming.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

#define MAX_CODE_NEEDED 64

unsigned char codes[MAX_CODE_NEEDED] = {0};
int code_max_v;
int hamming_distance;
int code_needed;
int code_found = 0;

int hamming(unsigned char a, unsigned char b) {
    unsigned char c = a ^ b;

    c = (c & 0x55) + ((c & 0xAA) >> 1);
    c = (c & 0x33) + ((c & 0xCC) >> 2);
    c = (c & 0x0F) + ((c & 0xF0) >> 4);

    return c;
}

void dfs(int start) {
    int i = 0;
    int cur_num = start;
    int cur_max = code_max_v - (code_needed - code_found) + 1;

    while (cur_num < cur_max) {
        for (i = 0; i < code_found; i++) {
            if (hamming(codes[i], cur_num) < hamming_distance) {
                break;
            }
        }

        // satisfy
        if (i == code_found) {
            codes[code_found] = cur_num;
            code_found++;
            if (code_found == code_needed) {
                return;
            } else {
                dfs(cur_num+1);
                if (code_found == code_needed) {
                    return;
                } else {
                    code_found--;
                }
            }
        }

        cur_num++;
    }
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("hamming.in", "r");
    fout = fopen("hamming.out", "w");

    int bit_len;
    int i;

    fscanf(fin, "%d %d %d", &code_needed, &bit_len, &hamming_distance);

    code_max_v = 1 << bit_len;

    dfs(0);

    for (i = 0; i < code_needed - 1; i++) {
        fprintf(fout, "%d", codes[i]);
        if (i % 10 == 9) {
            fprintf(fout, "\n");
        } else {
            fprintf(fout, " ");
        }
    }

    fprintf(fout, "%d\n", codes[i]);

    return 0;
}

