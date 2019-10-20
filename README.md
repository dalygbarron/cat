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

So you get an object with an image property telling you the path to the related
image, a version property telling you the version of the program it was made
with, and a rats property that has an array of all the rats in the pack.

Each rat is an object with a name and it's dimensions.


## Creating New Formats
While the two given output formats are reasonably good, there are obviously
going to be cases still in which you are going to want to use some custom
format for your own game engine or whatever, and there may also be cases where
there is a perfectly good and general format which has been neglected.

The code has been written in such a way that it should be as easy as possible
to add a new output format and recompile.

 1. Go to write.h and copy one of the function definitions, renaming it to
   represent the name of your new format.

 2. Go to write.c and write the implementation of your new format.

 3. Go to util.c and add the name of your format to the `parseWrite` function so
   it can be requested from the commandline.

 4. Go to main.c add information about your new mode to the help and usage
   functions (if you want).

 5. recompile and reinstall if necessary.

### Implementation
```
int writeJson(
    FILE *out,
    char const *imageFile,
    char const *version,
    struct Picture **pics,
    int n
)
```
Here is the signiature of a write function. 
 - out is the file to which the output is to be written.
 - imageFile is the relative path to the associated image file.
 - version is the current version string of the program.
 - pics is a list of pointers to the pictures going into the pack
 - n is the number of items in pics

You may also want to look at Picture.h to see what information is stored in
a Picture struct. Based on this information and the existing write functions it
should be easy enough to implement something useful for you.
