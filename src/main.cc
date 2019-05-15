#include <iostream>
#include <list>
#include "ImageNode.hh"
#include "File.hh"

#define SHEET_WIDTH 512
#define SHEET_HEIGHT 512

/**
 * Compares the size of two image nodes. The size is calculated as adding both sides which is accurate for boolean
 * comparison purposes as far as I know.
 * @param a is the first image node.
 * @param b is the second image node.
 * @return true if a is bigger than b.
 */
int compareSize(ImageNode const *a, ImageNode const *b) {
    sf::Vector2u aSize = a->getSize();
    sf::Vector2u bSize = b->getSize();
  return (std::max(aSize.x, aSize.y) > std::max(bSize.x, bSize.y));
}

/**
 * starts the program and parses the arguments.
 * @param argc is the number of commandline arguments.
 * @param argv is the array of commandline arguments.
 * @return 0 if all is well otherwise something else.
 */
int main(int argc, char **argv) {
    if (argc < 3) {
        std::cerr << "usage: rat outputfile inputfile1 inputfile2 ... inputfileN" << std::endl;
        return 1;
    }
    // place all input images into list and sort it by size.
    std::list<ImageNode *> images;
    for (int i = 2; i < argc; i++) {
        images.push_front(new ImageNode(argv[i]));
    }
    images.sort(compareSize);
    // Build node tree.
    ImageNode *root = 0;
    sf::Vector2u rootSize;
    for (ImageNode *node: images) {
        if (root) {
            if (!root->addChild(node, sf::Vector2u(SHEET_WIDTH, SHEET_HEIGHT))) {
                std::cout << "the nest is too small for the RATS. " << node->name << std::endl;
            }
        } else {
            root = node;
            rootSize = root->getSize();
        }
    }
    // Render to pic.
    sf::Image pic;
    pic.create(SHEET_WIDTH, SHEET_HEIGHT, sf::Color(0, 0, 0, 0));
    root->flatten(&pic, sf::Vector2u(0, 0));
    //write out to file.
    std::ofstream file(argv[1], std::ofstream::binary);
    File::writeInt(SHEET_WIDTH, &file);
    File::writeInt(SHEET_HEIGHT, &file);
    sf::Vector2u size = pic.getSize();
    for (int x = 0; x < size.x; x++) {
        for (int y = 0; y < size.y; y++) {
            File::writeColour(pic.getPixel(x, y), &file);
        }
    }
    File::writeInt(images.size(), &file);
    root->write(&file, sf::Vector2u());
    // free the shit.
    images.clear();
    return 0;
}
