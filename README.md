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
rat src/images/bullets bin/data/bullets.rat
```
Which would load all the images in src/images/bullets and put them in together in bullets.rat.
