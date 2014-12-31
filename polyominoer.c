/*
 * Copyright © 2014 Bart Massey
 * [This program is licensed under the "MIT License"]
 * Please see the file COPYING in the source
 * distribution of this software for license terms.
 */

/* Polyomino solver. Currently just four-ominoes. */

/* The polyominos:

 I) ####

     ##
 5) ##

    ##
 2)  ##

 T) ###
     #

      #
 L) ###

 P) ###
      #

 O) ##
    ##

*/

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef DEBUG_PROGRESS
#include <inttypes.h>
#endif

typedef int point[2];
typedef point tiles[4];

struct shape {
    char name;
    int asymmetries;
    tiles squares;
};

static struct shape fourominoes[] = {
    {'I', 2, {{0, 0}, {0, 1}, {0, 2}, {0, 3}}},
    {'5', 2, {{1, 0}, {1, 1}, {0, 1}, {0, 2}}},
    {'2', 2, {{0, 0}, {0, 1}, {1, 1}, {1, 2}}},
    {'T', 4, {{0, 0}, {0, 1}, {1, 1}, {0, 2}}},
    {'L', 4, {{1, 0}, {1, 1}, {1, 2}, {0, 2}}},
    {'P', 4, {{0, 0}, {0, 1}, {0, 2}, {1, 2}}},
    {'O', 1, {{0, 0}, {0, 1}, {1, 0}, {1, 1}}}};

static const int nfourominoes = sizeof(fourominoes) / sizeof(struct shape);

void copy_tiles(tiles source, tiles dest) {
    for (int i = 0; i < 4; i++) {
        dest[i][0] = source[i][0];
        dest[i][1] = source[i][1];
    }
}

void rotate(int r, tiles piece) {
    while (r-- > 0) {
        int h = 0;
        for (int i = 0; i < 4; i++)
            if (piece[i][0] > h)
                h = piece[i][0];

        tiles tmp;
        for (int i = 0; i < 4; i++) {
            tmp[i][0] = piece[i][1];
            tmp[i][1] = h - piece[i][0];
        }

        copy_tiles(tmp, piece);
    }
}

typedef char square[4][4];

void render_piece(tiles source, char visual, square dest, int *w, int *h) {
    *h = 0;
    *w = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            dest[i][j] = ' ';
    for (int i = 0; i < 4; i++) {
        int r = source[i][0];
        int c = source[i][1];
        dest[r][c] = visual;
        if (r >= *h)
            *h = r + 1;
        if (c >= *w)
            *w = c + 1;
    }
}

void print_piece(tiles source, char visual) {
    square dest;
    int w, h;
    render_piece(source, visual, dest, &w, &h);
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++)
            printf("%c", dest[r][c]);
        printf("\n");
    }
}

void show_rotations() {
    for (int i = 0; i < nfourominoes; i++) {
        printf("%c\n", fourominoes[i].name);
        for (int r = 0; r < fourominoes[i].asymmetries; r++) {
            printf("---");
            tiles om;
            copy_tiles(fourominoes[i].squares, om);
            rotate(r, om);
            for (int j = 0; j < 4; j++)
                printf(" %d%d", om[j][0], om[j][1]);
            printf("\n");
            print_piece(om, fourominoes[i].name);
        }
        printf("\n");
    }
}

int lookup_piece(char name) {
    for (int i = 0; i < nfourominoes; i++)
        if (fourominoes[i].name == name)
            return i;
    return -1;
}

int bw, bh;
#define MAX_BOARD_DIM 20
static char board[MAX_BOARD_DIM][MAX_BOARD_DIM];

void print_board() {
    for (int r = 0; r < bh; r++) {
        for (int c = 0; c < bw; c++)
            printf("%c", board[r][c]);
        printf("\n");
    }
}

int fits(int r0, int c0, square image, int h, int w) {
    for (int r = 0; r < h; r++)
        for (int c = 0; c < w; c++)
            if (image[r][c] != ' ' && board[r0 + r][c0 + c] != ' ')
                return 0;
    return 1;
}

void place(char visual, int r0, int c0, square image, int h, int w) {
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            if (image[r][c] != ' ') {
                char *bp = &board[r0 + r][c0 + c];
                if (visual == ' ')
                    assert(*bp != ' ');
                else
                    assert(*bp == ' ');
                *bp = visual;
            }
        }
    }
}

#ifdef DEBUG_PROGRESS
uint64_t leaves = 0;
#endif

void try_fit(int idx, char *pieces) {
    if (pieces[idx] == '\0') {
#ifdef DEBUG_PROGRESS
        fprintf(stderr, "\n");
#endif
        print_board();
        exit(0);
    }
    int om = lookup_piece(pieces[idx]);
    assert(om >= 0);
    for (int rot = 0; rot < fourominoes[om].asymmetries; rot++) {
        tiles cur;
        copy_tiles(fourominoes[om].squares, cur);
        rotate(rot, cur);
        int h, w;
        square image;
        render_piece(cur, 'a' + idx, image, &w, &h);
        for (int r0 = 0; r0 < bh - h + 1; r0++) {
            for (int c0 = 0; c0 < bw - w + 1; c0++) {
                if (fits(r0, c0, image, h, w)) {
                    place('a' + idx, r0, c0, image, h, w);
                    try_fit(idx + 1, pieces);
                    place(' ', r0, c0, image, h, w);
                }
#ifdef DEBUG_PROGRESS
                else {
                    leaves++;
                    if (leaves % DEBUG_PROGRESS == 0) {
                        fprintf(stderr, ".");
                    }
                }
#endif
            }
        }
    }
}


int main(int argc, char **argv) {
#ifdef DEBUG_ROTATE
    show_rotations();
#endif

    assert(argc == 3);
    assert(sscanf(argv[1], "%dx%d", &bh, &bw) == 2);
    assert(bw <= MAX_BOARD_DIM && bh <= MAX_BOARD_DIM);
    for (int r = 0; r < bh; r++)
        for (int c = 0; c < bw; c++)
            board[r][c] = ' ';
    
    char *pieces = argv[2];
    for (int i = 0; i < strlen(pieces); i++)
        assert(lookup_piece(pieces[i]) >= 0);
    assert(bw * bh == strlen(pieces) * 4);
    int nt = 0;
    for (int i = 0; i < strlen(pieces); i++)
        if (pieces[i] == 'T')
            nt++;
    assert(nt % 2 == 0);

    try_fit(0, pieces);
    printf("no solution found\n");
    return 1;
}
