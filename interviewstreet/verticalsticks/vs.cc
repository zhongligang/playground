/**
 * Copyright (c) 2012 Flatter World. All Rights Reserved
 * $Id$ 
 * 
 * @file vs.cc
 * @author zhongligang <ligang@flatterworld.com>
 * @date 2012-03-02 12:44:22
 */

#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main (int argc, char *argv[]) {
    int test_case_num, stick_num, sticks[50];
    int sticks_dist[50][2]; // sticks_dist[i][0]: how many sticks < sticks[i], sticks_dist[i][1]: how many sticks >= sitcks[i]
    int i, j, t;
    int ray_len, shorter, longer;
    double result, e_ray_len, prob_all_shorter, prob_longer;

    scanf("%d", &test_case_num);
    for (t = 0; t < test_case_num; t++) {
        scanf("%d", &stick_num);
        for (i = 0; i < stick_num; i++) {
            scanf("%d", &sticks[i]);
        }
        sort(sticks, sticks + stick_num);

        sticks_dist[0][0] = 0;
        sticks_dist[0][1] = stick_num - 1;
        for (i = 1; i < stick_num; i++) {
            if (sticks[i] == sticks[i - 1]) {
                sticks_dist[i][0] = sticks_dist[i - 1][0];
                sticks_dist[i][1] = sticks_dist[i - 1][1];
            } else {
                sticks_dist[i][0] = i;
                sticks_dist[i][1] = stick_num - i - 1;
            }
        }

        result = 1.0;
        // for each position(count from 0), caculate E(ray_len)
        for (i = 1; i < stick_num; i++) {
            e_ray_len = 0;

            // put each line to postion i
            for (j = 0; j < stick_num; j++) {
                shorter = sticks_dist[j][0];
                longer = sticks_dist[j][1];

                // caculate E(ray_len) for this line
                if (longer > 0 && shorter > 0) {
                    prob_all_shorter = 1;
                    for (ray_len = 1; ray_len <= i && shorter >= 0; ray_len++, shorter--) {
                        prob_longer = (double)longer/(longer + shorter);
                        e_ray_len += ray_len * prob_all_shorter * prob_longer;
                        prob_all_shorter *= (1 - prob_longer);
                    }

                    if (ray_len == i + 1) {
                        e_ray_len += prob_all_shorter * ray_len;
                    }
                } else if (longer == 0) {
                    e_ray_len += i + 1;
                } else {
                    e_ray_len += 1;
                }
            }

            result += e_ray_len / stick_num;
        }

        printf("%.2f\n", result);
    }
}

/* vim: set ts=4 sw=4 sts=4 tw=100 et: */
