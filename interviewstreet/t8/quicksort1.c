/**
 * Description
 *
 * @file quicksort1.c
 * @date 2013-06-17 01:32:27
 * @author ligang <ZhongLigang@gmail.com>
 * @copyright (c) 2013 ZhongLigang
 */

#include <stdio.h>
#include <stdlib.h>

/* Head ends here */
void partition(int ar_size, int *ar) {
    if (ar_size == 0) {
        return;
    }

    int el = ar[0];
    int i;
    int to_print = 0;

    for (i = 1; i < ar_size; i++) {
        if (ar[i] <= el) {
            to_print++;
            if (to_print != ar_size) {
                printf("%d ", ar[i]);
            } else {
                printf("%d\n", ar[i]);
            }
        }
    }

    to_print++;
    if (to_print != ar_size) {
        printf("%d ", el);
    } else {
        printf("%d\n", el);
    }
    for (i = 1; i < ar_size; i++) {
        if (ar[i] > el) {
            to_print++;
            if (to_print != ar_size) {
                printf("%d ", ar[i]);
            } else {
                printf("%d\n", ar[i]);
            }
        }
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

    partition(_ar_size, _ar);
   
   return 0;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 et: */
