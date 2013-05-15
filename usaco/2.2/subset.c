/*
ID: baikaiz1
PROG: subset
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file subset.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

int subset(int max) {
    unsigned long int cache[781] = {0};
    int i, j, sum;

    sum = max*(max+1)/2;

    if (sum & 1) {
        return 0;
    }

    cache[0] = 1;
    for (i = 1; i <= max; i++) {
        sum = i*(i+1)/2;
        for (j = sum; j >= i; j--) {
            cache[j] += cache[j-i];
        }
    }

    return cache[max*(max+1)/4]/2;
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("subset.in", "r");
    fout = fopen("subset.out", "w");
    int n;
    int result;

    fscanf(fin, "%d", &n);

    result = subset(n);
    fprintf(fout, "%d\n", result);

    return 0;
}

