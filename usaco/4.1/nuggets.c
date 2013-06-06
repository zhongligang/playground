/*
ID: baikaiz1
PROG: nuggets
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file nuggets.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

int gcd(int a, int b) {
    int tmp;

    if (a > b) {
        tmp = b;
        b = a;
        a = tmp;
    }

    if (a == 0) {
        return b;
    }

    return gcd(b % a, a);
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("nuggets.in", "r");
#ifdef DEBUG
    fout = stdout;
#else
    fout = fopen("nuggets.out", "w");
#endif

    int n_numbers;
    int numbers[10] = {0};
    int i, j;
    int check_max = 2000000000;
    int cgcd;
    int map[65537];

    fscanf(fin, "%d", &n_numbers);
    for (i = 0; i < n_numbers; i++) {
        fscanf(fin, "%d", numbers+i);
        if (numbers[i] == 1) {
            fprintf(fout, "0\n");
            return 0;
        }

        if (i == 0) {
            cgcd = numbers[0];
        } else {
            cgcd = gcd(cgcd, numbers[i]);
        }

        map[numbers[i]] = 1;
    }

    if (cgcd != 1) {
        fprintf(fout, "0\n");
        return 0;
    }

    for (i = 0; i < 65537; i++) {
        for (j = 0; j < n_numbers; j++) {
            if (i - numbers[j] >= 0 && map[i - numbers[j]]) {
                map[i] = 1;
                break;
            }
        }
    }

    for (i = 65536; i; i--) {
        if (!map[i]) {
            fprintf(fout, "%d\n", i);
            return 0;
        }
    }

    return 0;
}

