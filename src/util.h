/*
 * Rat Pack Texture Atlas Creator
 * Copyright 2019 Daly Graham Barron dalygbarron@gmail.com
 *
 * util.h
 * This file defines utility functions that are useful within this application.
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
#include "Options.h"
#include "lodepng.h"

/**
 * Returns the greater of two values.
 * @param a is the first value.
 * @param b is the second value.
 * @return the higher one.
 */
int max(int a, int b);

/**
 * Gives the value of the picture's longest side.
 * @param in is the picture to compare.
 * @return the length of it's longest side.
 */
float longestSide(struct Picture const *in);

/**
 * Gives the length of the picture's sides added together.
 * @param in is the picture to look at.
 * @return the total of the picture's sides.
 */
float totalSides(struct Picture const *in);

/**
 * Sorts a list of pictures by comparing them against a value calculated with
 * your choice of function.
 * @param pictures   is a pointer to an array of pictures to sort in place.
 * @param n          is the number of pictures.
 * @param comparison is a function which gives a value for each picture by
 *                   which to compare them for sorting.
 */
void sort(
    struct Picture **pics,
    int n,
    float (*comparison)(struct Picture const *in)
);

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

/**
 * Parses a string and returns a comparison function from it.
 * @param name is the name of the comparison function you want.
 * @return a function pointer for the output function.
 */
float (*parseComparison(char const *name))(struct Picture const *a);

/**
 * Parses a string and returns a writing output function from it.
 * @param name is the name of the writing output function you want.
 * @return a pointer to the function you wanted or null if you gave an
 *         incorrect string.
 */
int (*parseWrite(char const *name))(
    FILE *out,
    char const *imageFile,
    char const *version,
    struct Picture **pics,
    int n
);

/**
 * Parses the given commandline options into the given options object.
 * Options that are not present in the commandline arguments are simply not
 * touched, so if you have defaults you can set them before calling this
 * method.
 * @param options is the options object to write the results to.
 * @param argc    is the number of commandline tokens.
 * @param argv    is the list of commandline input tokens.
 * @return 1 if all is well and 0 if the arguments were invalid.
 */
int parseOptions(struct Options *options, int argc, char **argv);

/**
 * Frees all the pictures and stuff out of an options object so there is no
 * memory leaking after you get rid of it.
 * @param options is the options object storing the pictures to free.
 */
void freePictures(struct Options *options);

/**
 * Draws an array worth of pictures onto a single picture and then writes that
 * picture to a file.
 * @param filename is the file to write to.
 * @param pics     is the list of pictures to render.
 * @param nPics    is the number of pictures in the array.
 * @param width    is the width the output image should have.
 * @param height   is the height the output image should have.
 * @return 1 if all went well and 0 if something screwed up.
 */
int renderImage(
    char const *filename,
    struct Picture **pics,
    int nPics,
    int width,
    int height
);

#endif
