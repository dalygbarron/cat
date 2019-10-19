/*
 * Rat Pack Texture Atlas Creator
 * Copyright 2019 Daly Graham Barron dalygbarron@gmail.com
 *
 * Options.h
 * Stores a representation of all of the commandline arguments that were
 * entered.
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

#ifndef OPTIONS_H
#define OPTIONS_H

#include "Picture.h"
#include <stdio.h>

/**
 * Stores all commandline flags and choices with their own special meaning that
 * are unique to this options thingy, and an array of the pictures to add.
 */
struct Options {
    int helpFlag;
    int versionFlag;
    int filePathFlag;
    int fileExtensionFlag;
    char const *outputImage;
    char const *outputData;
    int width;
    int height;
    struct Picture **pictures;
    int nPics;
    float (*comparison)(struct Picture const *a);
    int (*write)(
        FILE *out,
        char const *imageFile,
        struct Picture **pics,
        int n
    );
};

#endif
