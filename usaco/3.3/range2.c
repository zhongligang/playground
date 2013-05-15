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
    int max_square[251] = {0};
    int n_squares[251] = {0};
    char c;
    int rows;
    int row, col;
    int i, s1, s2, s, prev;

    fscanf(fin, "%d\n", &rows);

    for (row = 0; row < rows; row++) {
        for (col = 1; col <= rows; col++) {
            c = fgetc(fin);

            if (c == '0') {
                max_square[col] = 0;
            } else {
                s1 = max_square[col-1];
                s2 = max_square[col];
                s = s1 > s2 ? s2 : s1;
                s = s > prev ? prev : s;
                s++;

                prev = max_square[col];
                max_square[col] = s;
                n_squares[s]++;
            }
        }
        c = fgetc(fin);
    }

    for (i = rows - 1; i >= 2; i--) {
        n_squares[i] += n_squares[i+1];
    }

    for (i = 2; i <= rows; i++) {
        if (n_squares[i] > 0) {
            fprintf(fout, "%d %d\n", i, n_squares[i]);
        }
    }

    return 0;
}

