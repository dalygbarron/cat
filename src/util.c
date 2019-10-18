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
#include <unistd.h>

#define GHOST_NAME_SIZE 128

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

// Undeclared helper function.
float (*parseComparison(char const *name))(struct Picture const *a) {
    if (strcmp(name, "longest-side") == 0) return longestSide;
    else if (strcmp(name, "total-sides") == 0) return totalSides;
    else return 0;
}

int parseOptions(struct Options *options, int argc, char **argv) {
    // parse the flags.
    int opt;
    struct Picture *ghosts = 0;
    int nGhosts = 0;
    while ((opt = getopt(argc, argv, "+hvo:f:d:g:c:")) != -1) {
        switch (opt) {
            case 'h':
                options->helpFlag = 1;
                return 0;
            case 'v':
                options->versionFlag = 1;
                return 0;
            case 'c':
                options->comparison = parseComparison(optarg);
                if (options->comparison == 0) {
                    fprintf(
                        stderr,
                        "comparison mode '%s' is not valid",
                        optarg
                    );
                    return 0;
                }
                break;
            case 'd':
                sscanf(
                    optarg,
                    "%d:%d",
                    &options->width,
                    &options->height
                );
                break;
            case 'g':
                nGhosts++;
                struct Picture *ghost = malloc(sizeof(struct Picture));
                ghost->name = malloc(sizeof(char) * GHOST_NAME_SIZE);
                ghost->data = 0;
                ghost->x = 0;
                ghost->y = 0;
                ghost->width = 0;
                ghost->height = 0;
                ghost->left = 0;
                ghost->right = 0;
                sscanf(
                    optarg,
                    "%d:%d:%s",
                    &ghost->width,
                    &ghost->height,
                    ghost->name
                );
                if (ghosts == 0) {
                    ghosts = ghost;
                } else {
                    struct Picture *node = ghosts;
                    while (node->left) node = node->left;
                    node->left = ghost;
                }
                break;
            case 'o':
                options->outputImage = optarg;
                break;
            case 'f':
                options->outputData = optarg;
                break;
            default:
                return 0;
        }
    }
    // handle arguments.
    options->nPics = argc - optind + nGhosts;
    options->pictures = malloc(sizeof(struct Picture *) * options->nPics);
    for (int i = optind; i < argc; i++) {
        options->pictures[i - optind] = loadPicture(argv[i], 0, 0);
    }
    int i = argc - optind;
    struct Picture *node = ghosts;
    while (node) {
        options->pictures[i] = node;
        struct Picture *next = node->left;
        node->left = 0;
        node = next;
        i++;
    }
    return 1;
}

void freePictures(struct Options *options) {
    for (int i = 0; i < options->nPics; i++) {
        free(options->pictures[i]->data);
        free(options->pictures[i]->name);
        free(options->pictures[i]);
    }
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
        if (pics[i]->data == 0) continue;
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
