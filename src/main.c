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
#include "path.h"
#include "pack.h"
#include "write.h"
#include "Picture.h"
#include "Options.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define VERSION "1.1.1"

/**
 * Outputs the usage information to stderr.
 * @param exe is the name of the executable.
 */
void usage(char const *exe) {
    fprintf(stderr, "Usage: %s [option]... [image]...\n", exe);
    fprintf(stderr, "options:\n");
    fprintf(stderr, "    [-h]\n");
    fprintf(stderr, "    [-v]\n");
    fprintf(stderr, "    [-o <outputImage>]\n");
    fprintf(stderr, "    [-f <outputDatafile>]\n");
    fprintf(stderr, "    [-d <width>:<height>]\n");
    fprintf(stderr, "    [-g <width>:<height>:<name>]...\n");
    fprintf(stderr, "    [-c longest-side|total-sides]\n");
    fprintf(stderr, "    [-w xml|json]\n");
    fprintf(stderr, "For more information: %s -h\n", exe);
}

/**
 * Outputs the help information to stdout.
 * @param exe is the name of the executable.
 */
void help(char const *exe) {
    printf("Rat Pack Texture Atlas Creator Version %s\n", VERSION);
    printf("Copyright 2019 Daly Graham Barron dalygbarron@gmail.com\n");
    printf("Licensed under the GNU GPL Version 2\n\n");
    printf("Usage: %s [option]... [image]...\n", exe);
    printf("options:\n");
    printf("    [-h]\n");
    printf("        Outputs help message and closes.\n");
    printf("    [-v]\n");
    printf("        Outputs version and closes.\n");
    printf("    [-o <outputImage>]\n");
    printf("        Specifies the output image (required)\n");
    printf("    [-f <outputDatafile>]\n");
    printf("        Specifies the output data file (required)\n");
    printf("    [-d <width>:<height>]\n");
    printf("        Specifies image dimensions (default: 512x512\n");
    printf("    [-g <width>:<height>:<name>]...\n");
    printf("        Specifies a ghost sprite with no pixels\n");
    printf("    [-c longest-side|total-sides]\n");
    printf("        Specifies the method of image sorting \n");
    printf("        (default: longest-side)\n");
    printf("    [-w xml|json]\n");
    printf("        Specifies output data format (default: xml)\n\n");
    printf("Example usage:\n");
    printf("    %s -o pic.png -f pic.xml a.png b.png c.png\n", exe);
}

/**
 * Outputs the version number to stdout.
 */
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
    options.filePathFlag = 0;
    options.fileExtensionFlag = 0;
    options.width = 512;
    options.height = 512;
    options.outputData = 0;
    options.outputImage = 0;
    if (!parseOptions(&options, argc, argv)) {
        usage(argv[0]);
        return 0;
    }
    // Do help or version.
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
        usage(argv[0]);
        return 1;
    }
    if (options.outputData == 0) {
        fprintf(stderr, "Error: Output data file must be specified with -f\n");
        usage(argv[0]);
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
    // Write the output to the data file.
    char *relativeImagePath = relativePathTo(
        options.outputData,
        options.outputImage
    );
    FILE *out = fopen(options.outputData, "w");
    if (!out) {
        fprintf(stderr, "Can't open '%s' for writing", options.outputData);
        return 1;
    }
    int writeResult = options.write(
        out,
        relativeImagePath,
        VERSION,
        options.pictures,
        options.nPics
    );
    fclose(out);
    // Tidy up and get outta here.
    free(relativeImagePath);
    freePictures(&options);
    if (!packResult) {
        return 1;
    }
    if (!writeResult) {
        fprintf(stderr, "Error writing to '%s'\n", options.outputData);
        return 1;
    }
    return 0;
}
