/*
ID: baikaiz1
PROG: rect1
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file rect1.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int x1;
    int y1;
    int x2;
    int y2;
    int color;
} rect_t;

rect_t rects[1000];
int colors[2500];
int color_sum;
int n_rect;

void split_rect(rect_t rect, rect_t filter, rect_t *splited_rects, int *rect_num) {
    rect_t *p = splited_rects;
    *rect_num = 0;
    if (filter.x1 <= rect.x1 && filter.x2 >= rect.x2 && filter.y1 <= rect.y1 && filter.y2 >= rect.y2) {
        return;
    } else if (filter.x2 <= rect.x1 || filter.x1 >= rect.x2
        || filter.y2 <= rect.y1 || filter.y1 >= rect.y2) {
        *rect_num = 1;
        *p = rect;
        return;
    } else if (filter.x1 <= rect.x1 && filter.x2 >= rect.x2) {
        if (filter.y2 < rect.y2) {
            (*rect_num)++;
            p->x1 = rect.x1;
            p->x2 = rect.x2;
            p->y1 = filter.y2;
            p->y2 = rect.y2;
            p->color = rect.color;
            p++;
        }

        if (filter.y1 > rect.y1) {
            (*rect_num)++;
            p->x1 = rect.x1;
            p->x2 = rect.x2;
            p->y1 = rect.y1;
            p->y2 = filter.y1;
            p->color = rect.color;
            p++;
        }
        return;
    } else if (filter.x1 <= rect.x1 && filter.x2 < rect.x2) {
        (*rect_num)++;
        p->x1 = filter.x2;
        p->x2 = rect.x2;
        p->y1 = rect.y1;
        p->y2 = rect.y2;
        p->color = rect.color;
        p++;

        if (filter.y2 < rect.y2) {
            (*rect_num)++;
            p->x1 = rect.x1;
            p->x2 = filter.x2;
            p->y1 = filter.y2;
            p->y2 = rect.y2;
            p->color = rect.color;
            p++;
        }

        if (filter.y1 > rect.y1) {
            (*rect_num)++;
            p->x1 = rect.x1;
            p->x2 = filter.x2;
            p->y1 = rect.y1;
            p->y2 = filter.y1;
            p->color = rect.color;
            p++;
        }

        return;
    } else if (filter.x1 > rect.x1 && filter.x2 >= rect.x2) {
        (*rect_num)++;
        p->x1 = rect.x1;
        p->x2 = filter.x1;
        p->y1 = rect.y1;
        p->y2 = rect.y2;
        p->color = rect.color;
        p++;

        if (filter.y2 < rect.y2) {
            (*rect_num)++;
            p->x1 = filter.x1;
            p->x2 = rect.x2;
            p->y1 = filter.y2;
            p->y2 = rect.y2;
            p->color = rect.color;
            p++;
        }

        if (filter.y1 > rect.y1) {
            (*rect_num)++;
            p->x1 = filter.x1;
            p->x2 = rect.x2;
            p->y1 = rect.y1;
            p->y2 = filter.y1;
            p->color = rect.color;
            p++;
        }

        return;
    } else {
        (*rect_num)++;
        p->x1 = rect.x1;
        p->x2 = filter.x1;
        p->y1 = rect.y1;
        p->y2 = rect.y2;
        p->color = rect.color;
        p++;

        (*rect_num)++;
        p->x1 = filter.x2;
        p->x2 = rect.x2;
        p->y1 = rect.y1;
        p->y2 = rect.y2;
        p->color = rect.color;
        p++;

        if (filter.y2 < rect.y2) {
            (*rect_num)++;
            p->x1 = filter.x1;
            p->x2 = filter.x2;
            p->y1 = filter.y2;
            p->y2 = rect.y2;
            p->color = rect.color;
            p++;
        }

        if (filter.y1 > rect.y1) {
            (*rect_num)++;
            p->x1 = filter.x1;
            p->x2 = filter.x2;
            p->y1 = rect.y1;
            p->y2 = filter.y1;
            p->color = rect.color;
            p++;
        }

        return;
    }
}

void put_in(rect_t rect, int pos) {
    if (pos == n_rect-1) {
        colors[rect.color - 1] += (rect.x2-rect.x1)*(rect.y2 - rect.y1);
        color_sum += (rect.x2-rect.x1)*(rect.y2 - rect.y1);
        return;
    }

    rect_t splited_rects[8];
    int rect_num, i;

    split_rect(rect, rects[pos + 1], splited_rects, &rect_num);
    for (i = 0; i < rect_num; i++) {
        put_in(splited_rects[i], pos+1);
    }
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("rect1.in", "r");
    fout = fopen("rect1.out", "w");
    int w, h;
    int i, j;

    fscanf(fin, "%d %d %d", &w, &h, &n_rect);
    for (i = 0; i < n_rect; i++) {
        fscanf(fin, "%d %d %d %d %d", &rects[i].x1, &rects[i].y1, &rects[i].x2, &rects[i].y2, &rects[i].color);
    }

    for (i = n_rect - 1; i >= 0; i--) {
        put_in(rects[i], i);
    }


    if (color_sum != w * h) {
        colors[0] += w * h - color_sum;
    }

    for (i = 0; i < 2500; i++) {
        if (colors[i] > 0) {
            fprintf(fout, "%d %d\n", i+1, colors[i]);
        }
    }

    return 0;
}

