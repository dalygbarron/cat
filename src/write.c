/*
 * Rat Pack Texture Atlas Creator
 * Copyright 2019 Daly Graham Barron dalygbarron@gmail.com
 *
 * write.c
 * Implements the output writing methods defined in write.h.
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

#include "write.h"
#include <stdio.h>

int writeXml(
    FILE *out,
    char const *imageFile,
    char const *version,
    struct Picture **pics,
    int n
) {
    int result = 0;
    result |= fprintf(
        out,
        "<pack image=\"%s\" version=\"%s\">",
        imageFile,
        version
    );
    for (int i = 0; i < n; i++) {
        if (!pics[i]->name) continue;
        result |= fprintf(
            out,
            "<rat name=\"%s\" x=\"%u\" y=\"%u\" w=\"%u\" h=\"%u\"/>",
            pics[i]->name,
            pics[i]->x,
            pics[i]->y,
            pics[i]->width,
            pics[i]->height
        );
    }
    result |= fprintf(out, "</pack>");
    return result >= 0;
}

int writeJson(
    FILE *out,
    char const *imageFile,
    char const *version,
    struct Picture **pics,
    int n
) {
    int result = 0;
    result |= fprintf(
        out,
        "{\"image\": \"%s\", \"version\": \"%s\", \"rats\": [",
        imageFile,
        version
    );
    for (int i = 0; i < n - 1; i++) {
        if (!pics[i]->name) continue;
        result |= fprintf(
            out,
            "{\"name\": \"%s\", \"x\": %u, \"y\": %u, \"w\": %u, \"h\": %u},",
            pics[i]->name,
            pics[i]->x,
            pics[i]->y,
            pics[i]->width,
            pics[i]->height
        );
    }
    result |= fprintf(
        out,
        "{\"name\": \"%s\", \"x\": %u, \"y\": %u, \"w\": %u, \"h\": %u}]}",
        pics[n - 1]->name,
        pics[n - 1]->x,
        pics[n - 1]->y,
        pics[n - 1]->width,
        pics[n - 1]->height
    );
    return result >= 0;
}

int writeCsv(
    FILE *out,
    char const *imageFile,
    char const *version,
    struct Picture **pics,
    int n
) {
    int result = 0;
    result |= fprintf(out, "name,x,y,w,h\n");
    for (int i = 0; i < n; i++) {
        result |= fprintf(
            out,
            "%s,%d,%d,%d,%d\n",
            pics[i]->name,
            pics[i]->x,
            pics[i]->y,
            pics[i]->width,
            pics[i]->height
        );
    }
    return result >= 0;
}
