/*
ID: baikaiz1
PROG: fence9
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file fence9.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int gcd(int a, int b) {
    int tmp;

    if (a < b) {
        tmp = a;
        a = b;
        b = tmp;    
    }

    return b != 0 ? gcd(b, a % b) : a;
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("fence9.in", "r");
#ifdef DEBUG
    fout = stdout;
#else
    fout = fopen("fence9.out", "w");
#endif

    int x1, y1, x2;
    int n = 0;

    fscanf(fin, "%d %d %d", &x1, &y1, &x2);

    /* Pick's theorem
     * s = i + b/2 - 1
     * where s is area
     * i is points inside,
     * b is points on edge
     */
    ///* {{ Solution by Pick's theorem
    int s;
    int b1, b2, b3;
    if (x1 > x2) {
        b2 = gcd(x1-x2, y1)+1;
    } else {
        b2 = gcd(x2-x1, y1)+1;
    }
    s = y1*x2;
    b1 = x2+1;
    b3 = gcd(x1, y1)+1;
    n = (s + 5 - b1 - b2 - b3)/2;
    // }}} */

    /* {{{ Solution by traverse
    int y;
    double xl, xr, ixl, ixr;
    for (y = 1; y < y1; y++) {
        xl = (double)x1*y/y1;
        if (x1 >= x2) {
            xr = x2+(double)(x1-x2)*y/y1;
        } else {
            xr = x2-(double)(x2-x1)*y/y1;
        }

        ixl = ceil(xl);
        ixr = floor(xr);

        if (ixr >= ixl) {
            n += ixr - ixl + 1;
            n -= ixl-xl<1e-9;
            n -= xr-ixr<1e-9;
        }
    }
    // }}} */

    fprintf(fout, "%d\n", n);

    return 0;
}

