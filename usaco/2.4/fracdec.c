/*
ID: baikaiz1
PROG: fracdec
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file fracdec.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("fracdec.in", "r");
    fout = fopen("fracdec.out", "w");
    int rs[100000] = {0};
    char result[200000];
    int idx;
    int r;
    int n, d;
    int i, j;

    fscanf(fin, "%d %d", &n, &d);

    if (n % d == 0) {
        fprintf(fout, "%d.0\n", n/d);

        return 0;
    }

    idx = 0;
    if (n < d) {
        result[idx++] = '0';
    } else {
        idx += snprintf(result, 10000, "%d", n/d);
        n %= d;
    }
    result[idx++] = '.';

    while (1) {
        rs[n] = idx;
        n *= 10;
        if (n < d) {
            result[idx++] = '0';
        } else {
            result[idx++] = n / d + '0';
            n %= d;
            if (n == 0) {
                break;
            }
        }

        if (rs[n] > 0) {
            break;
        }
    }

    for (i = 0, j = 0; i < idx; i++) {
        if (n != 0 && rs[n] == i) {
            fprintf(fout, "(");
            j++;
            if (j == 76) {
                fprintf(fout, "\n");
                j = 0;
            }
        }

        fprintf(fout, "%c", result[i]);
        j++;
        if (j == 76) {
            fprintf(fout, "\n");
            j = 0;
        }
    }

    if (n != 0) {
        fprintf(fout, ")\n");
    } else if (j != 0) {
        fprintf(fout, "\n");
    }

    return 0;
}

