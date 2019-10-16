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

#include <stdio.h>
#include <unistd.h>

void help() {
    printf("Rat Pack Texture Atlas Creator\n");
    printf("Copyright 2019 Daly Graham Barron dalygbarron@gmail.com\n");
}

/**
 * Entrance of le fiele.
 * @param argc is the number of commandline arguments.
 * @param argv is an array of pointers to the arguments.
 * @return 0 if all is good and 1 if it's screwed.
 */
int main(int argc, char * const *argv) {
    // Parse commandline arguments.
    int opt;
    int helpFlag = 0;
    while ((opt = getopt(argc, argv, "+ht:")) != -1) {
        switch (opt) {
            case 'h':
                help();
                break;
            case 't':
                printf(">%s\n", optarg);
                break;
            default:
                fprintf(
                    stderr,
                    "Usage: %s [-h] [-o outputImage] [-x outputXml] "
                    "[-d <width>x<height>] [-s <width>x<height>"
                    "<image1> <image2> <...>\n",
                    argv[0]
                );
                return 1;
        }
    }
    for (int i = optind; i < argc; i++) {
        printf("eh\n");
    }
    // das end.
    return 0;
}
