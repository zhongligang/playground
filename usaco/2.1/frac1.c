/*
ID: baikaiz1
PROG: frac1
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file frac1.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>
FILE *fin, *fout;
int max_den;

void worker(int start_num, int start_den, int end_num, int end_den) {
    int middle_den = start_den + end_den;
    int middle_num = start_num + end_num;

    if (start_den + middle_den <= max_den) {
        worker(start_num, start_den, middle_num, middle_den);
    }
    if (middle_den <= max_den) {
        fprintf(fout, "%d/%d\n", middle_num, middle_den);
    }
    if (end_den + middle_den <= max_den) {
        worker(middle_num, middle_den, end_num, end_den);
    }
}

int main(int argc, char** argv) {
    fin = fopen("frac1.in", "r");
    fout = fopen("frac1.out", "w");

    fscanf(fin, "%d", &max_den);

    fprintf(fout, "0/1\n");
    worker(0, 1, 1, 1);
    fprintf(fout, "1/1\n");

    return 0;
}

