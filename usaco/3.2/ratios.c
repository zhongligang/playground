/*
ID: baikaiz1
PROG: ratios
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file ratios.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("ratios.in", "r");
    fout = fopen("ratios.out", "w");
    int target_radio[3];
    int owned_radio[3][3];
    int i, j, k;
    int solution[3];
    int minMulti = 100;
    int sum[3];
    int multi;

    fscanf(fin, "%d %d %d", target_radio, target_radio+1, target_radio+2);
    fscanf(fin, "%d %d %d", owned_radio[0], owned_radio[0]+1, owned_radio[0]+2);
    fscanf(fin, "%d %d %d", owned_radio[1], owned_radio[1]+1, owned_radio[1]+2);
    fscanf(fin, "%d %d %d", owned_radio[2], owned_radio[2]+1, owned_radio[2]+2);
    for (i = 0; i < 100; i++) {
        sum[0] = i * owned_radio[0][0];
        sum[1] = i * owned_radio[0][1];
        sum[2] = i * owned_radio[0][2];
        for (j = 0; j < 100; j++) {
            sum[0] += j*owned_radio[1][0];
            sum[1] += j*owned_radio[1][1];
            sum[2] += j*owned_radio[1][2];
            for (k =(i+j==0)?1:0; k < 100; k++) {
                sum[0] += k*owned_radio[2][0];
                sum[1] += k*owned_radio[2][1];
                sum[2] += k*owned_radio[2][2];
                if (sum[0] % target_radio[0] == 0) {
                    multi = sum[0]/target_radio[0];
                    if (multi < 100 && target_radio[1]*multi == sum[1] && target_radio[2]*multi == sum[2]) {
                        if (multi < minMulti) {
                            minMulti = multi;
                            solution[0] = i;
                            solution[1] = j;
                            solution[2] = k;
                        }
                    }
                }
                sum[0] -= k*owned_radio[2][0];
                sum[1] -= k*owned_radio[2][1];
                sum[2] -= k*owned_radio[2][2];
            }
            sum[0] -= j*owned_radio[1][0];
            sum[1] -= j*owned_radio[1][1];
            sum[2] -= j*owned_radio[1][2];
        }
    }

    if (minMulti >= 100) {
        fprintf(fout, "NONE\n");
    } else {
        fprintf(fout, "%d %d %d %d\n", solution[0], solution[1], solution[2], minMulti);
    }

    return 0;
}

