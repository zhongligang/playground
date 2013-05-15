/*
ID: baikaiz1
PROG: agrinet
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file agrinet.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

#define INFINITY 0x7FFFFFFF

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("agrinet.in", "r");
    fout = fopen("agrinet.out", "w");
    int npoints, i, j, p, m;
    int matrix[100][100] = {0};
    int d[100] = {0};
    int visited[100] = {0};
    int cost = 0;

    fscanf(fin, "%d", &npoints);
    for (i = 0; i < npoints; i++) {
        for (j = 0; j < npoints; j++) {
            fscanf(fin, "%d", &matrix[i][j]);
        }
        d[i] = INFINITY;
    }

    visited[0] = 1;
    d[0] = 0;
    for (j = 1; j < npoints; j++) {
        if (matrix[0][j] > 0) {
            d[j] = matrix[0][j];
        }
    }

    i = npoints-1;
    while (i--) {
        m = INFINITY;
        for (j = 1; j < npoints; j++) {
            if (!visited[j] && d[j] < m) {
                m = d[j];
                p = j;
            }
        }

        visited[p] = 1;
        cost += d[p];

        for (j = 1; j < npoints; j++) {
            if (!visited[j] && d[j] > matrix[j][p] && matrix[j][p] > 0) {
                d[j] = matrix[j][p];
            }
        }
    }

    fprintf(fout, "%d\n", cost);

    return 0;
}

