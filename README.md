# Rat
Packs a bunch of textures into a single image and also provides metadata about where each image is.

All of the output is put together in one big file with metadata and image data and it is some kind of home made binary
file type.

![bin packed texture atlas](example.png?raw=true)


## Format
```
4 bytes: number of bytes in sheet picture.
many bytes: full data of a png file of this sheet.
4 bytes: number of images in the sheet.
(for each image)
    null terminated string: name of the image
    4 bytes: x position of top left of image.
    4 bytes: y position of top left of image.
    4 bytes: image width.
    4 bytes: image height.
```
By the way, it is always written big endian whether that is what the system normally does or not. I think, or maybe it's
small endian. I don't really know but it's consistent.

## invocation
To use this from the commandline it should be something along the lines of:
```
rat bin/data/bullets.rat images/bullets/*.png
```
Which would load all the images in src/images/bullets and put them in together in bullets.rat.
