#include "ImageNode.hh"
#include <iostream>
#include <cstring>
#include "File.hh"

ImageNode::ImageNode(char const *filename) {
    this->loadFromFile(filename);
    // TODO: process the name to make it shorter.
    this->name = filename;
}

int ImageNode::addChild(ImageNode *child, sf::Vector2u bounds) {
    if (bounds.x > 9999) bounds.x = 0;
    if (bounds.y > 9999) bounds.y = 0;
    sf::Vector2u identity(1, 1);
    sf::Vector2u size = this->getSize() + identity;
    sf::Vector2u childSize = child->getSize() + identity;
    if (!this->right && this->offset.x + childSize.x <= bounds.x - size.x && childSize.y <= size.y) {
        this->right = child;
        child->offset.x = size.x;
        child->offset.y = 0;
        return true;
    }
    if (this->right && this->right->addChild(child, sf::Vector2u(bounds.x - size.x, size.y))) {
        return true;
    }
    if (!this->down && childSize.x <= bounds.x && childSize.y <= bounds.y - size.y) {
        this->down = child;
        child->offset.x = 0;
        child->offset.y = size.y;
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
    if (this->right) this->right->flatten(image, drawOffset + this->offset);
    if (this->down) this->down->flatten(image, drawOffset + this->offset);
}

void ImageNode::write(std::ofstream *file, sf::Vector2u drawOffset) {
    sf::Vector2u pos = this->offset + drawOffset;
    sf::Vector2u size = this->getSize();
    file->write(this->name, strlen(this->name));
    File::writeInt(pos.x, file);
    File::writeInt(pos.y, file);
    File::writeInt(size.x, file);
    File::writeInt(size.y, file);
    if (this->right) this->right->write(file, pos);
    if (this->down) this->down->write(file, pos);
}
