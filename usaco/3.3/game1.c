/*
ID: baikaiz1
PROG: game1
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file game1.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("game1.in", "r");
    fout = fopen("game1.out", "w");
    int num[100];
    int score[100][100];
    int sum[100][100] = {0};
    int n_num;
    int head, tail;
    int head_max;
    int sum_head, sum_tail;
    int i, j, len;

    fscanf(fin, "%d", &n_num);
    for (i = 0; i < n_num; i++) {
        fscanf(fin, "%d", num+i);
    }

    for (head = 0, head_max = n_num - 1; head < head_max; head++) {
        score[head][head] = num[head];
    }

    for (head = 0, head_max = n_num - 1; head < head_max; head++) {
        tail = head+1;
        score[head][tail] = num[head]>num[tail]?num[head]:num[tail];
    }

    for (i = 0; i < n_num; i++) {
        for (j = i; j < n_num; j++) {
            sum[i][j] += num[j] + (j == 0 ? 0 : sum[i][j-1]);
        }
    }

    for (len = 3; len <= n_num; len++) {
        for (head = 0, head_max = n_num - len + 1; head < head_max; head++) {
            tail = head + len - 1;
            sum_head = sum[head+1][tail] - score[head+1][tail] + num[head];
            sum_tail = sum[head][tail-1] - score[head][tail-1] + num[tail];

            score[head][tail] = sum_head > sum_tail ? sum_head : sum_tail;
        }
    }

    fprintf(fout, "%d %d\n", score[0][n_num-1], sum[0][n_num-1]-score[0][n_num-1]);

    return 0;
}

