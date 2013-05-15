/*
ID: baikaiz1
PROG: msquare
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file msquare.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

const int MASK_0 = 7;
const int MASK_1 = 7 << 3;
const int MASK_2 = 7 << 6;
const int MASK_3 = 7 << 9;
const int MASK_4 = 7 << 12;
const int MASK_5 = 7 << 15;
const int MASK_6 = 7 << 18;
const int MASK_7 = 7 << 21;

struct node {
    int val;
    char op;
    int parent;
} tree[40320];

unsigned char hash[0x3FFFF] = {0};
int tree_tail;
FILE *fin, *fout;

int operate(int p, int op) {
    int tmp[8];

    tmp[0] = p & MASK_0;
    tmp[1] = (p & MASK_1) >> 3;
    tmp[2] = (p & MASK_2) >> 6;
    tmp[3] = (p & MASK_3) >> 9;
    tmp[4] = (p & MASK_4) >> 12;
    tmp[5] = (p & MASK_5) >> 15;
    tmp[6] = (p & MASK_6) >> 18;
    tmp[7] = (p & MASK_7) >> 21;

    switch (op) {
        case 0:
            p = tmp[7] | (tmp[6] << 3) | (tmp[5] << 6) | (tmp[4] << 9) | (tmp[3] << 12) | (tmp[2] << 15) | (tmp[1] << 18) | (tmp[0] << 21);
            break;
        case 1:
            p = tmp[3] | (tmp[0] << 3) | (tmp[1] << 6) | (tmp[2] << 9) | (tmp[5] << 12) | (tmp[6] << 15) | (tmp[7] << 18) | (tmp[4] << 21);
            break;
        case 2:
            p = tmp[0] | (tmp[6] << 3) | (tmp[1] << 6) | (tmp[3] << 9) | (tmp[4] << 12) | (tmp[2] << 15) | (tmp[5] << 18) | (tmp[7] << 21);
            break;
        default:
            break;
    }

    return p;
}

void hash_set(int p) {
    int idx, pos;

    idx = p>>6;
    pos = (p>>3)&7;

    hash[idx] |= (1 << pos);
}

int hash_is_set(int p) {
    int idx, pos;

    idx = p>>6;
    pos = (p>>3)&7;

    return hash[idx] & (1 << pos);
}

int printpath(int idx, int height) {
    int h;

    if (tree[idx].parent > 0) {
        h = printpath(tree[idx].parent, height+1);
        if (h % 60 == 0) {
            fprintf(fout, "\n");
        }
        fprintf(fout, "%c", tree[idx].op);

        return h+1;
    } else {
        fprintf(fout, "%d\n", height);
        fprintf(fout, "%c", tree[idx].op);
        return 1;
    }
}

int main(int argc, char** argv) {
    int target = 0;
    int init = 0;
    int d;
    int i;

    fin = fopen("msquare.in", "r");
    fout = fopen("msquare.out", "w");

    for (i = 0; i < 8; i++) {
        fscanf(fin, "%d", &d);
        target |= (d-1) << (3*i);
        init |= i << (3*i);
    }

    if (init == target) {
        fprintf(fout, "0\n\n");
        return 0;
    }

    tree[0].val = init;
    tree[0].parent = 0;
    tree_tail = 0;

    i = 0;
    while (i <= tree_tail) {
        d = operate(tree[i].val, 0);
        if (!hash_is_set(d)) {
            hash_set(d);
            tree_tail++;
            tree[tree_tail].val = d;
            tree[tree_tail].parent = i;
            tree[tree_tail].op = 'A';
            if (d == target) {
                break;
            }
        }

        d = operate(tree[i].val, 1);
        if (!hash_is_set(d)) {
            hash_set(d);
            tree_tail++;
            tree[tree_tail].val = d;
            tree[tree_tail].parent = i;
            tree[tree_tail].op = 'B';
            if (d == target) {
                break;
            }
        }

        d = operate(tree[i].val, 2);
        if (!hash_is_set(d)) {
            hash_set(d);
            tree_tail++;
            tree[tree_tail].val = d;
            tree[tree_tail].parent = i;
            tree[tree_tail].op = 'C';
            if (d == target) {
                break;
            }
        }

        i++;
    }

    if (i < tree_tail) {
        printpath(tree_tail, 1);
        fprintf(fout, "\n");
    }

    return 0;
}

