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

#include "util.h"
#include <stdlib.h>
#include <stdio.h>

float longestSide(struct Picture const *in) {
    if (in->width > in->height) return in->width;
    return in->height;
}

float totalSides(struct Picture const *in) {
    return in->width + in->height;
}

void sort(
    struct Picture **pics,
    int n,
    float (*comparison)(struct Picture const *in)
) {
    for (int i = 1; i < n; i++){
        int j = i;
        while (j > 0 && comparison(pics[j - 1]) < comparison(pics[j])) {
            struct Picture *tmp = pics[j - 1];
            pics[j - 1] = pics[j];
            pics[j] = tmp;
            j--;
        }
    }
}

struct Picture *loadPicture(
    char const *filename,
    int pathFlag,
    int extensionFlag
) {
    struct Picture *pic = malloc(sizeof(struct Picture));
    int error = lodepng_decode32_file(
        &pic->data,
        &pic->width,
        &pic->height,
        filename
    );
    if (error) {
        fprintf(
            stderr,
            "error %u on file '%s': %s.\n",
            error,
            filename,
            lodepng_error_text(error)
        );
        free(pic->data);
        free(pic);
        return 0;
    }
    return pic;
}
