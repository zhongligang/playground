/*
ID: baikaiz1
PROG: pprime
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file pprime.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

int primes[1000] = {2, 3, 0};
int prime_num = 2;

int is_prime(num) {
    int i;
    for (i = 0; i < prime_num && num > primes[i]; i++) {
        if (num % primes[i] == 0) {
            return 0;
        }
    }

    if (num < 3163) {
        primes[prime_num] = num;
        prime_num++;
    }

    return 1;
}

int is_reverse(i) {
    if (i < 10) {
        return 1;
    } else if (i < 100) {
        return i == 11;
    } else if (i < 1000) {
        return i/100 == i % 10;
    } else if (i < 10000) {
        return 0;
    } else if (i < 100000) {
        return i/10000 == i % 10
            && (i/1000%10==i%100/10);
    } else if (i < 1000000) {
        return 0;
    } else {
        return i/1000000 == i % 10
            && (i/100000%10==i%100/10)
            && (i/10000%10==i%1000/100);
    }
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("pprime.in", "r");
    fout = fopen("pprime.out", "w");

    int a, b, i, min, max;

    fscanf(fin, "%d %d", &a, &b);

    for (i = 5; i < 3163; i++) {
        is_prime(i);
    }

    if (b >= 10000000) {
        b = 9999999;
    }

    min = 6 * (a/6) + 6;
    max = 6 * (b/6) - 6;

    for (i = a; i < min; i++) {
        if (is_prime(i)) {
            if (is_reverse(i)) {
                fprintf(fout, "%d\n", i);
            }
        }
    }

    // step of 6
    for (i = min; i <= max; i++) {
        i+=1;
        if (is_reverse(i)) {
            if (is_prime(i)) {
                fprintf(fout, "%d\n", i);
            }
        }

        i+=4;
        if (is_reverse(i)) {
            if (is_prime(i)) {
                fprintf(fout, "%d\n", i);
            }
        }
    }

    for (i = max+6; i <= b; i++) {
        if (is_prime(i)) {
            if (is_reverse(i)) {
                fprintf(fout, "%d\n", i);
            }
        }
    }

    return 0;
}
