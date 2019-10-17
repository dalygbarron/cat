/*
 * Rat Pack Texture Atlas Creator
 * Copyright 2019 Daly Graham Barron dalygbarron@gmail.com
 *
 * util.c
 * Implements utility functions defined in util.h.
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

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

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
    // do other parameters and parse filename.
    pic->x = 0;
    pic->y = 0;
    pic->left = 0;
    pic->right = 0;
    int nameLength = strlen(filename);
    pic->name = malloc(sizeof(char) * nameLength);
    strncpy(pic->name, filename, nameLength);
    return pic;
}


int renderImage(
    char const *filename,
    struct Picture **pics,
    int nPics,
    int width,
    int height
) {
    // if allowed, shrink the image to the required size.
    // TODO: this probably needs more work.
    if (width == 0 || height == 0) {
        for (int i = 0; i < nPics; i++) {
            width = max(width, pics[i]->x + pics[i]->width);
            height = max(height, pics[i]->y + pics[i]->height);
        }
    }
    // draw in the pics.
    unsigned char *data = malloc(sizeof(unsigned char) * width * height * 4);
    for (int i = 0; i < nPics; i++) {
        for (int j = 0; j < pics[i]->width * pics[i]->height; j++) {
            int x = pics[i]->x + j % pics[i]->width;
            int y = pics[i]->y + j / pics[i]->width;
            if (x < width && y < height) {
                int index = (y * width + x % width) * 4;
                for (int u = index; u < index + 4; u++) {
                    data[u] = pics[i]->data[j * 4 + u - index];
                }
            }
        }
    }
    // write the file.
    unsigned error = lodepng_encode32_file(filename, data, width, height);
    if (error) {
        fprintf(
            stderr,
            "error %u writing to '%s': %s\n",
            error,
            filename,
            lodepng_error_text(error)
        );
        return 1;
    }
    return 0;
}
