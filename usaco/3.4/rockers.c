/*
ID: baikaiz1
PROG: rockers
LANG: C
*/
/**
 * Copyright (c) 2012 ZhongLigang. All Rights Reserved
 * $Id$
 *
 * @file rockers.c
 * @author ligang <ZhongLigang@gmail.com>
 * @date 2012-12-18 01:35:12
 */

#include <stdlib.h>
#include <stdio.h>

int n_songs, n_disks, n_volumn;
int song_length[21];
int max_songs = 0;

int dfs(int song_idx, int disk_idx, int disk_left, int selected_songs) {
    if (song_idx >= n_songs || disk_idx >= n_disks) {
        if (selected_songs > max_songs) {
            max_songs = selected_songs;
        }

        return 0;
    }

    if (n_songs - song_idx <= max_songs - selected_songs) {
        return 0;
    }

    // select
    if (song_length[song_idx]<=disk_left) {
        dfs(song_idx+1, disk_idx, disk_left-song_length[song_idx], selected_songs+1);
    } else {
        dfs(song_idx, disk_idx+1, n_volumn, selected_songs);
    }
    // do not select
    dfs(song_idx+1, disk_idx, disk_left, selected_songs);

    return 1;
}

int main(int argc, char** argv) {
    FILE *fin, *fout;
    fin = fopen("rockers.in", "r");
#ifdef DEBUG
    fout = stdout;
#else
    fout = fopen("rockers.out", "w");
#endif

    int i;

    fscanf(fin, "%d %d %d", &n_songs, &n_volumn, &n_disks);
    for (i = 1; i <= n_songs; i++) {
        fscanf(fin, "%d", song_length+i);
    }

    /* {{{ dfs
    dfs(0, 0, n_volumn, 0);
    // }}} */

    // /* {{{ dp
    int result[21][21][21] = {0};
    int idx_song, idx_disk, n_used, j;
    for (idx_song = 1; idx_song <= n_songs; idx_song++) {
        for (idx_disk = 1; idx_disk <= n_disks; idx_disk++) {
            for (n_used = 0; n_used <= n_volumn; n_used++) {
                if (result[idx_song-1][idx_disk][n_used] > result[idx_song-1][idx_disk-1][n_volumn]) {
                    result[idx_song][idx_disk][n_used] = result[idx_song-1][idx_disk][n_used];
                } else {
                    result[idx_song][idx_disk][n_used] = result[idx_song-1][idx_disk-1][n_volumn];
                }

                if (song_length[idx_song] <= n_used
                    && result[idx_song-1][idx_disk-1][n_volumn]+1 > result[idx_song][idx_disk][n_used]) {
                    result[idx_song][idx_disk][n_used] = result[idx_song-1][idx_disk-1][n_volumn]+1;
                }

                if (n_used>=song_length[idx_song]
                    && result[idx_song-1][idx_disk][n_used-song_length[idx_song]]+1>result[idx_song][idx_disk][n_used]) {
                    result[idx_song][idx_disk][n_used] = result[idx_song-1][idx_disk][n_used-song_length[idx_song]]+1;
                }

                if (result[idx_song][idx_disk][n_used] > max_songs) {
                    max_songs = result[idx_song][idx_disk][n_used];
                }
            }
        }
    }
    // }}} */

    fprintf(fout, "%d\n", max_songs);

    return 0;
}

