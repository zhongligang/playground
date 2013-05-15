/*
ID: baikaiz1
PROG: shopping
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file shopping.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

typedef struct {
    int id;
    int num;
} packet_t;

typedef struct {
    int num;
    packet_t packet[5];
    int price;
} offer_t;

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("shopping.in", "r");
    fout = fopen("shopping.out", "w");
    int i, j, k;
    int product_prices[1000] = {0};
    int product_id, product_num, product_price;
    int n_to_buy;
    packet_t to_buy[5];
    int n_offer;
    offer_t offers[99];
    int to_pay[6][6][6][6][6];
    int p1, p2, p3, p4, p5;
    int price_pre, price_packet;
    offer_t offer_proceed[99];
    int n_offer_proceed;
    int should_proceed;

    fscanf(fin, "%d", &n_offer);
    for (i = 0; i < n_offer; i++) {
        fscanf(fin, "%d", &offers[i].num);
        for (j = 0; j < offers[i].num; j++) {
            fscanf(fin, "%d %d", &offers[i].packet[j].id, &offers[i].packet[j].num);
        }
        fscanf(fin, "%d", &offers[i].price);
    }

    fscanf(fin, "%d", &n_to_buy);
    for (i = 0; i < n_to_buy; i++) {
        fscanf(fin, "%d %d %d", &product_id, &product_num, &product_price);
        to_buy[i].id = product_id;
        to_buy[i].num = product_num;
        product_prices[product_id] = product_price;
    }
    while (i < 5) {
        to_buy[i].id = 0;
        to_buy[i].num = 0;
        i++;
    }

    n_offer_proceed = 0;
    for (i = 0; i < n_offer; i++) {

        for (j = 0; j < offers[i].num; j++) {
            should_proceed = 0;
            for (k = 0; k < n_to_buy; k++) {
                if (to_buy[k].id == offers[i].packet[j].id) {
                    should_proceed = 1;
                }
            }

            if (!should_proceed) {
                break;
            }
        }

        if (should_proceed) {
            offer_proceed[n_offer_proceed].num = 5;
            offer_proceed[n_offer_proceed].price = offers[i].price;
            for (j = 0; j < 5; j++) {
                offer_proceed[n_offer_proceed].packet[j].id= 0;
                offer_proceed[n_offer_proceed].packet[j].num = 0;
                for (k = 0; k < offers[i].num; k++) {
                    if (offers[i].packet[k].id == to_buy[j].id) {
                        offer_proceed[n_offer_proceed].packet[j].id = offers[i].packet[k].id;
                        offer_proceed[n_offer_proceed].packet[j].num = offers[i].packet[k].num;
                        break;
                    }
                }
            }
            n_offer_proceed++;
        }

    }

    bzero(to_pay, sizeof(to_pay));
    for (p1 = 0; p1 <= to_buy[0].num; p1++) {
        for (p2 = 0; p2 <= to_buy[1].num; p2++) {
            for (p3 = 0; p3 <= to_buy[2].num; p3++) {
                for (p4 = 0; p4 <= to_buy[3].num; p4++) {
                    for (p5 = 0; p5 <= to_buy[4].num; p5++) {
                        to_pay[p1][p2][p3][p4][p5] =
                            product_prices[to_buy[0].id]*p1
                            +product_prices[to_buy[1].id]*p2
                            +product_prices[to_buy[2].id]*p3
                            +product_prices[to_buy[3].id]*p4
                            +product_prices[to_buy[4].id]*p5;

                        for (i = 0; i < n_offer_proceed; i++) {
                            if (p1 >= offer_proceed[i].packet[0].num
                                && p2 >= offer_proceed[i].packet[1].num
                                && p3 >= offer_proceed[i].packet[2].num
                                && p4 >= offer_proceed[i].packet[3].num
                                && p5 >= offer_proceed[i].packet[4].num
                                && to_pay[p1][p2][p3][p4][p5] > to_pay[p1-offer_proceed[i].packet[0].num][p2-offer_proceed[i].packet[1].num][p3-offer_proceed[i].packet[2].num][p4-offer_proceed[i].packet[3].num][p5-offer_proceed[i].packet[4].num] + offer_proceed[i].price
                                ) {
                                to_pay[p1][p2][p3][p4][p5] = to_pay[p1-offer_proceed[i].packet[0].num][p2-offer_proceed[i].packet[1].num][p3-offer_proceed[i].packet[2].num][p4-offer_proceed[i].packet[3].num][p5-offer_proceed[i].packet[4].num] + offer_proceed[i].price;
                            }
                        }
                    }
                }
            }
        }
    }

    fprintf(fout, "%d\n", to_pay[to_buy[0].num][to_buy[1].num][to_buy[2].num][to_buy[3].num][to_buy[4].num]);

    return 0;
}

