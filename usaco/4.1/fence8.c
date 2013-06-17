/*
ID: baikaiz1
PROG: fence8
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file fence8.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

#define MAX_BOARDS   50
#define MAX_RAILS    1023
#define MAX_RAIL_LEN 128

int boards[MAX_BOARDS], num_boards;
int rails[MAX_RAILS], num_rails;
int sum_rails[MAX_RAILS];
int sum_boards;
int current_test;
int rail_from[MAX_RAILS];

int dfs(int idx_rail) {
    int i, j, wasted = 0, max;

    if (idx_rail == -1) {
        return 1;
    }

    for (i = 0; i < num_boards; i++) {
        if (boards[i] < rails[0]) {
            wasted += boards[i];
        }
    }

    // impossible
    if (wasted > sum_boards - sum_rails[current_test]) {
        return 0;
    }

    // If nth and n+1th have the same length; then
    //  nth from ith board and n+1th form i+1th board is the same as
    //  n+1th from ith board and nth form i+1th board
    // so we ignore some boards
    if (idx_rail < num_rails - 1 && rails[idx_rail] == rails[idx_rail+1]) {
        max = rail_from[idx_rail+1];
    } else {
        max = num_boards-1;
    }

    for (i = max; i >= 0; i--) {
        if (boards[i] >= rails[idx_rail]) {
            boards[i] -= rails[idx_rail];
            rail_from[idx_rail] = i;

            if (dfs(idx_rail-1)) {
                boards[i] += rails[idx_rail];
                return 1;
            }

            rail_from[idx_rail] = num_rails - 1;
            boards[i] += rails[idx_rail];
        }
    }

    return 0;
}

int cmp_int(const void *a, const void *b) {
    return *(int*)a > *(int*)b ? 1 : -1;
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("fence8.in", "r");
#ifdef DEBUG
    fout = stdout;
#else
    fout = fopen("fence8.out", "w");
#endif
    int i, l, r, m;

    fscanf(fin, "%d", &num_boards);
    for (i = 0; i < num_boards; i++) {
        fscanf(fin, "%d", boards+i);
        sum_boards += boards[i];
    }

    fscanf(fin, "%d", &num_rails);
    for (i = 0; i < num_rails; i++) {
        fscanf(fin, "%d", rails+i);
    }

    qsort(rails, num_rails, sizeof(int), cmp_int);
    qsort(boards, num_boards, sizeof(int), cmp_int);

    sum_rails[0] = rails[0];
    for (i = 1; i < num_rails; i++) {
        sum_rails[i] = rails[i] + sum_rails[i-1];
    }

    l = 0;
    r = num_rails - 1;
    // dfs id
    while (l < r - 1) {
        m = (l + r) / 2;
        current_test = m;
        for (i = 0; i < num_rails; i++) {
            rail_from[i] = num_boards - 1;
        }

        if (dfs(m)) {
            l = m;
        } else {
            r = m - 1;
        }
    }

    current_test = r;
    if (l >= r || !dfs(r)) {
        if (l == 0 && dfs(0) == 0) {
            m = -1;
        } else {
            m = l;
        }
    } else {
        m = r;
    }

    fprintf(fout, "%d\n", m+1);

    return 0;
}

