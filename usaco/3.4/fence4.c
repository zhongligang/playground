/*
ID: baikaiz1
PROG: fence4
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file fence4.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int x;
    int y;
} point_t;

typedef struct {
    double x;
    double y;
} float_point_t;

point_t points[201];
point_t observer;
int n_points;

int strict_intersect(point_t *p1, point_t *p2, point_t *p3, point_t *p4) {
    int x = p2->x - p1->x,
        y = p2->y - p1->y,
        x1 = p3->x - p1->x,
        y1 = p3->y - p1->y,
        x2 = p4->x - p1->x,
        y2 = p4->y - p1->y,
        _x = p4->x - p3->x,
        _y = p4->y - p3->y,
        _x1 = p1->x - p3->x,
        _y1 = p1->y - p3->y,
        _x2 = p2->x - p3->x,
        _y2 = p2->y - p3->y;


    return ((x*y1-y*x1)>0&&(x*y2-y*x2)<0||(x*y1-y*x1)<0&&(x*y2-y*x2)>0)
        && ((_x*_y1-_y*_x1)>0&&(_x*_y2-_y*_x2)<0||(_x*_y1-_y*_x1)<0&&(_x*_y2-_y*_x2)>0) > 0;
}

int double_strict_intersect(float_point_t *p1, float_point_t *p2, float_point_t *p3, float_point_t *p4) {
    double x = p2->x - p1->x,
        y = p2->y - p1->y,
        x1 = p3->x - p1->x,
        y1 = p3->y - p1->y,
        x2 = p4->x - p1->x,
        y2 = p4->y - p1->y,
        _x = p4->x - p3->x,
        _y = p4->y - p3->y,
        _x1 = p1->x - p3->x,
        _y1 = p1->y - p3->y,
        _x2 = p2->x - p3->x,
        _y2 = p2->y - p3->y;


    return ((x*y1-y*x1)>=0&&(x*y2-y*x2)<=0||(x*y1-y*x1)<=0&&(x*y2-y*x2)>=0)
        && ((_x*_y1-_y*_x1)>=0&&(_x*_y2-_y*_x2)<=0||(_x*_y1-_y*_x1)<=0&&(_x*_y2-_y*_x2)>=0) > 0;
}

int is_valid() {
    int i, last_point, j;

    last_point = n_points - 2;
    for (i = 0; i < last_point; i++) {
        for (j = i + 2; j < n_points; j++) {
            if (i == 0 && j == n_points - 1) {
                continue;
            }
            if (strict_intersect(points+i, points+i+1, points+j, points+j+1)) {
                return 0;
            }
        }
    }

    return 1;
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("fence4.in", "r");
#ifdef DEBUG
    fout = stdout;
#else
    fout = fopen("fence4.out", "w");
#endif

    int i, j;
    float_point_t p1, p2, seg_p, ob, dp1, dp2;
    double dx, dy;
    int see_seg;
    int can_see[200] = {0};
    int see_count = 0;
    int segs = 100;
    int seg_i;
    int blocked;

    fscanf(fin, "%d", &n_points);
    fscanf(fin, "%d %d", &observer.x, &observer.y);
    for (i = 0; i < n_points; i++) {
        fscanf(fin, "%d %d", &points[i].x, &points[i].y);
    }
    points[i] = points[0];

    if (is_valid()) {
        ob.x = observer.x;
        ob.y = observer.y;
        for (i = 0; i < n_points; i++) {
            p1.x = points[i].x;
            p1.y = points[i].y;
            p2.x = points[i+1].x;
            p2.y = points[i+1].y;
            dx = (p2.x-p1.x)/segs;
            dy = (p2.y-p1.y)/segs;
            seg_p = p1;
            see_seg = 0;
            for (seg_i = 0; seg_i <= segs; seg_i++) {
                if (seg_i == 0) {
                    seg_p.x += dx/10000;
                    seg_p.y += dy/10000;
                } else if (seg_i == segs) {
                    seg_p.x -= dx/5000;
                    seg_p.y -= dy/5000;
                }
                blocked = 0;
                for (j = 0; j < n_points; j++) {
                    if (j == i) {
                        continue;
                    }
                    dp1.x = points[j].x;
                    dp1.y = points[j].y;
                    dp2.x = points[j+1].x;
                    dp2.y = points[j+1].y;

                    if (double_strict_intersect(&ob, &seg_p, &dp1, &dp2)) {
                        blocked = 1;
                        break;
                    }
                }

                if (!blocked) {
                    see_seg = 1;
                    break;
                }

                seg_p.x += dx;
                seg_p.y += dy;
            }

            if (see_seg) {
                if (can_see[i] == 0) {
                    can_see[i] = 1;
                    see_count++;
                }
            }
        }

        fprintf(fout, "%d\n", see_count);
        for (i = 0; i < n_points-2; i++) {
            if (can_see[i]) {
                fprintf(fout, "%d %d %d %d\n", points[i].x, points[i].y, points[i+1].x, points[i+1].y);
            }
        }
        if (can_see[n_points-1]) {
            fprintf(fout, "%d %d %d %d\n", points[0].x, points[0].y, points[n_points-1].x, points[n_points-1].y);
        }
        if (can_see[n_points-2]) {
            fprintf(fout, "%d %d %d %d\n", points[n_points-2].x, points[n_points-2].y, points[n_points-1].x, points[n_points-1].y);
        }
    } else {
        fprintf(fout, "NOFENCE\n");
    }

    return 0;
}

