#include "ImageNode.hh"
#include <iostream>

ImageNode::ImageNode(char const *filename) {
    this->loadFromFile(filename);
    // TODO: process the name to make it shorter.
    this->name = filename;
}

int ImageNode::addChild(ImageNode *child, sf::Vector2u bounds) {
    if (bounds.x > 9999) bounds.x = 0;
    if (bounds.y > 9999) bounds.y = 0;
    sf::Vector2u size = this->getSize();
    sf::Vector2u childSize = child->getSize();
    if (!this->right && this->offset.x + childSize.x <= bounds.x - size.x && childSize.y <= size.y) {
        this->right = child;
        child->offset.x = size.x;
        child->offset.y = 0;
        return true;
    }
    if (!this->down && childSize.x <= bounds.x && childSize.y <= bounds.y - size.y) {
        this->down = child;
        child->offset.x = 0;
        child->offset.y = size.y;
        return true;
    }
    if (this->right && this->right->addChild(child, sf::Vector2u(bounds.x - size.x, size.y))) {
        return true;
    }
    if (this->down && this->down->addChild(child, sf::Vector2u(bounds.x, bounds.y - size.y))) {
        return true;
    }
    return false;
}


void ImageNode::flatten(sf::Image *image, sf::Vector2u drawOffset) {
    sf::Vector2u size = this->getSize();
    for (int x = 0; x < size.x; x++) {
        for (int y = 0; y < size.y; y++) {
            image->setPixel(this->offset.x + drawOffset.x + x, this->offset.y + drawOffset.y + y, this->getPixel(x, y));
        }
    }
    //for (int x = 0; x < size.x; x++) image->setPixel(drawOffset.x + this->offset.x + x, drawOffset.y + this->offset.y, sf::Color(255, 0, 0, 255));
    //for (int y = 0; y < size.y; y++) image->setPixel(drawOffset.x + this->offset.x, drawOffset.y + this->offset.y + y, sf::Color(255, 0, 0, 255));
    if (this->right) this->right->flatten(image, drawOffset + this->offset);
    if (this->down) this->down->flatten(image, drawOffset + this->offset);
}
