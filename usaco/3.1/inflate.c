/*
ID: baikaiz1
PROG: inflate
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file inflate.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("inflate.in", "r");
    fout = fopen("inflate.out", "w");
    int m, ncat;
    int cat_cost[10000];
    int cat_point[10000];
    int solution[10001] = {0};
    int i, j, k;

    fscanf(fin, "%d %d", &m, &ncat);
    for (i = 0; i < ncat; i++) {
        fscanf(fin, "%d %d", cat_point+i, cat_cost+i);
    }

    for (i = 0; i < ncat; i++) {
        k = cat_cost[i];
        for (j = k; j <= m; j++) {
            solution[j] = solution[j] > solution[j-k]+cat_point[i]
                ? solution[j]
                : solution[j-k]+cat_point[i];
        }
    }

    fprintf(fout, "%d\n", solution[m]);

    return 0;
}

