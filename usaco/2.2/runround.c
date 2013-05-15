/*
ID: baikaiz1
PROG: runround
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file runround.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

int is_runaround(int m) {
    int digits[10] = {0}, digit_count[10] = {0}, digit_visited[10] = {0}, r, i, idx, num_of_digits;

    num_of_digits = 0;
    while (m) {
        r = m % 10;

        if (digit_count[r]) {
            return 0;
        }

        digit_count[r] = 1;
        digits[9 - num_of_digits] = r;

        m /= 10;
        num_of_digits++;
    }

    if (num_of_digits != 9) {
        for (i = 1; i <= num_of_digits; i++) {
            digits[i] = digits[i+9-num_of_digits];
        }
    }

    idx = 1;
    i = num_of_digits;
    while (i--) {
        r = digits[idx];

        idx += r;
        if (idx > num_of_digits) {
            idx %= num_of_digits;
            if (idx == 0) {
                idx = num_of_digits;
            }
        }

        if (digit_visited[digits[idx]]) {
            return 0;
        }

        digit_visited[digits[idx]] = 1;
    }

    return 1;
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("runround.in", "r");
    fout = fopen("runround.out", "w");
    int m;

    fscanf(fin, "%d", &m);

    while (1) {
        m++;
        if (is_runaround(m)) {
            fprintf(fout, "%d\n", m);
            break;
        }
    }

    return 0;
}

