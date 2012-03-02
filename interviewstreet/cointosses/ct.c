/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$ 
 * 
 * @file ct.c
 * @author zhongligang <ZhongLigang@gmail.com>
 * @date 2012-01-31 03:05:47
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUM_LEN 303

int
main(int argc, char *argv[])
{
    int t, m, n, i, j, k, a_len, b_len;
    char a[NUM_LEN], b[NUM_LEN], plus, minus;

    scanf("%d", &t);
    for (i = 0; i < t; i++) {
        scanf("%d %d", &n, &m);

        if (n == m) {
            printf("0.00\n");
        } else {
            bzero(a, NUM_LEN);

            a[0] = 1;
            a_len = 1;
            for (j = 0; j < m + 1; j++) {
                plus = 0;
                for (k = 0; k < a_len; k++) {
                    a[k] += a[k] + plus;
                    plus = 0;
                    if (a[k] >= 10) {
                        a[k] -= 10;
                        plus = 1;
                    }
                }
                if (plus) {
                    a[a_len] += 1;
                    a_len++;
                }
            }

            memcpy(b, a, NUM_LEN);
            b_len = a_len;
            for (; j < n + 1; j++) {
                plus = 0;
                for (k = 0; k < b_len; k++) {
                    b[k] += b[k] + plus;
                    plus = 0;
                    if (b[k] >= 10) {
                        b[k] -= 10;
                        plus = 1;
                    }
                }
                if (plus) {
                    b[b_len] += 1;
                    b_len++;
                }
            }

            minus = 0;
            for (j = 0; j < b_len; j++) {
                b[j] -= a[j] + minus;
                minus = 0;
                if (b[j] < 0) {
                    b[j] += 10;
                    minus = 1;
                }
            }

            while (!b[b_len - 1]) {
                b_len--;
            }

            while (--b_len >= 0) {
                printf("%d", b[b_len]);
            }
            printf(".00\n");
        }
    }
}

/* vim: set ts=4 sw=4 sts=4 tw=100 et: */
