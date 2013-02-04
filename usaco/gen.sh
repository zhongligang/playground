#!/bin/sh

echo "\
/*
ID: baikaiz1
PROG: $1
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * \$Id$
 *
 * @file $1.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen(\"$1.in\", \"r\");
    fout = fopen(\"$1.out\", \"w\");

    return 0;
}
" > $1.c
