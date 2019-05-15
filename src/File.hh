#ifndef FILE_H
#define FILE_H

#include <cstdint>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

/**
 * Contains some functions for writing and reading stuff from files without having to deal with endianness.
 */
namespace File {
    /**
     * Writes an int into a file.
     * @param value is the value to write.
     * @param file  is the file to write into.
     */
    void writeInt(uint32_t value, std::ofstream *file);

    /**
     * Reads a 4 byte integer in from the file.
     * @param file is the file to read from.
     * @return the value that was read.
     */
    uint32_t readInt(std::ifstream *file);

    /**
     * Writes a sfml colour into a file.
     * @param value is the value to write.
     * @param file  is the file to write it into.
     */
    void writeColour(sf::Color value, std::ofstream *file);

    /**
     * Reads an sfml colour out of a file.
     * @param file is the file.
     * @return the colour that was read.
     */
    sf::Color readColour(std::ifstream *file);
};

#endif
