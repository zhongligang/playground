/*
ID: baikaiz1
PROG: preface
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file preface.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

int counts1[] = {0, 1, 3, 6, 7, 7, 8, 10, 13, 14};
int counts5[] = {0, 0, 0, 0, 1, 2, 3, 4, 5, 5};
int counts1_[] = {0, 1, 2, 3, 1, 0, 1, 2, 3, 1};
int counts5_[] = {0, 0, 0, 0, 1, 1, 1, 1, 1, 0};

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("preface.in", "r");
    fout = fopen("preface.out", "w");
    int n;
    int r, num;
    int i = 0,
        v = 0,
        x = 0,
        l = 0,
        c = 0,
        d = 0,
        m = 0;

    fscanf(fin, "%d", &n);

    r = n % 10;
    num = n / 10;

    i = num * counts1[9] + counts1[r];
    v = num * counts5[9] + counts5[r];
    x = (num + (r == 9));

    r = n / 10 % 10;
    num = n / 10 / 10;
    x += num * counts1[9]*10 + (r>0?counts1[r-1]*10:0) + n%10*counts1_[r]+counts1_[r];
    l = num * counts5[9]*10 + (r>0?counts5[r-1]*10:0) + n%10*counts5_[r]+counts5_[r];
    c = num*10 + (r == 9?(n%10+1):0);

    r = n / 100 % 10;
    num = n / 100 / 10;
    c += num * counts1[9]*100 + (r>0?counts1[r-1]*100:0) + n%100*counts1_[r]+counts1_[r];
    d = num * counts5[9]*100 + (r>0?counts5[r-1]*100:0) + n%100*counts5_[r]+counts5_[r];
    m = num*100 + (r==9?(n%100+1):0);

    r = n / 1000 % 10;
    m += (r>0?counts1[r-1]*1000:0) + n%1000*counts1_[r]+counts1_[r];

    if (i > 0) {
        fprintf(fout, "I %d\n", i);
    }

    if (v > 0) {
        fprintf(fout, "V %d\n", v);
    }

    if (x > 0) {
        fprintf(fout, "X %d\n", x);
    }

    if (l > 0) {
        fprintf(fout, "L %d\n", l);
    }

    if (c > 0) {
        fprintf(fout, "C %d\n", c);
    }

    if (d > 0) {
        fprintf(fout, "D %d\n", d);
    }

    if (m > 0) {
        fprintf(fout, "M %d\n", m);
    }

    return 0;
}

