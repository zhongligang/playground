/*
ID: baikaiz1
PROG: zerosum
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file zerosum.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

void dfs(FILE *fout, int sum, char pre_optoken, int pre_numtoken, char *ops, int ops_len, int ops_need) {
    int num = ops_len+2;
    int new_numtoken, new_sum;
    int i;

    if (ops_need == 0) {
        if (pre_optoken == '-') {
            sum -= pre_numtoken;
        } else {
            sum += pre_numtoken;
        }

        if (sum == 0) {
            fprintf(fout, "1");
            for (i = 0; i < ops_len; i++) {
                fprintf(fout, "%c%d", ops[i], i+2);
            }
            fprintf(fout, "\n");
        }

        return;
    }

    new_numtoken = pre_numtoken*10+num;
    ops[ops_len] = ' ';
    dfs(fout, sum, pre_optoken, new_numtoken, ops, ops_len+1, ops_need-1);

    if (pre_optoken == '-') {
        new_sum = sum - pre_numtoken;
    } else {
        new_sum = sum + pre_numtoken;
    }

    ops[ops_len] = '+';
    dfs(fout, new_sum, '+', ops_len+2, ops, ops_len+1, ops_need-1);

    ops[ops_len] = '-';
    dfs(fout, new_sum, '-', ops_len+2, ops, ops_len+1, ops_need-1);
}

// ASCII order ' ' '+' '-'
int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("zerosum.in", "r");
    fout = fopen("zerosum.out", "w");
    int n;
    int i;
    char ops[8];

    fscanf(fin, "%d", &n);
    dfs(fout, 0, '+', 1, ops, 0, n-1);

    return 0;
}

