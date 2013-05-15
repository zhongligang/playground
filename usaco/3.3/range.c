/*
ID: baikaiz1
PROG: range
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file range.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("range.in", "r");
    fout = fopen("range.out", "w");
    unsigned int count[250][250][8] = {0};
    int n_squares[251] = {0};
    unsigned int map[250][8] = {0};
    char c;
    int rows;
    int row, col;
    int i, j, l, rowl, coll, maxl;

    fscanf(fin, "%d\n", &rows);

    row = 0;
    col = 0;
    while ((c = fgetc(fin)) != EOF) {
        if (c == '\n') {
            row++;
            col = 0;
            continue;
        }

        if (c == '1') {
            map[row][col/32] |= (1 << (col%32));
            count[row][col][0] = 2;
        }

        col++;
    }

    for (row = 1; row < rows; row++) {
        for (col = 1; col < rows; col++) {
            if (!(map[row][col/32] & (1<<(col%32)))) {
                continue;
            }

            rowl = row+1;
            coll = col+1;
            maxl = rowl > coll ? coll : rowl;
            for (l = 2; l <= maxl; l++) {
                if (count[row-1][col-1][(l-1)/32] & (1<<((l-1)%32))
                    && count[row-1][col][(l-1)/32] & (1<<((l-1)%32))
                    && count[row][col-1][(l-1)/32] & (1<<((l-1)%32))) {
                    count[row][col][l/32] |= (1<<(l%32));
                    n_squares[l]++;
                } else {
                    break;
                }
            }
        }
    }

    for (i = 2; i <= rows; i++) {
        if (n_squares[i] > 0) {
            fprintf(fout, "%d %d\n", i, n_squares[i]);
        }
    }

    return 0;
}

