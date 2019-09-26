# Rat
Packs together a set of images into a single image, and outputs an xml file
which tells you where each sub image is stored within the image.

Allows you to create texture atlases for hardware rendered games and stuff like
that.

## Format
```
<pack image="output.png">
    <rat name="bongo.png" x="10" y="3" width="32" height="64" />
    <rat name="bingo.png" x="42" y="3" width="32" height="64" />
</pack>
```
First you have a top level pack object with the attribute image giving the
relative location of the outputted image file
