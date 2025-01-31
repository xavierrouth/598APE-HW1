# 598APE-HW1

This repository contains code for homework 1 of 598APE.

In particular, this repository is an implementation of a Raytracer.

To compile the program run:
```bash
make -j
```

To clean existing build artifacts run:
```bash
make clean
```

This program assumes the following are installed on your machine:
* A working C++ compiler (g++ is assumed in the Makefile)
* make
* ImageMagick (for importing and exporting non-ppm images)
* FFMpeg (for exporting movies from image sequences)

The raytracer program here is general and can be used to generate any number of different potential scenes.

Once compiled, one can call the raytracer program as follows:
```bash
./main.exe --help
```
