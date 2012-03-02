/**
 * Copyright (c) 2012 Flatter World. All Rights Reserved
 * $Id$ 
 * 
 * @file main.cc
 * @author zhongligang <ligang@flatterworld.com>
 * @date 2012-03-02 21:24:38
 */

/**
 * 1/x + 1/y = 1/n!
 * x > 0 & y > 0, so x > n! & y > n!
 * -> y = n! + n!^2/(x - n!)
 *
 * so it's to find how many numbers that can be divided by n!^2
 */
#include <cstdlib>
#include <cstdio>

int primes[80000];
int primes_map[1000001] = {0}; // primes_map[i] = 1 means i is not prime, later, primes_map[i] = n, means there are n number i in the n!

int fill_primes(int n) {
    int i, j;

    for (i = 2; i <= n; i++) {
        if (primes_map[i] == 0) {
            for (j = i + i; j <= n; j += i) {
                primes_map[j] = 1;
            }
        }
    }

    j = 0;
    for (i = 2; i <= n; i++) {
        if (primes_map[i] == 0) {
            primes[j++] = i;
        }
    }

    return 0;
}

int main (int argc, char *argv[]) {
    int i, j, k, n, num;
    long long result;
    scanf("%d", &n);

    fill_primes(n + 1);

    result = 1;
    i = 0;
    while (primes[i] && primes[i] <= n) {
        num = primes[i++];
        for (j = num; j <= n; j += num) {
            k = j;
            while (k % num == 0) {
                k /= num;
                primes_map[num]++;
            }
        }

        if (primes_map[num] > 0) {
            result *= primes_map[num] + primes_map[num] + 1;
            if (result > 1000007) {
                result %= 1000007;
            }
        }
    }

    printf("%d\n", (int) result);
    return 0;
}
/* vim: set ts=4 sw=4 sts=4 tw=100 et: */
