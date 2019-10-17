/*
 * Rat Pack Texture Atlas Creator
 * Copyright 2019 Daly Graham Barron dalygbarron@gmail.com
 *
 * testUtil.c
 * Tests to make sure that the functions in util.h are implemented correctly.
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
#include "test/unit.h"
#include <stdio.h>

static char *testMax() {
    ASS("max is wrong 1", max(1, 2) == 2);
    ASS("max is wrong 2", max(5, 2) == 5);
    ASS("max is wrong 3", max(6, -2) == 6);
    ASS("max is wrong 4", max(0, 0) == 0);
    ASS("max is wrong 5", max(-1000, 1) == 1);
    return 0;
}

static char *testSort() {
    struct Picture a = {0, 0, 0, 100, 10, 0};
    struct Picture b = {0, 0, 0, 90, 60, 0};
    struct Picture c = {0, 0, 0, 13, 31, 0};
    struct Picture d = {0, 0, 0, 64, 64, 0};
    struct Picture e = {0, 0, 0, 12, 42, 0};
    struct Picture f = {0, 0, 0, 50, 45, 0};
    struct Picture g = {0, 0, 0, 32, 32, 0};
    struct Picture *pics[] = {&g, &a, &b, &e, &f, &d, &c};
    struct Picture *sidesPics[] = {&g, &a, &b, &e, &f, &d, &c};
    sort(pics, 7, longestSide);
    sort(sidesPics, 7, totalSides);
    // Test with longest side.
    ASS("sort longestSide is wrong a", pics[0] == &a);
    ASS("sort longestSide is wrong b", pics[1] == &b);
    ASS("sort longestSide is wrong d", pics[2] == &d);
    ASS("sort longestSide is wrong f", pics[3] == &f);
    ASS("sort longestSide is wrong e", pics[4] == &e);
    ASS("sort longestSide is wrong g", pics[5] == &g);
    ASS("sort longestSide is wrong c", pics[6] == &c);
    // test with total sides.
    ASS("sort totalSides is wrong b", sidesPics[0] == &b);
    ASS("sort totalSides is wrong a", sidesPics[1] == &d);
    ASS("sort totalSides is wrong d", sidesPics[2] == &a);
    ASS("sort totalSides is wrong f", sidesPics[3] == &f);
    ASS("sort totalSides is wrong g", sidesPics[4] == &g);
    ASS("sort totalSides is wrong e", sidesPics[5] == &e);
    ASS("sort totalSides is wrong c", sidesPics[6] == &c);
    return 0;
}

static char *allTests() {
    RUN_TEST(testMax);
    RUN_TEST(testSort);
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
