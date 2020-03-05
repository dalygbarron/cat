#include "main/Options.hh"
#include "main/PicTree.hh"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>


Options getOptions(int argc, char **argv) {
    Options options;
    int opt;
    while ((opt = getopt(argc, argv, "hvi:o:s:d:f:")) != -1) {
        switch (opt) {
            case 'h':
                options.help = true;
                break;
            case 'v':
                options.version = true;
                break;
            case 'i':
                options.image = optarg;
                break;
            case 'o':
                options.output = optarg;
                break;
            case 's':
                options.style = optarg;
                break;
            case 'd':
                // TODO: parse dimensions into vector.
                break;
            case 'f':
                options.fonts.emplace(options.fonts.end(), optarg);
                break;
        }
    }
    for (int i = optind; i < argc; i++) {
        options.pics.emplace(options.pics.end(), argv[i]);
    }
    return options;
}

int main(int argc, char **argv) {
    // Read input.
    Options options = getOptions(argc, argv);
    std::vector
    // Convert fonts.
    // Sort Pictures
    std::sort(
        options.pics.begin(),
        options.pics.end(),
        [](ImageFile const &a, ImageFile const &b) {
            return a.getLongestSide() > b.getLongestSide();
        }
    );
    if (options.pics.size() > 0) {
        // Position Pictures.
        PicTree tree(options.dimensions, options.pics[0]);
        for (
            auto it = ++(options.pics.begin());
            it != options.pics.end();
            it++
        ) {
            int result = tree.insert(*it);
            if (!result) {
                std::cerr << "Couldn't fit all the pics sorry: " << (*it).name << std::endl;
            }
        }
        // Render Image.
        sf::Image image;
        image.create(
            options.dimensions.x,
            options.dimensions.y,
            sf::Color::Transparent
        );
        tree.render(image);
        if (!image.saveToFile(options.image)) {
            std::cerr << "Could not save to image file " << options.image <<
                std::endl;
        }
    }
    // Write to file.
    return 0;
}
