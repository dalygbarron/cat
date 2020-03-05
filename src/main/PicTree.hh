#ifndef PIC_TREE_H
#define PIC_TREE_H

#include "ImageFile.hh"
#include <SFML/Graphics.hpp>

/**
 * Represents a node of a tree that stores pics and inserts them in a square.
 */
class PicTree {
    public:
        sf::Vector2u const space;
        ImageFile const &image;

        /**
         * Creates this tree node by giving it the space it has to put children
         * in, and the image it has at it's root.
         * @param space is the space it has which is not taking into account
         *              the size of the image in any way.
         * @param image is the image that it has at it's root.
         */
        PicTree(sf::Vector2u space, ImageFile const &image);

        /**
         * Deletes the children but not the images.
         */
        ~PicTree();

        /**
         * Tries to add an image to the tree.
         * @param image is the image to add.
         * @return true if it was able to add it and has done so, otherwise it
         *              will be false.
         */
        int insert(ImageFile const &image);

        /**
         * Saves the pics onto one pic with the correct spacing.
         * @param image  is the image to draw onto.
         * @param offset is the offset at which to draw.
         */
        void render(sf::Image &image, sf::Vector2u offset=sf::Vector2u(0, 0));
    
    private:
        PicTree *right = NULL;
        PicTree *bottom = NULL;
};

#endif
