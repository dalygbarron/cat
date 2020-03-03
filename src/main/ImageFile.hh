#ifndef IMAGE_FILE_H
#define IMAGE_FILE_H

#include <SFML/Graphics.hpp>

/**
 * Stores an image and the file it was loaded from.
 */
class ImageFile {
    sf::Image image;
    std::string name;
};

#endif
