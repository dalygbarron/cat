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

#include "util.h"
#include "pack.h"
#include "Picture.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * Outputs the help information to stdout.
 */
void help() {
    printf("Rat Pack Texture Atlas Creator\n");
    printf("Copyright 2019 Daly Graham Barron dalygbarron@gmail.com\n");
    printf("Licensed under the GNU GPL Version 2\n");
    printf("Actually, this program kinda sucks, maybe don't use it.\n");
}

/**
 * Outputs the usage information to stderr.
 */
void usage(char const *exe) {
    fprintf(stderr, "Usage: %s [options] <image1> <image2> <...>\n", exe);
    fprintf(stderr, "options:\n");
    fprintf(stderr, "    [-h]\n");
    fprintf(stderr, "    [-o <outputImage>]\n");
    fprintf(stderr, "    [-x <outputXml>]\n");
    fprintf(stderr, "    [-d <width>x<height>]\n");
    fprintf(stderr, "    [-s <width>x<height>]\n");
    fprintf(stderr, "    [-c longest-side|total-sides]\n");
}

/**
 * Entrance of le fiele.
 * @param argc is the number of commandline arguments.
 * @param argv is an array of pointers to the arguments.
 * @return 0 if all is good and 1 if it's screwed.
 */
int main(int argc, char * const *argv) {
    // Parse commandline arguments.
    int longestSideFlag = 1;
    int dimensionsX = 512;
    int dimensionsY = 512;
    int opt;
    while ((opt = getopt(argc, argv, "+ho:x:d:s:c:")) != -1) {
        switch (opt) {
            case 'h':
                help();
                return 0;
            case 'c':
                printf(">%s\n", optarg);
                break;
            case 'd':
                sscanf(optarg, "%dx%d", &dimensionsX, &dimensionsY);
                break;
            case 's':
                fprintf(stderr, "Sorry, -s option doesn't work yet\n");
                break;
            default:
                usage(argv[0]);
                return 1;
        }
    }
    // Make sure there is nothing invalid going on here.
    // Load in the argument pics.
    int nPics = argc - optind;
    struct Picture **pictures = malloc(sizeof(struct Picture *) * nPics);
    for (int i = optind; i < argc; i++) {
        pictures[i - optind] = loadPicture(argv[i], 0, 0);
    }
    // perform the placement operation upon them.

    // das end.
    return 0;
}
