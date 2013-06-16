/**
 * Description
 *
 * @file quicksort.c
 * @date 2013-06-17 01:46:44
 * @author ligang <ZhongLigang@gmail.com>
 * @copyright (c) 2013 ZhongLigang
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <strings.h>

/* Head ends here */
int quickSortPartition(int ar_size, int *ar) {
    assert(ar_size > 0);

    int *new = malloc(sizeof(int)*ar_size);
    int el = ar[0];
    int i;
    int p = 0;
    int ret;

    for (i = 1; i < ar_size; i++) {
        if (ar[i] < el) {
            *(new+p++) = ar[i];
        }
    }

    ret = p;
    *(new+p++) = el;

    for (i = 1; i < ar_size; i++) {
        if (ar[i] >= el) {
            *(new+p++) = ar[i];
        }
    }

    bcopy(new, ar, sizeof(int)*ar_size);
    free(new);

    return ret;

    /* {{{
    int el = ar[0], tmp;
    int *head = ar, *tail = ar + ar_size - 1;

    while (head < tail) {
        while (*tail >= el && tail > head) {tail--;}
        if (tail != head) {
            tmp = *tail;
            *tail = *head;
            *head = tmp;
            head++;
        }
        while (*head <= el && tail > head) {head++;}
        if (tail != head) {
            tmp = *tail;
            *tail = *head;
            *head = tmp;
            tail--;
        }
    }

    return head - ar;
    // }}} */
}

void quickSort(int ar_size, int *ar) {
    int mid, tmp, i;

    if (ar_size >= 2) {
        mid = quickSortPartition(ar_size, ar);
        if (mid > 0) {
            quickSort(mid, ar);
        }
        if (mid < ar_size - 1) {
            quickSort(ar_size-mid-1, ar+mid+1);
        }
        for (i = 0; i < ar_size - 1; i++) {
            printf("%d ", ar[i]);
        }
        printf("%d\n", ar[i]);
    }
}

/* Tail starts here */
int main(void) {
    int _ar_size;
    scanf("%d", &_ar_size);

    int _ar[_ar_size], _ar_i;
    for(_ar_i = 0; _ar_i < _ar_size; _ar_i++) { 
        scanf("%d", &_ar[_ar_i]); 
    }

    quickSort(_ar_size, _ar);

    return 0;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 et: */
