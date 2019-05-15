#ifndef IMAGE_NODE_H
#define IMAGE_NODE_H

#include <SFML/Graphics.hpp>

class ImageNode: public sf::Image {
    ImageNode *right = 0;
    ImageNode *down = 0;

public:
    sf::Vector2u offset;
    char const *name;

    /**
     * creates the image node, loads it's image and saves it's name.
     * @param filename is the name of the image to open.
     */
    ImageNode(char const *filename);

    /**
     * Tries to add a child node to this node.
     * @param child  is the child to add.
     * @param bounds is how much space left there is for the child to fit in. This is meant to decrease recursively.
     * @return true if it was added, and false if it was too big to fit in.
     */
    int addChild(ImageNode *child, sf::Vector2u bounds);

    /**
     * Flattens the tree onto one picture.
     * @param image      is the image to write onto. You must make sure it's big enough before passing it obviously.
     * @param drawOffset is the offset to start drawing at so the function can be called recursively.
     */
    void flatten(sf::Image *image, sf::Vector2u drawOffset);

    /**
     * Writes about the image in a file.
     * @param file is the file to write it into.
     * @param drawOffset is the offset to add to this image's offset for it's global position which gets written in.
     */
    void write(std::ofstream *file, sf::Vector2u drawOffset);
};

#endif
