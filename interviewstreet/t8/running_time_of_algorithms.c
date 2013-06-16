/**
 * Description
 *
 * @file running_time_of_algorithms.c
 * @date 2013-06-17 01:20:22
 * @author ligang <ZhongLigang@gmail.com>
 * @copyright (c) 2013 ZhongLigang
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int size;
    int *ar;
    int i, j, el;
    int ops = 0;

    scanf("%d", &size);
    ar = (int *)malloc(sizeof(int)*size);
    for (i = 0; i < size; i++) {
        scanf("%d", ar+i);
    }

    for (i = 1; i < size; i++) {
        el = *(ar+i);
        for (j = i - 1; j >= 0; j--) {
            if (*(ar+j) > el) {
                ops++;
            }
        }
    }

    printf("%d", ops);
}

/* vim: set ts=4 sw=4 sts=4 tw=100 et: */
