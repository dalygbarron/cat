#include "ImageFile.hh"
#include <iostream>
#include <cmath>

ImageFile::ImageFile(char const *file) {
    // TODO: only use actual file name without extension here.
    this->name = file;
    if (!this->image.loadFromFile(file)) {
        std::cerr << file << " is not a valid image file" << std::endl;
        throw new std::invalid_argument("bad image file");
    }
}

ImageFile::ImageFile(FontInstance const &font) {
    this->name = font.name;
    sf::Glyph const *glyphs[256];
    sf::Vector2u bounds;
    for (int i = 0; i < 256; i++) {
        glyphs[i] = &font.font.getGlyph(i, font.size, false);
        if (glyphs[i]->textureRect.width > bounds.x) {
            bounds.x = glyphs[i]->textureRect.width;
        }
        if (glyphs[i]->textureRect.height > bounds.y) {
            bounds.y = glyphs[i]->textureRect.height;
        }
    }
    this->image.create(bounds.x * 16, bounds.y * 16, sf::Color::Transparent);
    sf::Image fontImage = font.font.getTexture(font.size).copyToImage();
    for (int i = 0; i < 256; i++) {
        sf::IntRect sprite = glyphs[i]->textureRect;
        if (sprite.width != 0 && sprite.height != 0) {
            this->image.copy(
                fontImage,
                (i % 16) * bounds.x,
                (i / 16) * bounds.y,
                glyphs[i]->textureRect
            );
        }
    }
}

int ImageFile::getLongestSide() const {
    sf::Vector2u size = this->image.getSize();
    return fmax(size.x, size.y);
}
