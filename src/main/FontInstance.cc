#include "FontInstance.hh"
#include <iostream>

FontInstance::FontInstance(char const *data) {
    std::string dataString = data;
    std::vector<std::string> bits = std::split(dataString, ':');
    if (bits.size() != 3) {
        std::cerr << dataString <<
            " is not a valid data string for font instance" << std::endl;
        throw new std::invalid_argument("bad font instance data string");
    }
    this->size = std::stoi(bits[1]);
    this->colour = sf::Color(std::stoi(bits[2], NULL, 16));
    if (!this->font.loadFromFile(bits[0])) {
        std::cerr << bits[0] << " is not a valid font file" << std::endl;
        throw new std::invalid_argument("bad font file");
    }
}
