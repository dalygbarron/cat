/*
 * Rat Pack Texture Atlas Creator
 * Copyright 2019 Daly Graham Barron dalygbarron@gmail.com
 *
 * pack.c
 * Implements bin packing algorithms from pack.h.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License Version 2 as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "pack.h"
#include "util.h"
#include <stdio.h>

struct Picture *tryNode(
    struct Picture *top,
    struct Picture *pic,
    int x,
    int y,
    int w,
    int h
) {
    if (!top) {
        if (pic->width <= w && pic->height <= h) {
            pic->x = x;
            pic->y = y;
            return pic;
        }
        return 0;
    }
    // old one
    struct Picture *result = tryNode(
        top->right,
        pic,
        x + top->width,
        y,
        w - top->width,
        top->height
    );
    if (result) {
        if (!top->right) top->right = pic;
        return result;
    }
    result = tryNode(
        top->left,
        pic,
        x,
        y + top->height,
        w,
        h - top->height
    );
    if (result) {
        if (!top->left) top->left = pic;
        return result;
    }
    return 0;
}

int treePack(
    struct Picture **pics,
    int n,
    int w,
    int h,
    float (*comparison)(struct Picture const *in)
) {
    // sort them to be descending.
    sort(pics, n, comparison);
    // now put them into a tree.
    struct Picture *top = pics[0];
    int succ = 1;
    for (int i = 1; i < n; i++) {
        if (!tryNode(top, pics[i], 0, 0, w - 1, h - 1)) {
            fprintf(stderr, "Pic '%s' did not fit\n", pics[i]->name);
            pics[i]->x = 0 - pics[i]->width;
            pics[i]->y = 0 - pics[i]->height;
            succ = 0;
        }
    }
    return succ;
}
