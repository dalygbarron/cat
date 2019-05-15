#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "File.hh"

/**
 * Start of program.
 * @param argc is number of commandline arguments.
 * @param argv is the values of the commandline arguments.
 */
int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: reader inputFile" << std::endl;
        return 1;
    }
    // read in the file.
    std::ifstream file(argv[1], std::ifstream::binary);
    int width = File::readInt(&file);
    int height = File::readInt(&file);
    sf::Color *pixels;
    int n;
    pixels = new sf::Color[width * height];




    // display some stuff.
    sf::RenderWindow window(sf::VideoMode(1920, 1440), "Rat Viewer");






    return 0;
}
