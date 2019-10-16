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

#ifndef UTIL_H
#define UTIL_H

#include "Picture.h"
#include "lodepng.h"

/**
 * Takes a pointer to an array of pictures and sorts them from the one to the
 * longest side to the one with the least long sides.
 * @param pictures is the array of pictures that we will sort in place.
 * @param n        is the number of pictures in the array.
 */
void sortByLongestSide(struct Picture **pictures, int n);

/**
 * Loads a picture in from the file system and returns it.
 * @param filename      is the name of the file to load it from.
 * @param pathFlag      is whether to keep the filename path in the name to
 *                      give to the picture.
 * @param extensionFlag is whether to keep the file extension in the name to
 *                      give to the picture.
 * @return the new picture all set up with offset set to (0, 0).
 */
struct Picture *loadPicture(
    char const *filename,
    int pathFlag,
    int extensionFlag
);


#endif
