/*
ID: baikaiz1
PROG: fact4
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file fact4.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("fact4.in", "r");
    fout = fopen("fact4.out", "w");
    int n;
    int primes[2110] = {0};
    int primes_count[2110] = {0};
    int primes_len;
    int prime_idx;
    int prime;
    int i, r;

    fscanf(fin, "%d", &n);

    primes[0] = 2;
    primes_len = 1;

    for (i = 2; i <=n; i++) {
        r = i;
        for (prime_idx = 0; prime_idx < primes_len; prime_idx++) {
            prime = primes[prime_idx];
            while (r > 1 && r % prime == 0) {
                r /= prime;
                primes_count[prime_idx]++;
            }
        }

        if (r > 1) {
            primes_count[primes_len] = 1;
            primes[primes_len++] = r;
        }
    }

    if (primes_len >= 3) {
        if (primes_count[0] > primes_count[2]) {
            primes_count[0] -= primes_count[2];
            primes_count[2] = 0;
        } else {
            primes_count[2] -= primes_count[0];
            primes_count[0] = 0;
        }
    }

    r = 1;
    for (prime_idx = 0; prime_idx < primes_len; prime_idx++) {
        prime = primes[prime_idx];
        for (i = 0; i < primes_count[prime_idx]; i++) {
            r *= prime;
            r %= 10;
        }
    }

    fprintf(fout, "%d\n", r);

    return 0;
}

