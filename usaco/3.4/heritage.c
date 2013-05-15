/*
ID: baikaiz1
PROG: heritage
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file heritage.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char in_order[27];
char pre_order[27];
char post_order[27];
int post_order_idx;
char in_order_hash[26];

void fill_root(int in_order_start, int in_order_end, int pre_order_start, int pre_order_end) {
    int in_order_split = in_order_hash[pre_order[pre_order_start]-'A'];

    post_order[post_order_idx--] = pre_order[pre_order_start];
    if (in_order_split < in_order_end) {
        fill_root(in_order_split+1, in_order_end, pre_order_end-(in_order_end-in_order_split)+1, pre_order_end);
    }

    if (in_order_split > in_order_start) {
        fill_root(in_order_start, in_order_split-1, pre_order_start+1, pre_order_start+(in_order_split-in_order_start));
    }
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("heritage.in", "r");
#ifdef DEBUG
    fout = stdout;
#else
    fout = fopen("heritage.out", "w");
#endif

    int tree_len;
    char *p, i;

    fscanf(fin, "%s", in_order);
    fscanf(fin, "%s", pre_order);

    tree_len = strlen(in_order);
    post_order_idx = tree_len - 1;
    p = in_order;
    i = 0;
    while (*p) {
        in_order_hash[*p-'A'] = i;
        i++;
        p++;
    }

    fill_root(0, tree_len - 1, 0, tree_len - 1);

    fprintf(fout, "%s\n", post_order);

    return 0;
}

