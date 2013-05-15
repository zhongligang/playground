/*
ID: baikaiz1
PROG: humble
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file humble.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

#define MAX_P_NUM 100
#define MAX_HUM_IDX 100000

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("humble.in", "r");
    fout = fopen("humble.out", "w");
    unsigned int p_set[MAX_P_NUM];
    int p_idx[MAX_P_NUM] = {0};
    unsigned int result[100001];
    int result_idx;
    unsigned m, tmp, m_hum;
    int p_num, nth;
    int i;

    fscanf(fin, "%d %d", &p_num, &nth);
    for (i = 0; i < p_num; i++) {
        fscanf(fin, "%d", p_set+i);
    }

    result[0] = 1;
    result_idx = 0;
    while (result_idx < nth) {
        m = 0xFFFFFFFF;
        m_hum = result[result_idx];
        for (i = 0; i < p_num; i++) {
            tmp = result[p_idx[i]]*p_set[i];
            while (tmp <= m_hum) {
                tmp = result[++p_idx[i]]*p_set[i];
            }

            if (tmp < m) {
                m = tmp;
            }
        }

        result[++result_idx] = m;
    }

    fprintf(fout, "%d\n", result[result_idx]);

    return 0;
}

