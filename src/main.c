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
#include "options.h"
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
    fprintf(stderr, "    [-s <name>:<width>x<height>]...\n");
    fprintf(stderr, "    [-c longest-side|total-sides]\n");
}

/**
 * Entrance of le fiele.
 * @param argc is the number of commandline arguments.
 * @param argv is an array of pointers to the arguments.
 * @return 0 if all is good and 1 if it's screwed.
 */
int main(int argc, char **argv) {
    // Set defaults and parse arguments.
    struct Options options;
    parseOptions(&options, argc, argv);
    // Make sure there is nothing invalid going on here.
    if (options.outputImage == 0) {
        fprintf(stderr, "Error: Output image must be specified with -o\n");
        return 1;
    }
    if (options.outputData == 0) {
        fprintf(stderr, "Error: Output xml must be specified with -x\n");
        return 1;
    }
    // Place the pictures.
    treePack(
        options.pictures,
        options.nPics,
        options.width,
        options.height,
        getComparison(options.comparisonMode)
    );
    // Render the output image.
    renderImage(
        options.outputImage,
        options.pictures,
        options.nPics,
        options.width,
        options.height
    );
    // Write the output to the correct file.
    FILE *out = fopen(options.outputData, "w");
    if (!out) {
        fprintf(stderr, "Can't open '%s' for writing", options.outputData);
        return 1;
    }
    int writeResult = writeXml(
        out,
        options.outputImage,
        options.pictures,
        options.nPics
    );
    if (!writeResult) {
        fprintf(stderr, "Error writing to '%s'", options.outputData);
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
