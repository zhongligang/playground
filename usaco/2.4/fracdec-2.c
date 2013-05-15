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

#define PRINT(d, j) \
    j += fprintf(fout, "%d", d);\
    if (j == 76) {\
        fprintf(fout, "\n");\
        j = 0;\
    }

int numBeforeRepeat(int n, int d) {
    int c2 = 0, c5 = 0;
    while (d%2==0) {d/=2;c2++;}
    while (d%5==0) {d/=5;c5++;}
    while (n%2==0) {n/=2;c2--;}
    while (n%5==0) {n/=5;c5--;}

    if (c2 > c5) {
        return c2 > 0 ? c2 : 0;
    } else {
        return c5 > 0 ? c5 : 0;
    }
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("fracdec.in", "r");
    fout = fopen("fracdec.out", "w");
    int r;
    int n, d;
    int i, j;
    int m;

    fscanf(fin, "%d %d", &n, &d);

    if (n % d == 0) {
        fprintf(fout, "%d.0\n", n/d);

        return 0;
    }

    j = 0;
    PRINT(n/d, j);
    n %= d;
    j += fprintf(fout, ".");

    m = numBeforeRepeat(n, d);
    while (m--) {
        n *= 10;
        PRINT(n/d, j);
        n %= d;
    }

    if (n != 0) {
        j += fprintf(fout, "(");
        if (j == 76) {
            fprintf(fout, "\n");
            j = 0;
        }

        r = n;
        do {
            n *= 10;
            PRINT(n/d, j);
            n %= d;
        } while (r != n);

        fprintf(fout, ")\n");
    } else {
        if (j != 0) {
            fprintf(fout, "\n");
        }
    }

    return 0;
}

