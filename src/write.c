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
    struct Picture **pics,
    int n
) {
    if (fprintf(out, "<ratpack image=\"%s\">", imageFile) < 0) return 0;
    for (int i = 0; i < n; i++) {
        if (!pics[i]->name) continue;
        int response = fprintf(
            out,
            "<pic name=\"%s\" x=\"%u\" y=\"%u\" w=\"%u\" h=\"%u\" />",
            pics[i]->name,
            pics[i]->x,
            pics[i]->y,
            pics[i]->width,
            pics[i]->height
        );
        if (response < 0) return 0;
    }
    if (fprintf(out, "</ ratpack>") < 0) return 0;
    return 1;
}
