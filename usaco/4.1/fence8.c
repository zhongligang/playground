/*
ID: baikaiz1
PROG: fence8
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file fence8.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("fence8.in", "r");
#ifdef DEBUG
    fout = stdout;
#else
    fout = fopen("fence8.out", "w");
#endif

    return 0;
}

