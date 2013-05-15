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

typedef struct {
    unsigned long long low;
    unsigned long long high;
} lint;

void lint_clear(lint *a) {
    a->low = 0;
    a->high = 0;
}

void lint_setbit(lint *a, int pos) {
    unsigned long long i = 1;
    if (pos <= 64) {
        a->low |= (i << (pos - 1));
    } else {
        a->high |= (i << (pos - 65));
    }
}

void lint_xor(lint *a, const lint *b) {
    a->low ^= b->low;
    a->high ^= b->high;
}

void lint_and(lint *a, const lint *b) {
    a->low &= b->low;
    a->high &= b->high;
}

int lint_cmp(const void *a, const void *b) {
    lint *a_ = (lint *)a;
    lint *b_ = (lint *)b;

    if (a_->high > b_->high) {
        return 1;
    } else if (a_->high < b_->high) {
        return -1;
    } else if (a_->low == b_->low) {
        return 0;
    } else {
        return a_->low > b_->low ? 1 : -1;
    }
}

void lint_print(FILE *fout, lint *v, int length) {
    int idx;
    unsigned long long tmp;
    unsigned long long mask = 0x8000000000000000UL;

    if (length > 64) {
        idx = length - 64;
        tmp = v->high;

        tmp = (tmp << (64 - idx));
        do {
            fprintf(fout, "%d", ((tmp&mask)>>63)>0?1:0);
            tmp <<= 1;
        } while(--idx);
    }

    idx = length>64?64:length;
    tmp = v->low;

    tmp = (tmp << (64 - idx));
    do {
        fprintf(fout, "%d", ((tmp&mask)>>63)>0?1:0);
        tmp <<= 1;
    } while(--idx);
    fprintf(fout, "\n");
}

void set_actions(lint *actions, int lights) {
    int i = 0, r;

    lint_clear(actions);
    i = lights;
    while (i > 0) {
        lint_setbit(actions, i);
        i--;
    }

    actions++;
    lint_clear(actions);
    i = 1;
    while(i <= lights) {
        lint_setbit(actions, lights + 1 - i);
        i += 2;
    };

    actions++;
    lint_clear(actions);
    i = 2;
    while (i <= lights) {
        lint_setbit(actions, lights + 1 - i);
        i += 2;
    };

    actions++;
    lint_clear(actions);
    i = 1;
    while (i <= lights) {
        lint_setbit(actions, lights + 1 - i);
        i += 3;
    };
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("lamps.in", "r");
    fout = fopen("lamps.out", "w");
    lint final_on;
    lint final_off;
    lint lights_original;
    lint actions[5];
    lint tmp, final;
    lint results[11];
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

    set_actions(actions+1, lights);

    lint_clear(&lights_original);
    i = lights;
    do {
        lint_setbit(&lights_original, i);
    } while(--i);

    lint_clear(&final_on);
    while (1) {
        fscanf(fin, "%d", &i);
        if (i != -1) {
            lint_setbit(&final_on, lights - i + 1);
        } else {
            break;
        }
    }

    lint_clear(&final_off);
    while (1) {
        fscanf(fin, "%d", &i);
        if (i != -1) {
            lint_setbit(&final_off, lights - i + 1);
        } else {
            break;
        }
    }

    if (counts == 0) {
        tmp = lights_original;
        lint_and(&tmp, &final_on);
        if (lint_cmp(&tmp, &final_on) != 0) {
            fprintf(fout, "IMPOSSIBLE\n");
            return 0;
        }

        tmp = lights_original;
        lint_and(&tmp, &final_off);
        lint_xor(&tmp, &final_off);
        if (lint_cmp(&tmp, &final_off) != 0) {
            fprintf(fout, "IMPOSSIBLE\n");
            return 0;
        }

        lint_print(fout, &lights_original, lights);

        return 0;
    }

    i = counts;
    while (i > 4) {
        i -= 2;
    }
    switch (i) {
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
                lint_xor(&final, actions+*current_action);
            }
            current_action++;
        }

        tmp = final;
        lint_and(&tmp, &final_on);
        if (lint_cmp(&tmp, &final_on) == 0) {
            tmp = final;
            lint_and(&tmp, &final_off);
            lint_xor(&tmp, &final_off);
            if (lint_cmp(&tmp, &final_off) == 0) {
                results[i++] = final;
            }
        }

        current_action++;
    }

    if (i == 0) {
        fprintf(fout, "IMPOSSIBLE\n");
        return 0;
    }

    qsort(results, i, sizeof(lint), lint_cmp);
    tmp = results[0];
    lint_print(fout, &tmp, lights);
    for (j = 1; j < i; j++) {
        if (lint_cmp(&tmp, &results[j])) {
            tmp = results[j];
            lint_print(fout, &tmp, lights);
        }
    }

    return 0;
}

