#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

/**
 * Where random utility things go.
 */
namespace Util {
    /**
     * Finds the bits that a string can be split into with a given delimiter.
     * @param string    is the string to split.
     * @param delimiter is the character to split it by.
     * @return a nice vector with the split bits in it.
     */
    std::vector<std::string> split(std::string const &string, char delimiter);
};

#endif
