/*
 * Rat Pack Texture Atlas Creator
 * Copyright 2019 Daly Graham Barron dalygbarron@gmail.com
 *
 * testPath.c
 * Tests to make sure that the functions in path.h are implemented correctly.
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
#include "test/unit.h"
#include <stdio.h>

static char *testFormatFilename() {
    ASS("test not implemented", 0);
    return 0;
}

static char *testRelativePathTo() {
    ASS("test not implemented", 0);
    return 0;
}

static char *testRelativePathToBasic() {
    ASS("test not implemented", 0);
    return 0;
}

static char *allTests() {
    RUN_TEST(testFormatFilename);
    RUN_TEST(testRelativePathTo);
    RUN_TEST(testRelativePathToBasic);
    return 0;
}

int main(int argc, char **argv) {
    char *result = allTests();
    if (result != 0) printf("%s\n", result);
    else printf("ALL TESTS PASSED\n");
    printf("Tests run: %d\n", runTests);
    printf("Assertions: %d\n", assertions);
    return result != 0;
}
