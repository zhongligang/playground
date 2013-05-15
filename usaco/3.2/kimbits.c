/*
ID: baikaiz1
PROG: kimbits
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file kimbits.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("kimbits.in", "r");
    fout = fopen("kimbits.out", "w");
    int n_bits, n_1s;
    int n_bit, n_1;
    unsigned int nth;
    unsigned int f[32][32] = {0};

    fscanf(fin, "%d %d %u", &n_bits, &n_1s, &nth);

    for (n_1 = 0; n_1 <= n_1s; n_1++) {
        f[0][n_1] = 1;
    }

    for (n_bit = 1; n_bit <= n_bits; n_bit++) {
        f[n_bit][0] = 1;
        for (n_1 = 1; n_1 <= n_1s; n_1++) {
            f[n_bit][n_1] = f[n_bit-1][n_1-1] + f[n_bit-1][n_1];
        }
    }

    while (n_bits--) {
        if (nth > f[n_bits][n_1s]) {
            nth -= f[n_bits][n_1s];
            n_1s--;
            fprintf(fout, "1");
        } else {
            fprintf(fout, "0");
        }
    }

    fprintf(fout, "\n");

    return 0;
}

