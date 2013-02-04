/*
ID: baikaiz1
PROG: checker
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file checker.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

// http://www.matrix67.com/blog/archives/3985
const int MultiplyDeBruijnBitPosition[32] = {
    0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
    31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
};

int size;
int row = 0, ld = 0, rd = 0;
// 0-2: top 3, 3: current
unsigned long long result[4] = {0};
int total = 0;
int mask = 0;

int get_pos(unsigned int v) {
    int r;
    r = MultiplyDeBruijnBitPosition[((v & -v) * 0x077CB531U) >> 27];

    return size - r;
}

void purge_result() {
    result[0] = result[1];
    result[1] = result[2];
    result[2] = result[3];
}

void check(row, ld, rd) {
    int available, pos;

    if (row != mask) {
        available = ~(row | ld | rd) & mask;
        while (available != 0) {
            pos = available & -available;
            result[3] = (result[3] << 4) | get_pos(pos);
            check(row | pos, (ld | pos) << 1, (rd | pos) >> 1);
            available ^= pos;
            result[3] >>= 4;
        }
    } else {
        total++;
        purge_result();
    }
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("checker.in", "r");
    fout = fopen("checker.out", "w");

    int i;
    char buffer[13];
    int buffer_idx;
    int result_idx;

    fscanf(fin, "%d", &size);

    i = size;
    while (i--) {
        mask = mask << 1 | 1;
    }
    check(0, 0, 0);

    for (result_idx = 2; result_idx >= 0; result_idx--) {
        buffer_idx = 0;
        while (result[result_idx] != 0) {
            buffer[buffer_idx++] = result[result_idx] & 15;
            result[result_idx] >>= 4 ;
        }
        fprintf(fout, "%d", buffer[--buffer_idx]);

        while (buffer_idx--) {
            fprintf(fout, " %d", buffer[buffer_idx]);
        }
        fprintf(fout, "\n");
    }

    fprintf(fout, "%d\n", total);

    return 0;
}

