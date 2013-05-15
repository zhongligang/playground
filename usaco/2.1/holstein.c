/*
ID: baikaiz1
PROG: holstein
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file holstein.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#define MAX_V_NUM 25
#define MAX_FEEDS_NUM 15

int vnum;
int feeds_num;
int feeds[MAX_FEEDS_NUM][MAX_V_NUM];

int min_feed_num = MAX_FEEDS_NUM;
unsigned int min_feed_selected = 0;

int dfs(int *requires, unsigned int selected, int idx, int selected_num) {
    int current_requires[MAX_V_NUM];
    int i, j;
    int required;

    bcopy(requires, current_requires, sizeof(current_requires));

    // try add
    selected_num++;
    selected |= (1 << (feeds_num - idx - 1));
    required = 1;
    for (i = 0; i < vnum; i++) {
        current_requires[i] -= feeds[idx][i];
        if (current_requires[i] > 0) {
            required = 0;
        }
    }

    if (required) {
        if (selected_num < min_feed_num || selected_num == min_feed_num && min_feed_selected < selected) {
            min_feed_num = selected_num;
            min_feed_selected = selected;
        }
        return 1;
    }

    if (idx < feeds_num - 1) {
        dfs(requires, selected ^ (1 << (feeds_num - idx -1)), idx + 1, selected_num - 1);
        dfs(current_requires, selected, idx + 1, selected_num);
    }

    return 0;
}

int numof1(unsigned int a) {
    a = (a & 0x55555555) + ((a & 0xAAAAAAAA) >> 1);
    a = (a & 0x33333333) + ((a & 0xCCCCCCCC) >> 2);
    a = (a & 0x0F0F0F0F) + ((a & 0xF0F0F0F0) >> 4);
    a = (a & 0x00FF00FF) + ((a & 0xFF00FF00) >> 8);
    a = (a & 0x0000FFFF) + ((a & 0xFFFF0000) >> 16);

    return a;
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("holstein.in", "r");
    fout = fopen("holstein.out", "w");
    int i, j;
    int requires[MAX_V_NUM];

    fscanf(fin, "%d", &vnum);
    for (i = 0; i < vnum; i++) {
        fscanf(fin, "%d", requires+i);
    }

    fscanf(fin, "%d", &feeds_num);
    for (i = 0; i < feeds_num; i++) {
        for (j = 0; j < vnum; j++) {
            fscanf(fin, "%d", &feeds[i][j]);
        }
    }

    dfs(requires, 0, 0, 0);
    min_feed_selected = min_feed_selected << (32 - feeds_num);

    fprintf(fout, "%d", min_feed_num);
    i = 1;
    while (min_feed_selected) {
        if (min_feed_selected & 0x80000000u) {
            fprintf(fout, " %d", i);
        }
        min_feed_selected <<= 1;
        i++;
    }

    fprintf(fout, "\n");

    return 0;
}

