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

int treePack(
    struct Picture **pictures,
    int n,
    float (*comparison)(struct Picture const *in)
) {
    sort(pictures, n, comparison);
    int x = 0;
    for (int i = 0; i < n; i++) {
        pictures[i]->x = x;
        x += pictures[i]->width;
    }
    return 1;
}
