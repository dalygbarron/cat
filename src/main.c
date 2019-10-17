/*
 * Rat Pack Texture Atlas Creator
 * Copyright 2019 Daly Graham Barron dalygbarron@gmail.com
 *
 * main.c
 * Contains program entry point, parses arguments, and oversees overall program
 * flow.
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
#include "write.h"
#include "Picture.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define VERSION "0.0.1"

/**
 * Outputs the help information to stdout.
 */
void help() {
    printf("Rat Pack Texture Atlas Creator Version %s\n", VERSION);
    printf("Copyright 2019 Daly Graham Barron dalygbarron@gmail.com\n");
    printf("Licensed under the GNU GPL Version 2\n");
    printf("Actually, this program kinda sucks, maybe don't use it.\n");
}

void version() {
    printf("%s\n", VERSION);
}

/**
 * Outputs the usage information to stderr.
 */
void usage(char const *exe) {
    fprintf(stderr, "Usage: %s [option]... [image]...\n", exe);
    fprintf(stderr, "options:\n");
    fprintf(stderr, "    [-h]\n");
    fprintf(stderr, "    [-v]\n");
    fprintf(stderr, "    [-o <outputImage>]\n");
    fprintf(stderr, "    [-x <outputXml>]\n");
    fprintf(stderr, "    [-d <width>x<height>]\n");
    fprintf(stderr, "    [-s <name>:<width>x<height>]\n");
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
    char const *outputImage = 0;
    char const *outputXml = 0;
    int opt;
    while ((opt = getopt(argc, argv, "+hvo:x:d:s:c:")) != -1) {
        switch (opt) {
            case 'h':
                help();
                return 0;
            case 'v':
                version();
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
            case 'o':
                outputImage = optarg;
                break;
            case 'x':
                outputXml = optarg;
                break;
            default:
                usage(argv[0]);
                return 1;
        }
    }
    // Make sure there is nothing invalid going on here.
    if (outputImage == 0) {
        fprintf(stderr, "Error: Output image must be specified with -o\n");
        return 1;
    }
    if (outputXml == 0) {
        fprintf(stderr, "Error: Output xml must be specified with -x\n");
        return 1;
    }
    // Load in the argument pics.
    int nPics = argc - optind;
    struct Picture **pictures = malloc(sizeof(struct Picture *) * nPics);
    for (int i = optind; i < argc; i++) {
        pictures[i - optind] = loadPicture(argv[i], 0, 0);
    }
    // Place the pictures.
    treePack(pictures, nPics, dimensionsX, dimensionsY, longestSide);
    // Render the output image.
    renderImage(outputImage, pictures, nPics, dimensionsX, dimensionsY);
    // Write the output to the correct file.
    FILE *out = fopen(outputXml, "w");
    if (!out) {
        fprintf(stderr, "Can't open '%s' for writing", outputXml);
        return 1;
    }
    int writeResult = writeXml(out, outputImage, pictures, nPics);
    if (!writeResult) {
        fprintf(stderr, "Error writing to '%s'", outputXml);
        return 1;
    }
    fclose(out);
    // das end.
    for (int i = 0; i < nPics; i++) {
        free(pictures[i]->data);
        free(pictures[i]->name);
        free(pictures[i]);
    }
    return 0;
}
