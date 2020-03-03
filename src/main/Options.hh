#ifndef OPTIONS_H
#define OPTIONS_H

#include "ImageFile.hh"
#include "FontInstance.hh"
#include <string>

/**
 * Represents the state of the options the program is running with.
 */
class Options {
    public:
        std::string image;
        std::string output;
        std::string style = "xml";
        sf::Vector2i dimensions = sf::Vector2i(1024, 1024);
        std::vector<ImageFile> pics;
        std::vector<FontInstance> fonts;
        int help = false;
        int version = false;
};

#endif
