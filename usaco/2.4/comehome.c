/*
ID: baikaiz1
PROG: comehome
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file comehome.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

#define INFINITY 0x7FFFFFFF

inline char label2idx(char a) {
    if (a <= 'Z') {
        return a - 'A';
    } else {
        return a - 'a' + 26;
    }
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("comehome.in", "r");
    fout = fopen("comehome.out", "w");
    int edge[52][52] = {0};
    int d[52] = {0};
    char visited[52] = {0};
    char start, end;
    int i, j, m, p;

    for (i = 0; i < 52; i++) {
        edge[i][i] = 0;
        for (j = i+1; j < 52; j++) {
            edge[j][i] = edge[i][j] = INFINITY;
        }
    }

    for (i = 0; i < 52; i++) {
        d[i] = INFINITY;
    }

    fscanf(fin, "%d\n", &i);
    while (fscanf(fin, "%c %c %d\n", &start, &end, &i) == 3) {
        start = label2idx(start); 
        end = label2idx(end);
        if (edge[start][end] > i) {
            edge[end][start] = edge[start][end] = i;
        }
    }
    d[label2idx('Z')] = 0;
    while (1) {
        p = -1;
        m = INFINITY;
        for (j = 0; j < 52; j++) {
            if (!visited[j] && d[j] < m) {
                m = d[j];
                p = j;
            }
        }

        if (p == -1) {
            break;
        }

        visited[p] = 1;
        for (j = 0; j < 52; j++) {
            if (!visited[j] && edge[p][j] < INFINITY && d[p]+edge[p][j] < d[j]) {
                d[j] = d[p] + edge[p][j];
            }
        }
    }

    m = INFINITY;
    i = 25;
    p = 0;
    while (i--) {
        if (d[i] < m) {
            m = d[i];
            p = i;
        }
    }

    fprintf(fout, "%c %d\n", p+'A', m);

    return 0;
}

