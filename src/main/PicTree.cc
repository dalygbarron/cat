#include "PicTree.hh"

PicTree::PicTree(sf::Vector2u space, ImageFile const &image):
    space(space),
    image(image)
{
    // nothing else.
}

PicTree::~PicTree() {
    if (this->right) delete this->right;
    if (this->bottom) delete this->bottom;
}

int PicTree::insert(ImageFile const &image) {
    sf::Vector2u size = this->image.image.getSize();
    sf::Vector2u childSize = image.image.getSize();
    if (childSize.x <= this->space.x - size.x && childSize.y <= size.y) {
        if (this->right) {
            int result = this->right->insert(image);
            if (result) return true;
        } else {
            this->right = new PicTree(
                sf::Vector2u(this->space.x - size.x, size.y),
                image
            );
            return true;
        }
    }
    if (childSize.x <= this->space.x &&
        childSize.y <= this->space.y - size.y
    ) {
        if (this->bottom) {
            int result = this->bottom->insert(image);
            if (result) return true;
        } else {
            this->bottom = new PicTree(
                sf::Vector2u(this->space.x, this->space.y - size.y),
                image
            );
            return true;
        }
    }
    return false;
}

void PicTree::render(sf::Image &image, sf::Vector2u offset) {
    image.copy(this->image.image, offset.x, offset.y);
    sf::Vector2u size = this->image.image.getSize();
    if (this->right) {
        this->right->render(image, sf::Vector2u(offset.x + size.x, offset.y));
    }
    if (this->bottom) {
        this->bottom->render(image, sf::Vector2u(offset.x, offset.y + size.y));
    }
}
