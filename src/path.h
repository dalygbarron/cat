/*
 * Rat Pack Texture Atlas Creator
 * Copyright 2019 Daly Graham Barron dalygbarron@gmail.com
 *
 * path.h
 * Defines functions for parsing file paths and doing stuff with them.
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

#ifndef PATH_H
#define PATH_H

/**
 * Cuts bits of junk off a filename and makes a new copy with only the good
 * stuff.
 * @param path          is the full filename.
 * @param keepPath      is whether to keep the path part of the filename.
 * @param keepExtension is whether to keep the file extension.
 * @return the newly made version which you will have to delete yourself.
 */
char *formatFilename(char const *path, int keepPath, int keepExtension);

/**
 * Gives you the relative path from the path to one file to the path to
 * another.
 * @param start is the first file.
 * @param end   is the second file that we are getting the relative path to.
 * @return a brand new string with the relative path which you will need to
 *         delete when you are done with it.
 */
char *relativePathTo(char const *start, char const *end);

#endif
