#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "File.hh"

#define NAME_BUFFER_SIZE 256

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
    std::ifstream file(argv[1], std::ios::in | std::ios::binary);
    int fileSize = File::readInt(&file);
    std::cout << fileSize << std::endl;
    char *fileContent = new char[fileSize];
    file.read(fileContent, fileSize);
    int n = File::readInt(&file);
    sf::IntRect *rects = new sf::IntRect[n];
    for (int i = 0; i < n; i++) {
        char name[NAME_BUFFER_SIZE];
        file.getline(name, NAME_BUFFER_SIZE, 0);
        file.putback(0);
        rects[i].left = File::readInt(&file);
        rects[i].top = File::readInt(&file);
        rects[i].width = File::readInt(&file);
        rects[i].height = File::readInt(&file);
    }
    // set up rendering stuff.
    sf::Texture pic;
    pic.loadFromMemory(fileContent, fileSize);
    pic.setSmooth(true);
    sf::RectangleShape shape(sf::Vector2f(640, 480));
    shape.setTexture(&pic);
    sf::RectangleShape zoom(sf::Vector2f(640, 480));
    zoom.setTexture(&pic);
    zoom.setPosition(640, 0);
    // display some stuff.
    sf::RenderWindow window(sf::VideoMode(1280, 480), "Rat Viewer");
    window.setFramerateLimit(5);
    int i = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        zoom.setTextureRect(rects[i]);
        window.clear();
        window.draw(shape);
        window.draw(zoom);
        window.display();
        if (i++ >= n) i = 0;
    }

    return 0;
}
