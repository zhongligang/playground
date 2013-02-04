/*
ID: baikaiz1
LANG: C
TASK: ariprog
*/
/**
 * Copyright (c) 2011 ZhongLigang. All Rights Reserved
 * $Id$ 
 * 
 * @file ariprog.c
 * @author zhongligang <ZhongLigang@gmail.com>
 * @date 2011-11-30 22:03:14
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct result {int a,b;} result;

int cmp_result(const void *a, const void *b)
{
    int t = ((result *)a)->b - ((result *)b)->b;
    if (t)
    {
        return t;
    } else {
        return ((result *)a)->a - ((result *)b)->a;
    }
}

int cmp_int(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int main(int argc, char *argv[])
{
    FILE *fin, *fout; 
    int m, n, i, j, k, l, b, x, y,
        max, flag, nsol,
        a[31626],
        set[31626], nset;
    char map[125001] = {0};
    result sol[10001];

    fin = fopen("ariprog.in", "r");
    fout = fopen("ariprog.out", "w");

    fscanf(fin, "%d %d", &n, &m);

    b = 0;
    for (i = 0; i <= m; i++)
    {
        for (j = i; j <= m; j++)
        {
            a[b++] = i*i + j*j;
        }
    }

    qsort(a, b, sizeof(int), cmp_int);
    set[0] = l = a[0];
    nset = 1;
    for (i = 1; i < b; i++)
    {
        if (a[i] != l)
        {
            set[nset++] = a[i];
            l = a[i];
        }
    }

    for (i = 0; i < nset; i++)
    {
        map[set[i]] = 1;
    }

    max = set[nset-1];
    nsol = 0;
    for (i = 0; i < nset; i++)
    {
        for (j = i + 1; j < nset; j++)
        {
            x = set[i];
            y = set[j] - set[i];
            if (x + y*(n - 1) <= max)
            {
                flag = 1;
                for (k = 2; k < n; k++)
                {
                    if (!map[x + k*y])
                    {
                        flag = 0;
                        break;
                    }
                }
                if (flag)
                {
                    sol[nsol].a = x;
                    sol[nsol].b = y;
                    nsol++;
                }
            }
        }
    }

    qsort(sol, nsol, sizeof(result), cmp_result);
    for (i = 0; i < nsol; i++)
    {
        fprintf(fout, "%d %d\n", sol[i].a, sol[i].b);
    }
    if (!nsol)
    {
        fprintf(fout, "NONE\n");
    }

    fclose(fin);
    fclose(fout);

    return 0;
}

/* vim: set ts=4 sw=4 sts=4 tw=100 et: */
