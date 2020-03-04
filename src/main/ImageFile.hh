#ifndef IMAGE_FILE_H
#define IMAGE_FILE_H

#include <SFML/Graphics.hpp>

/**
 * Stores an image and the file it was loaded from.
 */
class ImageFile {
    public:
        sf::Image image;
        std::string name;

        /**
         * Loads the image hell yeah.
         * @param file is the file the pic is from.
         */
        ImageFile(char const *file);
};

#endif
