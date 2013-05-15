/*
ID: baikaiz1
PROG: ttwo
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file ttwo.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

#define MOVE(row, col, direction)\
    switch (direction) {\
        case NORTH:\
            if (row > 0 && graph[row-1][col]) {\
                row--;\
            } else {\
                direction = EAST;\
            }\
            break;\
        case EAST:\
            if (col < 9 && graph[row][col+1]) {\
                col++;\
            } else {\
                direction = SOUTH;\
            }\
            break;\
        case SOUTH:\
            if (row < 9 && graph[row+1][col]) {\
                row++;\
            } else {\
                direction = WEST;\
            }\
            break;\
        case WEST:\
            if (col > 0 && graph[row][col-1]) {\
                col--;\
            } else {\
                direction = NORTH;\
            }\
            break;\
    }

#define NORTH 0 
#define EAST 1
#define SOUTH 2
#define WEST 3

char graph[10][10] = {0};

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("ttwo.in", "r");
    fout = fopen("ttwo.out", "w");
    int farmer_row, farmer_col;
    int cow_row, cow_col;
    char line[11];
    char *p;
    int row, col;
    int maxop = 160000;
    int counter = 0;
    int farmer_direction = NORTH;
    int cow_direction = NORTH;

    row = 0;
    while (fscanf(fin, "%s", line) == 1) {
        p = line;
        col = 0;
        while (*p) {
            if (*p == '*') {
                graph[row][col] = 0;
            } else {
                graph[row][col] = 1;
                if (*p == 'F') {
                    farmer_row = row;
                    farmer_col = col;
                } else if (*p == 'C') {
                    cow_row = row;
                    cow_col = col;
                }
            }
            p++;
            col++;
        }
        row++;
    }

    while (++counter <= maxop) {
        MOVE(farmer_row, farmer_col, farmer_direction);
        MOVE(cow_row, cow_col, cow_direction);

        if (cow_row == farmer_row && cow_col == farmer_col) {
            break;
        }
    }

    if (counter > maxop) {
        fprintf(fout, "0\n");
    } else {
        fprintf(fout, "%d\n", counter);
    }

    return 0;
}

