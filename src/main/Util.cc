#include "Util.hh"

#include <sstream>

std::vector<std::string> Util::split(
    std::string const &string,
    char delimiter
) {
    std::stringstream stream(string);
    std::string item;
    std::vector<std::string> bits;
    while (std::getline(stream, item, delimiter)) {
        bits.push_back(std::move(item));
    }
    return bits;
}
