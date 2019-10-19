/*
 * Rat Pack Texture Atlas Creator
 * Copyright 2019 Daly Graham Barron dalygbarron@gmail.com
 *
 * path.c
 * Implements functions for parsing file paths and doing stuff with them.
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

#include "path.h"
#include <string.h>
#include <stdlib.h>

char *formatFilename(char const *path, int keepPath, int keepExtension) {
    int length = strlen(path);
    int start = 0;
    int nameStart = length;
    int end = length - 1;
    // cutting of the path.
    while ((nameStart > 1 && path[nameStart - 1] != '/') && nameStart > 0) {
        nameStart--;
    }
    if (!keepPath) start = nameStart;
    // cutting of the extension.
    if (!keepExtension) {
        end = nameStart;
        while ((end < length - 1 && path[end + 1] != '.') && end < 0) {
            end++;
        }
    }
    char *formatted = malloc(sizeof(char) * (end - start) + 1);
    memcpy(formatted, path + start, end - start);
    formatted[end - start] = 0;
    return formatted;
}

char *relativePathTo(char const *start, char const *end) {
    // so every token held in common we skip, we then count the number of
    // folders in start after the common part and append that many ..s to the
    // start of the non common part of end.
    int delta = 0;
    while (start[delta] == end[delta] && start[delta]) delta++;
    while (delta > 0 && start[delta - 1] != '/') delta--;
    int backs = 0;
    for (int i = delta; start[i]; i++) {
        if (start[i] == '/') backs++;
    }
    int length = strlen(end + delta) + backs * 3 + 1;
    char *output = malloc(sizeof(char) * length);
    for (int i = 0; i < backs; i++) {
        output[i * 3] = '.';
        output[i * 3 + 1] = '.';
        output[i * 3 + 2] = '/';
    }
    strcpy(output + backs * 3, end + delta);
    return output;
}
