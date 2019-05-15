#include "File.hh"


void File::writeInt(uint32_t value, std::ofstream *file) {
    char bytes[4];
    bytes[0] = (value & 0xff000000) >> 24;
    bytes[1] = (value & 0xff0000) >> 16;
    bytes[2] = (value & 0xff00) >> 8;
    bytes[3] = value & 0xff;
    file->write(bytes, 4);
}

uint32_t File::readInt(std::ifstream *file) {
    char bytes[4];
    file->read(bytes, 4);
    uint32_t value = 0;
    value += bytes[0] << 24;
    value += bytes[1] << 16;
    value += bytes[2] << 8;
    value += bytes[3];
    return value;
}

void File::writeColour(sf::Color value, std::ofstream *file) {
    File::writeInt(value.toInteger(), file);
}

sf::Color File::readColour(std::ifstream *file) {
    return sf::Color(File::readInt(file));
}
