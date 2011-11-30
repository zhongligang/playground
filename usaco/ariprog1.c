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

    max = set[nset-1]/(n-1);
    nsol = 0;
    for (i = 1; i <= max; i++)
    {
        for (j = 0; j < nset; j++)
        {
            x = set[j];
            flag = 0;
            if (x+(n-1)*i < 125001)
            {
                flag = 1;
                for (k = n - 1; k; k--)
                {
                    if (!map[x+k*i])
                    {
                        flag = 0;
                        break;
                    }
                }
            }

            if (flag)
            {
                nsol++;
                fprintf(fout, "%d %d\n", x, i);
            }
        }
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
