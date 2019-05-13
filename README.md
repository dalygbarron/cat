# Rat
Packs a bunch of textures into a single image and also provides metadata about where each image is.

All of the output is put together in one big file with metadata and image data and it is some kind of home made binary
file type.

## Format
```
4 bytes: sheet width.
4 bytes: sheet height.
sheet width * sheet height * 4 bytes: pixel data of whole spritesheet.
4 bytes: number of images in the sheet.
(for each image)
    null terminated string: name of the image
    4 bytes: x position of top left of image.
    4 bytes: y position of top left of image.
    4 bytes: image width.
    4 bytes: image height.
```

## invocation
To use this from the commandline it should be something along the lines of:
```
rat bin/data/bullets.rat images/bullets/*.png
```
Which would load all the images in src/images/bullets and put them in together in bullets.rat.


## TODO
Try this as it is, but if it's garbage and annoying, maybe consider dropping the bin packing entirely and using a
configuration ini file that defines rows by size and sets the bullets that are placed within that row. It will still
output to the same format though.
