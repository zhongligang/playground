/*
ID: baikaiz1
PROG: concom
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file concom.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

char share[101][101] = {0};
char control[101][101] = {0};

void update(int a, int b) {
    int i;

    if (control[a][b]) {
        return;
    }

    control[a][b] = 1;
    for (i = 1; i <= 100; i++) {
        share[a][i] += share[b][i];
        if (share[a][i] > 50) {
            update(a, i);
        }
    }

    for (i = 1; i <= 100; i++) {
        if (control[i][a]) {
            update(i, b);
        }
    }
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("concom.in", "r");
    fout = fopen("concom.out", "w");

    //a owns v% percent of b
    int comp_a, comp_b, s;
    int i;

    for (i = 1; i <= 100; i++) {
        control[i][i] = 1;
    }

    fscanf(fin, "%d", &comp_a);
    while (fscanf(fin, "%d %d %d", &comp_a, &comp_b, &s) == 3) {
        for (i = 1; i <= 100; i++) {
            if (control[i][comp_a]) {
                share[i][comp_b] += s;
                if (share[i][comp_b] > 50) {
                    update(i, comp_b);
                }
            }
        }
    }

    for (comp_a = 1; comp_a <= 100; comp_a++) {
        for (comp_b = 1; comp_b <= 100; comp_b++) {
            if (comp_a != comp_b && control[comp_a][comp_b]) {
                fprintf(fout, "%d %d\n", comp_a, comp_b);
            }
        }
    }

    return 0;
}

