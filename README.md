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

The data 

## Options
`-h` shows help.

`-v` shows version and nothing else.

`-o <outputImage>` specifies the image file the final pack should go to.
Requied.

-f <outputFile> specifies the data output file that should describe the
locations in the pack image.

`-d <width>:<height>` specifies the required dimensions in the final image. If
this is not specifies then it defaults to 512:512.

`-g <name>:<width>:<height>` defines an empty sprite to add into the sheet.
Name is the name given to it in the xml file.

`-c longest-side|total-sides` specifies the type of comparison to use for
sorting when packing. total-sides is more normal, but longest-side can be good
if you have some images that are long and thin that otherwise screw everthing
up. total-sides is the default if not specified.

