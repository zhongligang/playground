/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$ 
 * 
 * @file fc.c
 * @author zhongligang <ZhongLigang@gmail.com>
 * @date 2012-01-30 13:42:48
 */
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#define MAX_WIDTH  200
#define MAX_MOVE 201

char board[MAX_WIDTH][MAX_WIDTH];
int result[MAX_MOVE][MAX_WIDTH][MAX_WIDTH] = {0};
int width; // board width
int step;  // step can move once

// can move from (x1, y1) to (x2, y2)?
int
reachable(int x1, int y1, int x2, int y2)
{
    return (abs(x1 - x2) + abs(y1 - y2) <= step) ? 1 : 0; 
}

int
compute(int _step, int x, int y)
{
    int num = 0;
    int x1, y1, x_bound;

        for (y1 = 0; y1 < width; y1++) {
            for (x1 = 0; x1 < width; x1++) {
                if (reachable(x1, y1, x, y)) {
                    num += result[_step - 1][y1][x1];
                    if (num >= 1000000007) {
                        num -= 1000000007;
                    }
                }
            }
        }

    return num;
}

int
main (int argc, char *argv[])
{
    int num_case;
    int moves;
    int i, j, k, l, sum;

    scanf("%d", &num_case);
    for (i = 0; i < num_case; i++) {
        scanf("%d %d %d", &width, &moves, &step);

        bzero(result, sizeof(i) * MAX_MOVE * MAX_WIDTH * MAX_WIDTH);
        for (j = 0; j < width; j++) {
            scanf("%s", board[j]);
            for (k = 0; k < width; k++) {
                result[0][j][k] = board[j][k] == 'L' ? 1 : 0;
            }
        }

        for (j = 1; j <= moves; j++) {
            for (k = 0; k < width; k++) {
                for (l = 0; l < width; l++) {
                    if (board[k][l] != 'P') {
                        result[j][k][l] = compute(j, l, k);
                    }
                }
            }
        }

        sum = 0;
        for (j = 0; j < width; j++) {
            for (k = 0; k < width; k++) {
                sum += result[moves][k][j];
                if (sum >= 1000000007) {
                    sum -= 1000000007;
                }
            }
        }

        printf("%d\n", sum);
    }

    return 0;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 et: */
