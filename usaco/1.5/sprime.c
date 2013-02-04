/*
ID: baikaiz1
PROG: sprime
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file sprime.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

FILE *fin, *fout;
int maxlen;

int is_prime(int num) {
    int i, j;

    j = (int)sqrt(num) + 1;
    for (i = 2; i < j; i++) {
        if (num % i == 0) {
            return 0;
        }
    }

    return 1;
}

void dfs(int base, int len) {
    int i, val;

    if (len == 0) {
        if (is_prime(base)) {
            fprintf(fout, "%d\n", base);
        }
    } else if (len == 1) {
        val = base * 10;
        if (is_prime(val + 1)) {
            fprintf(fout, "%d\n", val + 1);
        }
        if (is_prime(val + 3)) {
            fprintf(fout, "%d\n", val + 3);
        }
        if (is_prime(val + 7)) {
            fprintf(fout, "%d\n", val + 7);
        }
        if (is_prime(val + 9)) {
            fprintf(fout, "%d\n", val + 9);
        }
    } else {
        val = base * 10;
        if (is_prime(val + 1)) {
            dfs(val + 1, len - 1);
        }
        if (is_prime(val + 3)) {
            dfs(val + 3, len - 1);
        }
        if (is_prime(val + 7)) {
            dfs(val + 7, len - 1);
        }
        if (is_prime(val + 9)) {
            dfs(val + 9, len - 1);
        }
    }
}

int main(int argc, char** argv) {
    fin = fopen("sprime.in", "r");
    fout = fopen("sprime.out", "w");

    fscanf(fin, "%d", &maxlen);

    dfs(2, maxlen - 1);
    dfs(3, maxlen - 1);
    dfs(5, maxlen - 1);
    dfs(7, maxlen - 1);

    return 0;
}

