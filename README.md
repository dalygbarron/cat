# Rat
Packs together a set of images into a single image, and outputs an xml file
which tells you where each sub image is stored within the image.

Allows you to create texture atlases for hardware rendered games and stuff like
that.

## Options
`-h` shows help.

`-v` shows version and nothing else.

`-o <outputImage>` specifies the image file the final pack should go to.
Requied.

`-f <outputFile>` specifies the data output file that should describe the
locations in the pack image.

`-w <xml|json>` specifies the output data file format to use. Currently only
choices are xml and json. For more details on these formats see the **Formats**
section.

`-d <width>:<height>` specifies the required dimensions in the final image. If
this is not specifies then it defaults to 512:512.

`-g <name>:<width>:<height>` defines an empty "ghost" sprite to add into the
sheet. Name is the name given to it in the xml file.

`-c longest-side|total-sides` specifies the type of comparison to use for
sorting when packing. total-sides is more normal, but longest-side can be good
if you have some images that are long and thin that otherwise screw everthing
up. total-sides is the default if not specified.

## Formats
Currently there are only two choices of data output. If you need something more
bespoke then view the **Creating new Formats** section for details on making
your own.

### XML
```
<pack image="output.png" version="1.1.1">
    <rat name="bongo" x="10" y="3" w="32" h="64" />
    <rat name="bingo" x="42" y="3" w="32" h="64" />
</pack>
```
First you have a top level pack object with the attribute image giving the
relative location of the outputted image file, then you have a bunch of rat
objects which have a name and then define the rectangle they point to.

### JSON
```
{
    "image": "output.png",
    "version": "1.1.1",
    "rats": [
        {"name": "bongo", "x": 10, "y": 3, "w": 32, "h": 64},
        {"name": "bingo", "x": 42, "y": 3, "w": 32, "h": 64}
    ]
}
```
