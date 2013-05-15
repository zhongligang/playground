/*
ID: baikaiz1
PROG: sort3
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file sort3.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

int sort_int(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("sort3.in", "r");
    fout = fopen("sort3.out", "w");

    int numbers[1000] = {0};
    int sorted[1000] = {0};
    int total = 0;
    int i = 0;
    int left = 0;
    int count[4][4];
    int moves = 0;

    fscanf(fin, "%d", &total);
    while (i < total) {
        fscanf(fin, "%d", numbers+i);
        i++;
    }

    bzero(count, sizeof(count));
    bcopy(numbers, sorted, sizeof(int)*total);
    qsort(sorted, total, sizeof(int), sort_int);
    for (i = 0; i < total; i++) {
        if (numbers[i] != sorted[i]) {
            count[sorted[i]][numbers[i]]++;
        }
    }


    if (count[1][2] > count[2][1]) {
        moves += count[2][1];
        count[1][2] -= count[2][1];
        count[2][1] = 0;
        left += count[1][2];
    } else {
        moves += count[1][2];
        count[2][1] -= count[1][2];
        count[1][2] = 0;
        left += count[2][1];
    }

    if (count[1][3] > count[3][1]) {
        moves += count[3][1];
        count[1][3] -= count[3][1];
        count[3][1] = 0;
        left += count[1][3];
    } else {
        moves += count[1][3];
        count[3][1] -= count[1][3];
        count[1][3] = 0;
        left += count[3][1];
    }

    if (count[2][3] > count[3][2]) {
        moves += count[3][2];
        count[2][3] -= count[3][2];
        count[3][2] = 0;
        left += count[2][3];
    } else {
        moves += count[2][3];
        count[3][2] -= count[2][3];
        count[2][3] = 0;
        left += count[3][2];
    }

    moves += (left/3)*2;

    fprintf(fout, "%d\n", moves);

    return 0;
}

