#include "ImageFile.hh"
#include <iostream>
#include <cmath>

ImageFile::ImageFile(char const *file) {
    // TODO: only use actual file name without extension here.
    this->name = file;
    if (!this->image.loadFromFile(file)) {
        std::cerr << file << " is not a valid image file" << std::endl;
        throw new std::invalid_argument("bad image file");
    }
}

int ImageFile::getLongestSide() const {
    sf::Vector2u size = this->image.getSize();
    return fmax(size.x, size.y);
}
