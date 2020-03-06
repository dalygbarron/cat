Ok so we need to add fonts. They should not be added as single seperate sprites
for each character, as we can draw them more efficiently in a game if they are
all together and we can just access them by a byte.

Yeah so basically for each font we create a single image with all of it's stuff
in it, and give it the name that is given for the font, and then in the xml, as
well as that image which is a completely normal rat, we also have a special
font entry which stores the name of the rat, and it's parameters like the space
between each character. There is no need to store vertical offset as this can
be rendered into the sprites at the cost of some space.
