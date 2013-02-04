/*
ID: baikaiz1
PROG: numtri
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file numtri.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

#define MAX_NUM 1000

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("numtri.in", "r");
    fout = fopen("numtri.out", "w");

    int triangle[MAX_NUM*(MAX_NUM+1)/2 + 1];
    int rows;
    int total;
    int i = 0;
    int current_row = 0;
    int start = 0;
    int lval, rval;

    fscanf(fin, "%d", &rows);
    total = (rows)*(rows+1)/2;

    i = 0;
    while (i++<=total) {
        fscanf(fin, "%d", triangle+i);
    }

    i = total - rows;
    current_row = rows - 1;
    while (i >= 1) {
        start = i - current_row;
        while (i > start) {
            lval = triangle[i+current_row];
            rval = triangle[i+current_row+1];
            if (lval > rval) {
                triangle[i] += lval;
            } else {
                triangle[i] += rval;
            }
            i--;
        }

        current_row--;
    }

    fprintf(fout, "%d\n", triangle[1]);

    return 0;
}

