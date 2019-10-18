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
#include "Options.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define VERSION "0.0.1"

/**
 * Outputs the usage information to stderr.
 */
void usage(char const *exe) {
    fprintf(stderr, "Usage: %s [option]... [image]...\n", exe);
    fprintf(stderr, "options:\n");
    fprintf(stderr, "    [-h] help\n");
    fprintf(stderr, "    [-v] version\n");
    fprintf(stderr, "    [-o <outputImage>] output image\n");
    fprintf(stderr, "    [-f <outputXml>] output file\n");
    fprintf(stderr, "    [-d <width>:<height>] image dimensions\n");
    fprintf(stderr, "    [-g <width>:<height>:<name>]... ghosts\n");
    fprintf(stderr, "    [-c longest-side|total-sides] comparison function\n");
    fprintf(stderr, "    [-w xml] output format\n");
}

/**
 * Outputs the help information to stdout.
 */
void help(char const *exe) {
    printf("Rat Pack Texture Atlas Creator Version %s\n", VERSION);
    printf("Copyright 2019 Daly Graham Barron dalygbarron@gmail.com\n");
    printf("Licensed under the GNU GPL Version 2\n");
    usage(exe);
}

void version() {
    printf("%s\n", VERSION);
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
    options.comparison = longestSide;
    options.write = writeXml;
    options.helpFlag = 0;
    options.versionFlag = 0;
    options.width = 512;
    options.height = 512;
    parseOptions(&options, argc, argv);
    // do help or version
    if (options.helpFlag) {
        help(argv[0]);
        return 0;
    }
    if (options.versionFlag) {
        version();
        return 0;
    }
    // Make sure there is nothing invalid going on here.
    if (options.outputImage == 0) {
        fprintf(stderr, "Error: Output image must be specified with -o\n");
        return 1;
    }
    if (options.outputData == 0) {
        fprintf(stderr, "Error: Output xml must be specified with -f\n");
        return 1;
    }
    // Place the pictures.
    int packResult = treePack(
        options.pictures,
        options.nPics,
        options.width,
        options.height,
        options.comparison
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
    int writeResult = options.write(
        out,
        options.outputImage,
        options.pictures,
        options.nPics
    );
    
    fclose(out);
    // das end.
    if (!packResult) {
        return 1;
    }
    if (!writeResult) {
        fprintf(stderr, "Error writing to '%s'", options.outputData);
        return 1;
    }
    freePictures(&options);
    return 0;
}
