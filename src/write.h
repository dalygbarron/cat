/*
 * Rat Pack Texture Atlas Creator
 * Copyright 2019 Daly Graham Barron dalygbarron@gmail.com
 *
 * write.h
 * This file defines methods of writing the locations of the seperate pictures
 * within the pack to file. Right now there is only one output format but that
 * could possibly change. Also, if you are making some kind of game and have
 * a special format, just alter or add a function here and use it to write and
 * recompile and you will be good to go with your new format.
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

#ifndef WRITE_H
#define WRITE_H

#include "Picture.h"
#include <stdio.h>

/**
 * Writes out the positions of all the pictures within the pack as xml.
 * @see README.md to see what the format is.
 * @param out       is the file to write to.
 * @param imageFile is the filename of the associated image.
 * @param pics      is the list of pics in the pack.
 * @param n         is the number of pics in the list.
 * @return 1 if all went well and 0 if it failed due to io or something.
 */
int writeXml(
    FILE *out,
    char const *imageFile,
    struct Picture **pics,
    int n
);

#endif
