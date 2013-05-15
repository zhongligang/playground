/*
ID: baikaiz1
PROG: prefix
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file prefix.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct trie_node {
    struct trie_node *next[26];
    char exists;
} trie_node;

void trie_node_clear(trie_node *node) {
    int i;
    node->exists = 0;
    for (i = 0; i < 26; i++) {
        node->next[i] = NULL;
    }
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("prefix.in", "r");
    fout = fopen("prefix.out", "w");

    char primitives[201][11];
    char s[200001];
    char reached[200001] = {0};
    int num_primitives;
    int num_chars;
    int i, j, k;
    char current;
    trie_node trie_root;
    trie_node *trie_tmp;
    trie_node *trie_p;

    trie_node_clear(&trie_root);

    num_primitives = 0;
    while (fscanf(fin, "%s", primitives[num_primitives]) == 1) {
        if (primitives[num_primitives][0] == '.') {
            break;
        }

        trie_p = &trie_root;
        for (i = 0, j = strlen(primitives[num_primitives]); i < j; i++) {
            current = primitives[num_primitives][i] - 'A';
            if (trie_p->next[current] == NULL) {
                trie_tmp = (trie_node *)malloc(sizeof(trie_node));
                trie_node_clear(trie_tmp);
                trie_p->next[current] = trie_tmp;
            }
            trie_p = trie_p->next[current];
        }
        trie_p->exists = 1;
        num_primitives++;
    }

    num_chars = 0;
    while (fscanf(fin, "%s", s+num_chars) != EOF) {
        num_chars += strlen(s+num_chars);
    }

    reached[0] = 1;
    for (i = 0; i < num_chars; i++) {
        if (reached[i]) {
            trie_p = &trie_root;
            k = 10;
            if (num_chars - i < 10) {
                k = num_chars - i;
            }
            for (j = 0; j < k; j++) {
                current = s[i+j]-'A';
                if (trie_p->next[current]) {
                    trie_p = trie_p->next[current];
                    if (trie_p->exists) {
                        reached[i+j+1] = 1;
                    }
                } else {
                    break;
                }
            }
        }
    }

    num_chars += 1;
    while (reached[--num_chars] == 0) {
    }

    fprintf(fout, "%d\n", num_chars);

    return 0;
}

