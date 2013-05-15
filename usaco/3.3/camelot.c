/*
ID: baikaiz1
PROG: camelot
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file camelot.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define MAXN 0x7FFFFFFF

int kdist[30][26];
int kcost[30][26];
int dist[30][26][2]; // tmp value for each knight, with or without king
int cost[30][26]; // sum value for all knights currently collocted;
int rows, cols;

int move_on(int row, int col, int has_king) {
    int f = 0, d = dist[row][col][has_king];

    if (row >= 2) {
        if (col >= 1 && dist[row-2][col-1][has_king] > d + 1) {
            dist[row-2][col-1][has_king] = d + 1;
            f = 1;
        }
        if (col < cols - 1 && dist[row-2][col+1][has_king] > d + 1) {
            dist[row-2][col+1][has_king] = d + 1;
            f = 1;
        }
    }

    if (row < rows - 2) {
        if (col >= 1 && dist[row+2][col-1][has_king] > d + 1) {
            dist[row+2][col-1][has_king] = d + 1;
            f = 1;
        }
        if (col < cols - 1 && dist[row+2][col+1][has_king] > d + 1) {
            dist[row+2][col+1][has_king] = d + 1;
            f = 1;
        }
    }

    if (col >= 2) {
        if (row >= 1 && dist[row-1][col-2][has_king] > d + 1) {
            dist[row-1][col-2][has_king] = d + 1;
            f = 1;
        }

        if (row < rows - 1 && dist[row+1][col-2][has_king] > d + 1) {
            dist[row+1][col-2][has_king] = d + 1;
            f = 1;
        }
    }

    if (col < cols - 2) {
        if (row >= 1 && dist[row-1][col+2][has_king] > d + 1) {
            dist[row-1][col+2][has_king] = d + 1;
            f = 1;
        }

        if (row < rows - 1 && dist[row+1][col+2][has_king] > d + 1) {
            dist[row+1][col+2][has_king] = d + 1;
            f = 1;
        }
    }

    return f;
}

void add_knight(int row, int col) {
    int i, j, maxd, d;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            dist[i][j][1] = dist[i][j][0] = MAXN;
        }
    }

    dist[row][col][0] = 0;
    maxd = dist[row][col][1] = kdist[row][col];

    for (d = 0; d <= maxd; d++) {
        for (i = 0; i < rows; i++) {
            for (j = 0; j < cols; j++) {
                if (dist[i][j][0] == d) {
                    if (move_on(i, j, 0)) {
                        if (maxd < d+1) {
                            maxd = d+1;
                        }
                    }

                    if (d+kdist[i][j] < dist[i][j][1]) {
                        dist[i][j][1] = d+kdist[i][j];
                        if (maxd < dist[i][j][1]) {
                            maxd = dist[i][j][1];
                        }
                    }
                }

                if (dist[i][j][1] == d) {
                    if (move_on(i, j, 1)) {
                        if (maxd < d+1) {
                            maxd = d+1;
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("camelot.in", "r");
    fout = fopen("camelot.out", "w");
    char c;
    int r, i, j, d, d1, d2;

    fscanf(fin, "%d %d\n", &rows, &cols);

    c = fgetc(fin);
    fscanf(fin, "%d", &r);
    c -= 'A';
    r--;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            d1 = abs(i-r);
            d2 = abs(j-c);
            kcost[i][j] = kdist[i][j] = max(d1, d2);
        }
    }

    while (1) {
        fgetc(fin);
        c = fgetc(fin);
        if (c == EOF) {
            break;
        }
        fscanf(fin, "%d", &r);
        c -= 'A';
        r--;

        add_knight(r, c);

        for (i = 0; i < rows; i++) {
            for (j = 0; j < cols; j++) {
                if (cost[i][j] != MAXN && dist[i][j][0] != MAXN && dist[i][j][1] != MAXN) {
                    cost[i][j] += dist[i][j][0];

                    if (kcost[i][j] > dist[i][j][1]-dist[i][j][0]) {
                        kcost[i][j] = dist[i][j][1]-dist[i][j][0];
                    }
                } else {
                    cost[i][j] = MAXN;
                }
            }
        }
    }

    d = cost[0][0]+kcost[0][0];
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (cost[i][j] != MAXN && d > cost[i][j]+kcost[i][j]) {
                d = cost[i][j]+kcost[i][j];
            }
        }
    }

    fprintf(fout, "%d\n", d);

    return 0;
}

