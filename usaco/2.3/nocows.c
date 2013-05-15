/*
ID: baikaiz1
PROG: nocows
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file nocows.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("nocows.in", "r");
    fout = fopen("nocows.out", "w");
    int nodes, height;
    // number of trees with 200 nodes not higher than 100
    int results[200][100] = {0};
    int n, h, i;
    int maxh;

    fscanf(fin, "%d %d", &nodes, &height);

    for (i = 1; i <= height; i++) {
        results[1][i] = 1;
    }

    for (n = 3; n <= nodes; n+=2) {
        maxh = (n+1)/2;
        if (maxh > height) {
            maxh = height;
        }
        for (h = 2; h <= maxh; h++) {
            for (i = 1; i <= n-2; i+=2) {
                results[n][h] += results[n-i-1][h-1]*results[i][h-1];
                if (results[n][h] > 9901) {
                    results[n][h] %= 9901;
                }
            }
        }

        for (i = maxh+1; i <= height; i++) {
            results[n][i] = results[n][maxh];
        }
    }

    fprintf(fout, "%d\n", (results[nodes][height]+9901-results[nodes][height-1])%9901);

    return 0;
}

