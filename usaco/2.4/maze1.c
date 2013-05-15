/*
ID: baikaiz1
PROG: maze1
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file maze1.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#define IFINITY 0x7FFFFFFF

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("maze1.in", "r");
    fout = fopen("maze1.out", "w");
    int rows, cols;
    int npoints;
    int exit1 = -1, exit2 = -1;
    int exit;
    char graph[201][77] = {0};
    int d1[3800];
    int row, col;
    int i;
    int j;
    int p;
    int d;
    int worst;
    int queue[3800];
    int queue_tail = 0;

    fscanf(fin, "%d %d", &cols, &rows);
    npoints = rows*cols;

    for (row = 0; row < rows*2+1; row++) {
        i = 0;
        fgetc(fin);
        while (i <= 2*cols) {
            fscanf(fin, "%c", &graph[row][i++]);
        }

        if (row % 2) {
            if (graph[row][0] == ' ') {
                if (exit1 == -1) {
                    exit1 = row/2*cols;
                } else {
                    exit2 = row/2*cols;
                }
            }

            if (graph[row][cols*2] == ' ') {
                if (exit1 == -1) {
                    exit1 = row/2*cols+cols-1;
                } else {
                    exit2 = row/2*cols+cols-1;
                }
            }
        } else {
            if (row == 0) {
                for (i = 1; i<cols*2; i+=2) {
                    if (graph[row][i] == ' ') {
                        if (exit1 == -1) {
                            exit1 = i/2;
                        } else {
                            exit2 = i/2;
                        }
                    }
                }
            } else if (row == 2*rows) {
                for (i = 1; i<cols*2; i+=2) {
                    if (graph[row][i] == ' ') {
                        if (exit1 == -1) {
                            exit1 = cols*(rows-1)+i/2;
                        } else {
                            exit2 = cols*(rows-1)+i/2;
                        }
                    }
                }
            }
        }
    }

    i = npoints;
    while (i--) {
        d1[i] = IFINITY;
    }

    d1[exit1] = 1;
    d1[exit2] = 1;
    queue[queue_tail++] = exit1;
    row = exit1/cols;
    col = exit1%cols;
    graph[row*2+1][col*2+1] = '*';
    if (exit1 != exit2) {
        queue[queue_tail++] = exit2;
        row = exit2/cols;
        col = exit2%cols;
        graph[row*2+1][col*2+1] = '*';
    }

    for (i = 0; i < queue_tail; i++) {
        p = queue[i];
        row = p/cols;
        col = p%cols;

        if (row > 0) {
            if (graph[row*2][col*2+1] == ' ' && graph[row*2-1][col*2+1] == ' ') {
                graph[row*2-1][col*2+1] = '*';
                d1[(row-1)*cols+col] = d1[p]+1;
                queue[queue_tail++] = (row-1)*cols+col;
            }
        }

        if (row < rows-1) {
            if (graph[row*2+2][col*2+1] == ' ' && graph[row*2+3][col*2+1] == ' ') {
                graph[row*2+3][col*2+1] = '*';
                d1[(row+1)*cols+col] = d1[p]+1;
                queue[queue_tail++] = (row+1)*cols+col;
            }
        }

        if (col > 0) {
            if (graph[row*2+1][col*2] == ' ' && graph[row*2+1][col*2-1] == ' ') {
                graph[row*2+1][col*2-1] = '*';
                d1[(row)*cols+col-1] = d1[p]+1;
                queue[queue_tail++] = (row)*cols+col-1;
            }
        }

        if (col < cols-1) {
            if (graph[row*2+1][col*2+2] == ' ' && graph[row*2+1][col*2+3] == ' ') {
                graph[row*2+1][col*2+3] = '*';
                d1[(row)*cols+col+1] = d1[p]+1;
                queue[queue_tail++] = (row)*cols+col+1;
            }
        }
    }

    fprintf(fout, "%d\n", d1[queue[queue_tail-1]]);

    return 0;
}

