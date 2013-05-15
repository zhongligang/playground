/*
ID: baikaiz1
PROG: lamps
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file lamps.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

// lights bit unsigned char 00123456

inline int light_is_on(unsigned char light, int pos) {
    return (light>>(5-(pos - 1)%6))&1;
}

void light_print(FILE *fout, unsigned char light, int length) {
    int i = 0, idx;

    while (i++ < length){
        fprintf(fout, "%d", light_is_on(light, i));
    }

    fprintf(fout, "\n");
}

int uchar_cmp(const void *a, const void *b) {
    if (*(unsigned char*)a > *(unsigned char*)b) {
        return 1;
    } else if (*(unsigned char*)a < *(unsigned char*)b) {
        return -1;
    } else {
        return 0;
    }
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("lamps.in", "r");
    fout = fopen("lamps.out", "w");

    unsigned char final_on;
    unsigned char final_off;
    unsigned char lights_original;
    unsigned char actions[] = {
        0,
        0x3F,
        0x2A,
        0x15,
        0x24
    };
    unsigned char tmp, final;
    unsigned char results[11];
    // zero to indicate empty action
    // -1 to indicate action end
    // -2 to indicate end
    int action_sequence1[] = {
        1, -1,
        2, -1,
        3, -1,
        4, -1,
        -2
    };
    int action_sequence2[] = {
        1, 2, -1,
        1, 3, -1,
        1, 4, -1,
        2, 3, -1,
        2, 4, -1,
        3, 4, -1,
        0, -1,
        -2
    };
    int action_sequence3[] = {
        1, 2, 4, -1,
        1, 3, 4, -1,
        2, 3, 4, -1,
        1, -1,
        2, -1,
        3, -1,
        4, -1,
        0, -1,
        -2
    };
    int action_sequence4[] = {
        1, -1,
        2, -1,
        3, -1,
        4, -1,
        1, 2, -1,
        1, 3, -1,
        1, 4, -1,
        2, 3, -1,
        2, 4, -1,
        3, 4, -1,
        0, -1,
        -2
    };
    int *applied_sequence;
    int *current_action;

    int lights;
    int counts;
    int i;
    int j;

    fscanf(fin, "%d", &lights);
    fscanf(fin, "%d", &counts);

    i = lights;
    lights_original = 0;
    for (i = 0; i < 6 && i < lights; i++) {
        lights_original |= 1 << (5 - i);
    }

    final_on = 0;
    while (1) {
        fscanf(fin, "%d", &i);
        if (i != -1) {
            final_on |= 1 << (5 - (i - 1) % 6);
        } else {
            break;
        }
    }

    final_off = 0;
    while (1) {
        fscanf(fin, "%d", &i);
        if (i != -1) {
            final_off |= 1 << (5 - (i-1) % 6);
        } else {
            break;
        }
    }

    if (final_off & final_on) {
        fprintf(fout, "IMPOSSIBLE\n");
        return 0;
    }

    if (counts == 0) {
        if (lights_original & final_on != final_on) {
            fprintf(fout, "IMPOSSIBLE\n");
            return 0;
        }

        if (lights_original & final_off ^ final_off != final_off) {
            fprintf(fout, "IMPOSSIBLE\n");
            return 0;
        }

        light_print(fout, lights_original, lights);

        return 0;
    }

    if (counts > 4) {
        if (counts & 1) {
            counts = 3;
        } else {
            counts = 4;
        }
    }
    switch (counts) {
        case 1:
            applied_sequence = action_sequence1;
            break;
        case 2:
            applied_sequence = action_sequence2;
            break;
        case 3:
            applied_sequence = action_sequence3;
            break;
        case 4:
            applied_sequence = action_sequence4;
            break;
        default:
            break;
    }

    i = 0;
    current_action = applied_sequence;
    while (*current_action != -2) {
        final = lights_original;
        while (*current_action != -1) {
            if (*current_action != 0) {
                final ^= actions[*current_action];
            }
            current_action++;
        }

        if ((final & final_on) == final_on && (final & final_off ^ final_off) == final_off) {
            results[i++] = final;
        }

        current_action++;
    }

    if (i == 0) {
        fprintf(fout, "IMPOSSIBLE\n");
        return 0;
    }

    qsort(results, i, sizeof(unsigned char), uchar_cmp);
    tmp = results[0];
    light_print(fout, tmp, lights);
    for (j = 1; j < i; j++) {
        if (results[j] != tmp) {
            tmp = results[j];
            light_print(fout, tmp, lights);
        }
    }

    return 0;
}

