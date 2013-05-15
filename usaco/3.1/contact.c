/*
ID: baikaiz1
PROG: contact
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file contact.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

#define MASK 0xFFF

typedef struct {
    int v;
    int c;
} v_t;

const int mask[] = {
    0,
    0x1,
    0x3,
    0x7,
    0xF,
    0x1F,
    0x3F,
    0x7F,
    0xFF,
    0x1FF,
    0x3FF,
    0x7FF,
    0xFFF,
};
const int prefix[] = {
    0x1,
    0x2,
    0x4,
    0x8,
    0x10,
    0x20,
    0x40,
    0x80,
    0x100,
    0x200,
    0x400,
    0x800,
    0x1000,
};

int cmp_v_t(const void *a, const void *b) {
    if (((v_t*)a)->c < ((v_t*)b)->c) {
        return 1;
    } else if (((v_t*)a)->c > ((v_t*)b)->c) {
        return -1;
    } else {
        return ((v_t*)a)->v > ((v_t*)b)->v ? 1 : -1;
    }
}

void print_seq(FILE *fout, int v) {
    int i;

    for (i = 12; !(prefix[i]&v); i--) {}
    while (i > 0) {
        fprintf(fout, "%d", (v&prefix[i-1])>0?1:0);
        i--;
    }
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("contact.in", "r");
    fout = fopen("contact.out", "w");
    v_t count[0x2001];
    int a, b, n;
    int current = 0;
    int i;
    int v;
    int n_bits;
    int m;
    int j;
    char c;

    for (i = 0; i < 0x2000; i++) {
        count[i].v = i;
        count[i].c = 0;
    }

    fscanf(fin, "%d %d %d", &a, &b, &n);

    v = 0;
    n_bits = 0;
    while ((c = fgetc(fin)) != EOF) {
        if (c != '\n') {
            n_bits++;
            c -= '0';
            v = (v << 1) | c;
            m = n_bits>=b?b:n_bits;
            for (i = a; i <= m; i++) {
                count[v&mask[i]|prefix[i]].c++;
            }
        }
    }

    qsort(count, 1 << (b+1), sizeof(v_t), cmp_v_t);

    m = 1 << (b+1);
    i = 0;
    v = 0;
    while (v++ < n) {
        if (count[i].c == 0) {
            break;
        }

        fprintf(fout, "%d\n", count[i].c);
        current = count[i].c;

        print_seq(fout, count[i].v);
        j = 1;
        i++;
        while (count[i].c == current) {
            fprintf(fout, j % 6 == 0 ? "\n" : " ");
            print_seq(fout, count[i].v);
            i++;
            j++;
        }

        fprintf(fout, "\n");
    }

    return 0;
}

