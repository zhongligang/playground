/**
 * Description
 *
 * @file flowers.c
 * @date 2013-06-18 00:26:41
 * @author ligang <ZhongLigang@gmail.com>
 * @copyright (c) 2013 ZhongLigang
 */

#include <stdlib.h>
#include <stdio.h>

int cmp_int(const void *a, const void *b) {
    return *(int *)a - *(int *)b > 0 ? -1 : 1;
}

int main(int argc, char **argv) {
    int num_flowers;
    int num_persons;
    int *flowers;
    int i;
    int person_idx, multi;
    int total;

    scanf("%d %d", &num_flowers, &num_persons);
    flowers = (int *)malloc(sizeof(int)*num_flowers);
    for (i = 0; i < num_flowers; i++) {
        scanf("%d", flowers+i);
    }

    qsort(flowers, num_flowers, sizeof(int), cmp_int);

    multi = 1;
    person_idx = 0;
    total = 0;
    for (i = 0; i < num_flowers; i++) {
        total += multi * flowers[i];
        person_idx++;
        if (person_idx == num_persons) {
            person_idx = 0;
            multi++;
        }
    }

    printf("%d\n", total);

    free(flowers);
}

/* vim: set ts=4 sw=4 sts=4 tw=100 et: */
