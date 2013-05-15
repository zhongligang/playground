/*
ID: baikaiz1
PROG: stamps
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file stamps.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#define STACK_MAX 2000001

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("stamps.in", "r");
    fout = fopen("stamps.out", "w");
    int n_pos, n_stamp;
    int stamps[50];
    int i, j, k;
    int seq[70000];
    int stack[STACK_MAX];
    int stack_top = 0;
    int current_top;
    int prev_top;
    int current_stamp;
    int new_v;
    int section;
    int section_val;


    fscanf(fin, "%d %d\n", &n_pos, &n_stamp);
    for (i = 0; i < n_stamp; i++) {
        fscanf(fin, "%d", stamps+i);
    }

    bzero(seq, sizeof(seq));
    stack[0] = 0;
    stack_top = 1;

    for (i = 0; i < n_stamp; i++) {
        new_v = stamps[i];
        section = new_v >> 5;
        section_val = 1 << (new_v & 0x1F);
        if (!(seq[section]&section_val)) {
            seq[section] |= section_val;
            stack[stack_top++] = new_v;
        }
    }

    prev_top = 1;
    current_top = stack_top;
    for (j = 1; j < n_pos; j++) {
        for (i = 0; i < n_stamp; i++) {
            current_stamp = stamps[i];
            for (k = prev_top; k < current_top; k++) {
                new_v = stack[k] + current_stamp;
                section = new_v >> 5;
                section_val = 1 << (new_v & 0x1F);
                if (!(seq[section]&section_val)) {
                    seq[section] |= section_val;
                    stack[stack_top++] = new_v;
                }
            }
        }
        prev_top = current_top;
        current_top = stack_top;
    }

    i = 0;
    section = 0;
    section_val = 2;
    while (seq[section] & section_val) {
        if (section_val == 0x80000000) {
            section_val = 1;
            section++;
        } else {
            section_val <<= 1;
        }
        i++;
    }

    fprintf(fout, "%d\n", i);

    return 0;
}

