#!/bin/sh

if [ $# -le 0 ]; then
    echo "Usage $0 name"
    exit 1
fi

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
    if ((fin = fopen(\"$1.in\", \"r\")) == NULL) {
        perror(\"Fail open $1.in\");
        return 1;
    }
#ifdef DEBUG
    fout = stdout;
#else
    if ((fout = fopen(\"$1.out\", \"w\")) == NULL) {
        perror(\"Fail open $1.out\");
        return 1;
    }
#endif

    return 0;
}

/* vim: set ts=4 sts=4 sw=4 et: */
" > $1.c

echo "\
CC=gcc
CFLAGS=\$(OCFLAGS)-DDEBUG -g
$1: $1.c
.PHONY: clean
clean: 
\trm -f $1 $1.in $1.out
\trm -rf $1.dSYM
" > Makefile
