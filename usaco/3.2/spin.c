/*
ID: baikaiz1
PROG: spin
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file spin.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("spin.in", "r");
    fout = fopen("spin.out", "w");
    int wheel_speed[5];
    int wheel_edge_num[5];
    int wheel_edge_p[5][5] = {0};
    int wheel_edge_len[5][5] = {0};
    int i, j, seconds;
    char wholes[360];
    int p_start, p_end;

    for (i = 0; i < 5; i++) {
        fscanf(fin, "%d %d", &wheel_speed[i], &wheel_edge_num[i]);
        for (j = 0; j < wheel_edge_num[i]; j++) {
            fscanf(fin, "%d %d", &wheel_edge_p[i][j], &wheel_edge_len[i][j]);
        }
    }

    for (seconds = 0; seconds < 360; seconds++) {
        bzero(wholes, sizeof(wholes));
        for (i = 0; i < 5; i++) {
            for (j = 0; j < wheel_edge_num[i]; j++) {
                p_start = wheel_edge_p[i][j] + wheel_speed[i] * seconds;
                if (p_start >= 360) {
                    p_start %= 360;
                }

                p_end = p_start + wheel_edge_len[i][j];
                while (p_start <= p_end) {
                    wholes[p_start%360]++;
                    p_start++;
                }
            }
        }

        for (i = 0; i < 360; i++) {
            if (wholes[i] >= 5) {
                break;
            }
        }

        if (i != 360) {
            fprintf(fout, "%d\n", seconds);
            break;
        }
    }

    if (seconds == 360) {
        fprintf(fout, "none\n");
    }

    return 0;
}

