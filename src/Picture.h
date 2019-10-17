/*
 * Rat Pack Texture Atlas Creator
 * Copyright 2019 Daly Graham Barron dalygbarron@gmail.com
 *
 * Picture.h
 * Defines a picture data structure which stores an offset, bounds, a file
 * name, and even left and right nodes for a binary tree.
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

#ifndef PICTURE_H
#define PICTURE_H

/**
 * Represents a nice picture which has got it's own size and stuff going on.
 * It also stores it's own x and y offset. The reason for this is that way the
 * code for drawing pictures into the final big picture does not need to know
 * about the code which sets the locations of the pictures.
 */
struct Picture {
    unsigned char *data;
    unsigned int x;
    unsigned int y;
    unsigned int width;
    unsigned int height;
    struct Picture *left;
    struct Picture *right;
    char *name;
};

#endif
