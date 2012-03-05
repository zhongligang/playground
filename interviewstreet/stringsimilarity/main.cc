/**
 * Copyright (c) 2012 Flatter World. All Rights Reserved
 * $Id$ 
 * 
 * @file main.cc
 * @author zhongligang <ligang@flatterworld.com>
 * @date 2012-03-04 15:00:56
 */
/**
 * Extend KMP(Z-algorithm);
 */

#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_LEN = 100000;

int main(int argc, char *argv[]) {
    char s[MAX_LEN+1];
    int z[MAX_LEN], max, max_idx;
    int t, s_len, i, j, k, result;

    scanf("%d", &t);
    while (t--) {
        scanf("%s", s);

        s_len = strlen(s);
        bzero(z, sizeof(int) * s_len);

        result = s_len;
        z[0] = 0;
        max_idx = 0;
        max = -1;
        for (i = 1; i < s_len; i++) {
            if (max < i) {
                j = i;
                k = 0;
                while (j < s_len && s[j] == s[k]) {
                    j++;
                    k++;
                }

                z[i] = k;
                max_idx = i;
                max = i + z[i] -1;
            } else {
                k = i - max_idx;
                j = i;
                if (z[k] + i - 1 >= max) {
                    j = max + 1;
                    k = j - i;
                    while (j < s_len && s[k] == s[j]) {
                        j++;
                        k++;
                    }

                    z[i] = k;
                    max_idx = i;
                    max = z[i] + i - 1;
                } else {
                    z[i] = z[k];
                }
            }
            result += z[i];
        }

        printf("%d\n", result);
    }

    return 0;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 et: */
