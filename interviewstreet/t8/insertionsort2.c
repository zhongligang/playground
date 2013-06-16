/**
 * Description
 *
 * @file insertionsort2.c
 * @date 2013-06-17 01:08:45
 * @author ligang <ZhongLigang@gmail.com>
 * @copyright (c) 2013 ZhongLigang
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

/* Head ends here */
void insertionSortEl(int total_size, int ar_size, int *ar) {
    int i, el;

    if (ar_size == 0) {
        return;
    }

    el = ar[ar_size - 1];

    for (i = ar_size - 2; i >= 0; i--) {
        if (ar[i] > el) {
            ar[i + 1] = ar[i];
        } else {
            ar[i + 1] = el;
            break;
        }
    }

    if (i == -1) {
        ar[0] = el;
    }

    for (i = 0; i < total_size - 1; i++) {
        printf("%d ", ar[i]);
    }
    printf("%d\n", ar[i]);
}

void insertionSort(int ar_size, int *ar) {
    int i;

    for (i = 2; i <= ar_size; i++) {
        insertionSortEl(ar_size, i, ar);
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

    insertionSort(_ar_size, _ar);
          
    return 0;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 et: */
