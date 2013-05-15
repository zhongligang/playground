/*
ID: baikaiz1
PROG: butter
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file butter.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#define INFINITY 0x7FFFFFFF

typedef struct {
    int id;
    int v;
} heap_node_t;

typedef struct {
    heap_node_t *nodes;
    int size;
    int tail;
} heap_t;

heap_t* heap_create(int size) {
    heap_t *heap;

    heap = (heap_t*)malloc(sizeof(heap_t));

    heap->nodes = (heap_node_t*)malloc(size*sizeof(heap_node_t));
    heap->size = size;
    heap->tail = 0;

    return heap;
}

void heap_free(heap_t *heap) {
    free(heap->nodes);
    free(heap);
}

int heap_add(heap_t *heap, int id, int v) {
    int idx = heap->tail;
    int p;
    int tmp;
    heap_node_t *nodes;

    if (idx >= heap->size) {
        return 0;
    }

    nodes = heap->nodes;
    nodes[idx].id = id;
    nodes[idx].v = v;
    (heap->tail)++;

    while (idx > 0) {
        p = (idx-1)>>1;
        if (nodes[idx].v < nodes[p].v) {
            tmp = nodes[p].v;
            nodes[p].v = nodes[idx].v;
            nodes[idx].v = tmp;

            tmp = nodes[p].id;
            nodes[p].id = nodes[idx].id;
            nodes[idx].id = tmp;
        } else {
            break;
        }
    }

    return 1;
}

heap_node_t heap_pop(heap_t *heap) {
    int idx;
    int left;
    int right;
    int tail;
    int tmp;
    heap_node_t ret;
    heap_node_t *nodes;

    if (heap->tail == 0) {
        ret.id = -1;
        return ret;
    }

    nodes = heap->nodes;
    ret = nodes[0];

    (heap->tail)--;
    tail = heap->tail;
    nodes[0] = nodes[tail];

    idx = 0; 
    left = idx<<1+1;
    right = left+1;
    while (left < tail) {
        if (nodes[idx].v > nodes[left].v || nodes[idx].v > nodes[right].v) {
            if (nodes[left].v > nodes[right].v) {
                tmp = nodes[right].v;
                nodes[right].v = nodes[idx].v;
                nodes[idx].v = tmp;

                tmp = nodes[right].id;
                nodes[right].id = nodes[idx].id;
                nodes[idx].id = tmp;
                idx = right;
            } else {
                tmp = nodes[left].v;
                nodes[left].v = nodes[idx].v;
                nodes[idx].v = tmp;

                tmp = nodes[left].id;
                nodes[left].id = nodes[idx].id;
                nodes[idx].id = tmp;
                idx = left;
            }
        } else {
            break;
        }

        left = idx<<1+1;
        right = left+1;
    }

    return ret;
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("butter.in", "r");
    fout = fopen("butter.out", "w");

    int n_cows, n_points, n_path;
    int pos_cows[800];
    int edge[800][800];
    int i, j, k;
    int result, sum, to_visit;
    char visited[800];
    int d[800];
    int neibour[800][800];
    int neibour_idx[800];

    int tmp;
    int heap[800];
    int heap_idx[800];
    int heap_tail;
    int heap_me, heap_left, heap_right, heap_parent;

    fscanf(fin, "%d %d %d", &n_cows, &n_points, &n_path);

    bzero(pos_cows, sizeof(pos_cows));
    for (i = 0; i < n_cows; i++) {
        fscanf(fin, "%d", &j);
        pos_cows[j-1]++;
    }

    for (i = 0; i < n_points; i++) {
        edge[i][i] = 0;
        neibour[i][i] = -1;
        for (j = i+1; j < n_points; j++) {
            edge[i][j] = INFINITY;
            edge[j][i] = INFINITY;
            neibour[i][j] = -1;
            neibour[j][i] = -1;
        }
    }
    bzero(neibour_idx, sizeof(neibour_idx));
    for (i = 0; i < n_path; i++) {
        fscanf(fin, "%d %d %d", &j, &k, d);
        j--;
        k--;
        edge[j][k] = edge[k][j] = *d;
        neibour[j][neibour_idx[j]++] = k;
        neibour[k][neibour_idx[k]++] = j;
    }

    result = INFINITY;
    for (i = 0; i < n_points; i++) {
        bzero(visited, sizeof(visited));
        for (j = 0; j < n_points; j++) {
            d[j] = INFINITY;
            heap_idx[j] = -1;
        }
        d[i] = 0;

        heap[0] = i;
        heap_idx[i] = 0;
        heap_tail = 1;
        while (heap_tail > 0) {
            to_visit = heap[0];
            visited[to_visit] = 1;
            heap_idx[to_visit] = -1;

            heap_tail--;
            if (heap_tail > 0) {
                heap[0] = heap[heap_tail];
                heap_me = 0;
                heap_idx[heap[heap_me]] = heap_me;
                heap_left = (heap_me<<1)+1;
                heap_right = (heap_me<<1)+2;
                while (heap_left < heap_tail) {
                    // the right is the same as me if right exceed the tail
                    if (d[heap[heap_me]] > d[heap[heap_left]] || d[heap[heap_me]] > d[heap[heap_right]]) {
                        if (d[heap[heap_left]] > d[heap[heap_right]]) {
                            tmp = heap[heap_me];
                            heap[heap_me] =  heap[heap_right];
                            heap[heap_right] = tmp;

                            heap_idx[heap[heap_me]] = heap_me;
                            heap_idx[heap[heap_right]] = heap_right;

                            heap_me = heap_right;
                            heap_left = (heap_me<<1)+1;
                            heap_right = (heap_me<<1)+2;
                        } else {
                            tmp = heap[heap_me];
                            heap[heap_me] =  heap[heap_left];
                            heap[heap_left] = tmp;

                            heap_idx[heap[heap_me]] = heap_me;
                            heap_idx[heap[heap_left]] = heap_left;

                            heap_me = heap_left;
                            heap_left = (heap_me<<1)+1;
                            heap_right = (heap_me<<1)+2;
                        }
                    } else {
                        break;
                    }
                }
            }

            j = 0;
            k = neibour[to_visit][j];
            while (k >= 0) {
                if (d[to_visit]+edge[to_visit][k] < d[k]) {
                    d[k] = d[to_visit] + edge[to_visit][k];
                    if (heap_idx[k] == -1) {
                        heap[heap_tail] = k;
                        heap_idx[k] = heap_tail;
                        heap_tail++;
                    }

                    heap_me = heap_idx[k];
                    while (heap_me > 0) {
                        heap_parent = (heap_me-1)>>1;
                        if (d[heap[heap_me]] < d[heap[heap_parent]]) {
                            tmp = heap[heap_me];
                            heap[heap_me] = heap[heap_parent];
                            heap[heap_parent] = tmp;

                            heap_idx[heap[heap_me]] = heap_me;
                            heap_idx[heap[heap_parent]] = heap_parent;

                            heap_me = heap_parent;
                        } else {
                            break;
                        }
                    }
                }
                k = neibour[to_visit][++j];
            }
        }

        sum = 0;
        for (j = 0; j < n_points; j++) {
            sum += d[j]*pos_cows[j];
        }
        if (sum < result) {
            result = sum;
        }
    }

    fprintf(fout, "%d\n", result);

    return 0;
}

