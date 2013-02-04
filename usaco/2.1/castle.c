/*
ID: baikaiz1
PROG: castle
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file castle.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

#define MAX_ROWS 50

int matrix[MAX_ROWS][MAX_ROWS][5] = {0};
int sizes[MAX_ROWS*MAX_ROWS+1] = {0};
int queue[MAX_ROWS*MAX_ROWS+1] = {0}, head = 0, tail = 0;
int col, row;
int room_no;
int room_max = 0, remove_row, remove_col;
char remove_wall;

void travel() {
    int i, j, current;

    while (head < tail) {
        current = queue[head++];
        i = current / col;
        j = current % col;

        matrix[i][j][0] = room_no;
        sizes[room_no]++;

        if (matrix[i][j][1] && j >= 1 && matrix[i][j-1][0] == 0) {
            matrix[i][j-1][0] = -1;
            queue[tail++] = i*col+j-1;
        }

        if (matrix[i][j][2] && i >= 1 && matrix[i-1][j][0] == 0) {
            matrix[i-1][j][0] = -1;
            queue[tail++] = (i-1)*col+j;
        }

        if (matrix[i][j][3] && j < col-1 && matrix[i][j+1][0] == 0) {
            matrix[i][j+1][0] = -1;
            queue[tail++] = i*col+j+1;
        }
        
        if (matrix[i][j][4] && i < row-1 && matrix[i+1][j][0] == 0) {
            matrix[i+1][j][0] = -1;
            queue[tail++] = (i+1)*col+j;
        }
    };
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("castle.in", "r");
    fout = fopen("castle.out", "w");

    int i, j, relation;

    fscanf(fin, "%d %d", &col, &row);
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            matrix[i][j][0] = 0;
            fscanf(fin, "%d", &relation);
            matrix[i][j][1] = !(relation & 1);
            matrix[i][j][2] = !(relation & 2);
            matrix[i][j][3] = !(relation & 4);
            matrix[i][j][4] = !(relation & 8);
        }
    }

    room_no = 0;
    head = 0;
    tail = 0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (matrix[i][j][0] == 0) {
                matrix[i][j][0] = -1;
                queue[tail++] = i*col+j;
                room_no++;
                travel();
            }
        }
    }

    fprintf(fout, "%d\n", room_no);

    int m = 0;
    for (i = 1; i <= room_no; i++) {
        if (sizes[i] > m) {
            m = sizes[i];
        }
    }
    fprintf(fout, "%d\n", m);

    int room_size_1, room_size_2;
    for (j = 0; j < col; j++) {
        for (i = row - 1; i >= 0; i--) {
            room_size_1 = sizes[matrix[i][j][0]];
            // North wall
            if (i >= 1) {
                room_size_2 = sizes[matrix[i-1][j][0]];
                if (matrix[i-1][j][0] != matrix[i][j][0] && room_size_2+room_size_1 > room_max) {
                    room_max = room_size_2+room_size_1;
                    remove_row = i + 1;
                    remove_col = j + 1;
                    remove_wall = 'N';
                }
            }

            // East wall
            if (j < col - 1) {
                room_size_2 = sizes[matrix[i][j+1][0]];
                if (matrix[i][j+1][0] != matrix[i][j][0] && room_size_2+room_size_1 > room_max) {
                    room_max = room_size_2+room_size_1;
                    remove_row = i + 1;
                    remove_col = j + 1;
                    remove_wall = 'E';
                }
            }

        }
    }

    fprintf(fout, "%d\n", room_max);
    fprintf(fout, "%d %d %c\n", remove_row, remove_col, remove_wall);

    return 0;
}

