# Rat Pack Texture Atlas Generator
Packs together a set of images into a single image, and outputs a data file
which tells you where each sub image is stored within the image.

The outputted data file can be one of a selection of easy to parse formats,
with the ability to easily develop output for your own format as well.

Rat Pack is used entirely from the commandline so it can be easily integrated
into an automatic workflow, and you do not need to mess around with a stupid
gui for no reason.

Also it is completely free and open source which seems to be unusual in the
field texture atlas generators.

## Install
There are no external dependencies except the standard library and the unix
standard library so all you need to do is download the source and execute
`make install` or possibly `sudo make install` from the main directory.

If you want the program to be installed into a different place than /usr/local
then you can provide the PREFIX argument to `make install`.

Obviously you do also need to have gcc and make installed.

This works for me on Ubuntu and Mac Os, I have not tried it on Cygwin but
I don't see any reason why it would not also work there.

Some people will probably be a bit spooked out by the fact that there is only
source and no binary but compiling and installing it from source is quick and
easy as hell, and it means that whenever you want to modify the functionality
of the program with custom behaviour, you can just jump into the code, mess
around with it, call `make install` again, and you have a new setup.


## Options
`-h` shows help.

`-v` shows version and nothing else.

`-e` includes file extension in individual sprite names.

`-p` inclcludes path in individual sprite names.

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
