/*
ID: baikaiz1
PROG: milk3
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$ 
 * 
 * @file milk3.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CAP  21

int status[MAX_CAP][MAX_CAP];
int result[MAX_CAP];
int a_size, b_size, c_size;

int max(a, b) {
    return a > b ? a: b;
}

int min(a, b) {
    return a > b ? b : a;
}

void dfs(int b, int c) {
    int a = c_size - c - b,
        out,
        new_a, new_b, new_c;

    status[b][c] = 1;
    // try c
    if (c > 0) {
        // c -> b
        if (b < b_size) {
            out = min(b_size - b, c);
            new_b = b + out;
            new_c = c - out;
            if (new_b + new_c == c_size) {
                result[new_c] = 1;
            }
            if (status[new_b][new_c] != 1) {
                dfs(new_b, new_c);
            }
        }
        // c -> a
        if (a < a_size) {
            out = min(a_size - a, c);
            new_a = a + out;
            new_c = c - out;
            new_b = c_size - new_a - new_c;
            if (status[new_b][new_c] != 1) {
                dfs(new_b, new_c);
            }
        }
    }

    //try b
    if (b > 0) {
        // b -> c
        if (c < c_size) {
            out = min(c_size - c, b);
            new_c = c + out;
            new_b = b - out;
            if (new_b + new_c == c_size) {
                result[new_c] = 1;
            }
            if (status[new_b][new_c] != 1) {
                dfs(new_b, new_c);
            }
        }
        // b -> a
        if (a < a_size) {
            out = min(a_size - a, b);
            new_a = a + out;
            new_b = b - out;
            new_c = c_size - new_a - new_b;
            if (status[new_b][new_c] != 1) {
                dfs(new_b, new_c);
            }
        }
    }

    // try a
    if (a > 0) {
        // a -> c
        if (c < c_size) {
            out = min(c_size - c, a);
            new_c = c + out;
            new_a = a - out;
            new_b = c_size - new_a - new_c;
            if (new_b + new_c == c_size) {
                result[new_c] = 1;
            }
            if (status[new_b][new_c] != 1) {
                dfs(new_b, new_c);
            }
        }
        // a -> b
        if (b < b_size) {
            out = min(b_size - b, a);
            new_b = b + out;
            new_a = a - out;
            new_c = c_size - new_a - new_b;
            if (new_b + new_c == c_size) {
                result[new_c] = 1;
            }
            if (status[new_b][new_c] != 1) {
                dfs(new_b, new_c);
            }
        }
    }
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    int i;

    fin = fopen("milk3.in", "r");
    fout = fopen("milk3.out", "w");

    fscanf(fin, "%d %d %d", &a_size, &b_size, &c_size);

    dfs(0, c_size);

    for (i = 0; i < c_size; i++) {
        if (result[i] == 1) {
            fprintf(fout, "%d ", i);
        }
    }

    fprintf(fout, "%d\n", c_size);

    return 0;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 et: */
