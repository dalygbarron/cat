#ifndef FONT_INSTANCE_H
#define FONT_INSTANCE_H

#include <SFML/Graphics.hpp>

/**
 * Stores a font and a size and a colour.
 */
class FontInstance {
    public:
        std::string prefix;
        sf::Font font;
        int size;
        sf::Color colour;

        /**
         * Creates a font instance based on a string that contains all the info
         * it needs.
          @param data is the data and it should be in the format
         *             file:size:hexColour.
         * @throws invalid_argument if the data is no good.
         */
        FontInstance(char const *data);
};

#endif
