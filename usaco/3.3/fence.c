/*
ID: baikaiz1
PROG: fence
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file fence.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int v;
    struct node *next;
} node;

node adj[500];
int path[1024];
int path_idx;
int stack[1024];
int stack_idx;

void find_path(int i) {
    node *min_neibor = NULL;
    node *p = adj[i].next;
    int next;

    while (p != NULL) {
        if (min_neibor == NULL || min_neibor->v > p->v) {
            min_neibor = p;
        }
        p = p->next;
    }

    if (min_neibor == NULL) {
        path[path_idx++] = i;
        if (stack_idx > 0) {
            find_path(stack[--stack_idx]);
        }
        return;
    }

    next = min_neibor->v;
    stack[stack_idx++] = i;

    p = &adj[i];
    while (p->next != min_neibor) {
        p = p->next;
    }
    p->next = min_neibor->next;
    free(min_neibor);

    p = &adj[next];
    while (p->next->v != i) {
        p = p->next;
    }
    min_neibor = p->next;
    p->next = min_neibor->next;
    free(min_neibor);

    find_path(next);
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("fence.in", "r");
    fout = fopen("fence.out", "w");
    int n_edges;
    int start, end;
    int i;
    node *tmp_node;
    int current;

    fscanf(fin, "%d", &n_edges);
    for (i = 0; i < n_edges; i++) {
        fscanf(fin, "%d %d", &start, &end);
        start -= 1;
        end -= 1;

        tmp_node = (node *)malloc(sizeof(node));
        tmp_node->v = start;
        tmp_node->next = adj[end].next;
        adj[end].next = tmp_node;
        (adj[end].v)++;

        tmp_node = (node *)malloc(sizeof(node));
        tmp_node->v = end;
        tmp_node->next = adj[start].next;
        adj[start].next = tmp_node;
        (adj[start].v)++;
    }

    current = -1;
    for (i = 0; i < 500; i++) {
        if (adj[i].v % 2 == 1) {
            current = i;
            break;
        }

        if (adj[i].v > 0 && current < 0) {
            current = i;
        }
    }

    find_path(current);

    for (i = path_idx-1; i >= 0; i--) {
        fprintf(fout, "%d\n", path[i]+1);
    }

    return 0;
}

