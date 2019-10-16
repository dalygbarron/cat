/*
 * Rat Pack Texture Atlas Creator
 * Copyright 2019 Daly Graham Barron dalygbarron@gmail.com
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

#ifndef PACK_H
#define PACK_H

#include "Picture.h"

/**
 * Packs an array of pictures by settign their offset properties using a binary
 * tree bin packing algorithm.
 * @param pictures   is the array of pointers to pictures.
 * @param n          is the number of pictures in the array.
 * @param comparison is the function used to compare pictures.
 * @return 1 if all is well, and 0 if they could not all fit.
 */
int treePack(
    struct Picture **pictures,
    int n,
    float (*comparison)(struct Picture const *in)
);


#endif
