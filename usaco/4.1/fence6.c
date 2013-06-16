/*
ID: baikaiz1
PROG: fence6
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file fence6.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

#define MAX_N 101
#define MAX_LEN 0x7FFFFFFF

int result = MAX_LEN;
int segs[MAX_N];
int seg_connect[MAX_N][MAX_N];
int seg_num;
int current_path[MAX_N];

void dfs(int start, int end, int end_point, int len) {
    int i;

    for (i = 1; i <= seg_num; i++) {
        if (seg_connect[end][i] && seg_connect[end][i] != end_point) {
            if (i == start) {
                if (seg_connect[start][end] == 2 && len < result) {
                    result = len;
                }
            } else {
                if (len + segs[i] < result && !current_path[i]) {
                    current_path[i] = 1;
                    dfs(start, i, seg_connect[i][end], len + segs[i]);
                    current_path[i] = 0;
                }
            }
        }
    }
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("fence6.in", "r");
#ifdef DEBUG
    fout = stdout;
#else
    fout = fopen("fence6.out", "w");
#endif
    int i, j, k, id, l, id2, n1, n2, len[MAX_N][MAX_N], end_point[MAX_N][MAX_N];

    fscanf(fin, "%d", &seg_num);
    for (i = 0; i < seg_num; i++) {
        fscanf(fin, "%d %d %d %d", &id, &l, &n1, &n2);
        segs[id] = l;

        for (j = 0; j < n1; j++) {
            fscanf(fin, "%d", &id2);
            seg_connect[id][id2] = 1;
        }

        for (j = 0; j < n2; j++) {
            fscanf(fin, "%d", &id2);
            seg_connect[id][id2] = 2;
        }
    }

    for (i = 1; i <= seg_num; i++) {
        // start from end point 1
        current_path[i] = 1;
        dfs(i, i, 2, segs[i]);
        current_path[i] = 0;
    }

    fprintf(fout, "%d\n", result);

    return 0;
}

/* vim: set ts=4 sts=4 sw=4 et: */

