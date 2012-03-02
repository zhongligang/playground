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
#define MODULAR 1000000007

#define FORMAT_RESULT(x) if (x >= MODULAR) {\
    x -= MODULAR;\
} else if (x < 0) {\
    x += MODULAR;\
}

char board[MAX_WIDTH][MAX_WIDTH];
int width; // board width
int max_step;  // step can move once
int max_moves;
int result[MAX_MOVE][MAX_WIDTH][MAX_WIDTH] = {0};
int cache_asc[2][MAX_WIDTH][MAX_WIDTH];
int cache_desc[2][MAX_WIDTH][MAX_WIDTH];
int read_index;
int write_index;

void
compute(int moves)
{
    int y, x, x1, y1, y2, x2, dx, dy;
    
    // (0, 0)
    for (y = 0; y < max_step; y++) {
        result[moves][0][0] += cache_desc[read_index][y][0];
        FORMAT_RESULT(result[moves][0][0]);
    }
    if (max_step < width) {
        result[moves][0][0] += cache_desc[read_index][max_step][0];
        FORMAT_RESULT(result[moves][0][0]);
    } else {
        if (1 < width) {
            result[moves][0][0] += cache_desc[read_index][max_step - 1][1];
            FORMAT_RESULT(result[moves][0][0]);
        }
    }
    cache_desc[write_index][0][0] = cache_asc[write_index][0][0] = board[0][0] == 'P' ? 0 : result[moves][0][0];

    // [(1, 0), (width - 1, 0)]
    for (x = 1; x < width; x++) {
        result[moves][0][x] = result[moves][0][x - 1];

        x1 = x;
        y1 = max_step;
        if (y1 >= width) {
            dy = y1 - width + 1;
            y1 -= dy;
            x1 += dy;
        }
        if (x1 < width) {
            result[moves][0][x] += cache_desc[read_index][y1][x1];
            FORMAT_RESULT(result[moves][0][x]);
        }

        x1 = x - 1;
        y1 = max_step;
        if (y1 >= width) {
            dy = y1 - width + 1;
            y1 -= dy;
            x1 -= dy;
        }
        if (x1 >= 0) {
            result[moves][0][x] -= cache_asc[read_index][y1][x1];
            FORMAT_RESULT(result[moves][0][x]);
        }

        cache_desc[write_index][0][x] = cache_asc[write_index][0][x] = board[0][x] == 'P' ? 0 : result[moves][0][x];
    }

    // [(0, 1), (width - 1, width - 1)]
    for (y = 1; y < width; y++) {
        for (x = 0; x < width; x++) {
            result[moves][y][x] = result[moves][y - 1][x];

            x1 = x;
            y1 = y + max_step;
            x2 = x + max_step;
            y2 = y;
            if (y1 >= width) {
                dy = y1 - width + 1;
                y1 -= dy;
                x1 += dy;
            }
            if (x1 < width) {
                if (x2 >= width - 1) {
                    result[moves][y][x] += cache_desc[read_index][y1][x1];
                    FORMAT_RESULT(result[moves][y][x]);
                } else {
                    result[moves][y][x] += cache_desc[read_index][y1][x1] - cache_desc[read_index][y2 - 1][x2 + 1];
                    FORMAT_RESULT(result[moves][y][x]);
                }
            }
            x1 = x;
            y1 = y + max_step;
            x2 = x - max_step;
            y2 = y;
            if (y1 >= width) {
                dy = y1 - width + 1;
                y1 -= dy;
                x1 -= dy;
            }
            if (x1 >= 0) {
                if (x2 <= 0) {
                    result[moves][y][x] += cache_asc[read_index][y1][x1];
                    FORMAT_RESULT(result[moves][y][x]);
                } else {
                    result[moves][y][x] += cache_asc[read_index][y1][x1] - cache_asc[read_index][y2 - 1][x2 - 1];
                    FORMAT_RESULT(result[moves][y][x]);
                }
            }
            if (y + max_step < width) {
                result[moves][y][x] -= result[moves - 1][y + max_step][x];
                FORMAT_RESULT(result[moves][y][x]);
            }

            x1 = x + max_step;
            y1 = y - 1;
            x2 = x;
            y2 = y - 1 - max_step;
            if (x1 >= width) {
                dx = x1 - width + 1;
                y1 -= dx;
                x1 -= dx;
            }
            if (y1 >= 0) {
                if (y2 <= 0 || x2 == 0) {
                    result[moves][y][x] -= cache_asc[read_index][y1][x1];
                    FORMAT_RESULT(result[moves][y][x]);
                } else {
                    result[moves][y][x] -= cache_asc[read_index][y1][x1] - cache_asc[read_index][y2 - 1][x2 - 1];
                    FORMAT_RESULT(result[moves][y][x]);
                }
            }

            x1 = x - max_step;
            y1 = y - 1;
            x2 = x;
            y2 = y - 1 - max_step;
            if (x1 < 0) {
                dx = -x1;
                x1 += dx;
                y1 -= dx;
            }
            if (y1 >= 0) {
                if (y2 <= 0 || x2 == width - 1) {
                    result[moves][y][x] -= cache_desc[read_index][y1][x1];
                    FORMAT_RESULT(result[moves][y][x]);
                } else {
                    result[moves][y][x] -= cache_desc[read_index][y1][x1] - cache_desc[read_index][y2 - 1][x2 + 1];
                    FORMAT_RESULT(result[moves][y][x]);
                }
            }
            if (y - 1 - max_step >= 0) {
                result[moves][y][x] += result[moves - 1][y - 1 - max_step][x];
                FORMAT_RESULT(result[moves][y][x]);
            }


            cache_asc[write_index][y][x] = x > 0 ? cache_asc[write_index][y - 1][x - 1] : 0;
            cache_desc[write_index][y][x] = (x < width - 1) ? cache_desc[write_index][y - 1][x + 1] : 0;
            if (board[y][x] != 'P') {
                cache_desc[write_index][y][x] += result[moves][y][x];
                FORMAT_RESULT(cache_desc[write_index][y][x]);
                cache_asc[write_index][y][x] += result[moves][y][x];
                FORMAT_RESULT(cache_asc[write_index][y][x]);
            }
        }
    }

    for (y = 0; y < width; y++) {
        for (x = 0; x < width; x++) {
            if (board[y][x] == 'P') {
                result[moves][y][x] = 0;
            }
        }
    }
}

int
main (int argc, char *argv[])
{
    int num_case;
    int x, y, moves, sum, i, j;

    scanf("%d", &num_case);
    while (num_case--) {
        bzero(result, sizeof(int) * MAX_MOVE * MAX_WIDTH * MAX_WIDTH);
        bzero(cache_asc, sizeof(int) * 2 * MAX_WIDTH * MAX_WIDTH);
        bzero(cache_desc, sizeof(int) * 2 * MAX_WIDTH * MAX_WIDTH);

        scanf("%d %d %d", &width, &max_moves, &max_step);
        for (y = width - 1; y >= 0; y--) {
            scanf("%s", board[y]);
        }

        read_index = 0;
        write_index = 1;
        for (y = 0; y < width; y++) {
            for (x = 0; x < width; x++) {
                if (board[y][x] == 'L') {
                    result[0][y][x] = 1;
                }
                if (x > 0 && y > 0) {
                    cache_asc[read_index][y][x] = result[0][y][x] + cache_asc[read_index][y - 1][x - 1];
                } else {
                    cache_asc[read_index][y][x] = result[0][y][x];
                }
                if (x < width && y > 0) {
                    cache_desc[read_index][y][x] = result[0][y][x] + cache_desc[read_index][y - 1][x + 1];
                } else {
                    cache_desc[read_index][y][x] = result[0][y][x];
                }
            }
        }

        for (moves = 1; moves <= max_moves; moves++) {
            compute(moves);
            if (read_index == 1) {
                write_index = 1;
                read_index = 0;
            } else {
                write_index = 0;
                read_index = 1;
            }
        }

        sum = 0;
        for (y = 0; y < width; y++) {
            for (x = 0; x < width; x++) {
                sum += result[max_moves][y][x];
                FORMAT_RESULT(sum);
            }
        }
        printf("%d\n", sum);
    }

    return 0;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 et: */
