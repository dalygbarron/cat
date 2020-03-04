#include "ImageFile.hh"
#include <iostream>

ImageFile::ImageFile(char const *file) {
    this->name = file;
    if (!this->image.loadFromFile(file)) {
        std::cerr << file << " is not a valid image file" << std::endl;
        throw new std::invalid_argument("bad image file");
    }
}
