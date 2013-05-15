/*
ID: baikaiz1
PROG: cowtour
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file cowtour.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <strings.h>

typedef struct {
    double x;
    double y;
} point_t;

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("cowtour.in", "r");
    fout = fopen("cowtour.out", "w");

    int npoint;
    char matrix[150][151];
    point_t points[150];
    int i, j;
    int x, y, z;
    double m;
    double lmi, lmj, lm;
    double md[150];
    double edge[150][150];
    double bridge;

    fscanf(fin, "%d", &npoint);
    for (i = 0; i < npoint; i++) {
        fscanf(fin, "%lf %lf", &points[i].x, &points[i].y);
    }

    for (i = 0; i < npoint; i++) {
        fscanf(fin, "%s", matrix[i]);
    }

    for (x = 0; x < npoint; x++) {
        for (y = x+1; y < npoint; y++) {
            if (matrix[x][y] == '1') {
                edge[y][x] = edge[x][y] = sqrt((points[x].x-points[y].x)*(points[x].x-points[y].x)+(points[x].y-points[y].y)*(points[x].y-points[y].y));
            } else {
                edge[y][x] = edge[x][y] = -1;
            }
        }
    }
    for (z = 0; z < npoint; z++) {
        for (x = 0; x < npoint; x++) {
            for (y = x+1; y < npoint; y++) {
                if (edge[x][z] > -0.5 && edge[y][z] > -0.5 && (edge[x][z]+edge[y][z] < edge[x][y] || edge[x][y] < -0.5)) {
                    edge[y][x] = edge[x][y] = edge[x][z] + edge[y][z];
                }
            }
        }
    }

    for (z = 0; z < npoint; z++) {
        md[z] = 0;
        for (x = 0; x < npoint; x++) {
            for (y = x+1; y < npoint; y++) {
                if ((x == z || edge[x][z] > -0.5) && (y == z || edge[y][z] > -0.5) && edge[x][y] > md[z]) {
                    md[z] = edge[x][y];
                }
            }
        }
    }

    m = -1;
    for (i = 0; i < npoint; i++) {
        for (j = i + 1; j < npoint; j++) {
            // try add an edge
            if (edge[i][j] < -0.5) {
                bridge = sqrt((points[i].x-points[j].x)*(points[i].x-points[j].x)+(points[i].y-points[j].y)*(points[i].y-points[j].y));

                lmi = 0;
                for (x = 0; x < npoint; x++) {
                    if (x != i && edge[x][i] > lmi) {
                        lmi = edge[x][i];
                    }
                }
                lmj = 0;
                for (x = 0; x < npoint; x++) {
                    if (x != j && edge[x][j] > lmj) {
                        lmj = edge[x][j];
                    }
                }

                lm = md[i] > md[j] ? md[i] : md[j];
                if (lm < lmi + lmj + bridge) {
                    lm = lmi+lmj+bridge;
                }
                if (lm < m || m < -0.5) {
                    m = lm;
                }
            }
        }
    }

    fprintf(fout, "%.6lf\n", m);

    return 0;
}

