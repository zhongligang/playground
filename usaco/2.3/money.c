/*
ID: baikaiz1
PROG: money
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file money.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("money.in", "r");
    fout = fopen("money.out", "w");

    unsigned long long solutions[10001] = {0};
    int n_coins, amount;
    int coins[25];
    int i, j;
    int current_coin;

    fscanf(fin, "%d %d", &n_coins, &amount);
    for (i = 0; i < n_coins; i++) {
        fscanf(fin, "%d", coins+i);
    }

    solutions[0] = 1;
    for (i = 0; i < n_coins; i++) {
        current_coin = coins[i];
        for (j = current_coin; j <= amount; j++) {
            solutions[j] = solutions[j] + solutions[j-current_coin];
        }
    }

    fprintf(fout, "%lld\n", solutions[amount]);

    return 0;
}

