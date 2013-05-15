/*
ID: baikaiz1
PROG: prefix
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file prefix.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("prefix.in", "r");
    fout = fopen("prefix.out", "w");

    char primitives[201][11];
    char s[200001];
    char reached[200001] = {0};
    int num_primitives;
    int num_chars;
    int i, j, k;

    num_primitives = 0;
    while (fscanf(fin, "%s", primitives[num_primitives]) == 1) {
        if (primitives[num_primitives][0] == '.') {
            break;
        }
        num_primitives++;
    }

    num_chars = 0;
    while (fscanf(fin, "%s", s+num_chars) != EOF) {
        num_chars += strlen(s+num_chars);
    }

    reached[0] = 1;
    for (i = 0; i < num_chars; i++) {
        if (reached[i]) {
            for (j = 0; j < num_primitives; j++) {
                k = 0;
                while (primitives[j][k] == s[i+k] && i+k<num_chars) {
                    k++;
                }

                if (!primitives[j][k]) {
                    reached[i+k] = 1;
                }
            }
        }
    }

    num_chars += 1;
    while (reached[--num_chars] == 0) {
    }

    fprintf(fout, "%d\n", num_chars);

    return 0;
}

