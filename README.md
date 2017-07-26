# VoidOS
A simple OS, don't expect much.
##Version 0.0.6
(Rewritten)

Added memory allocation and a working keyboard driver with getc() and gets() (there is a test in boot.cpp). Also, the cursor now moves when typing.

### Possible uses
* Still none
### Features
* Printing on screen
* Halting
* Scrolling (Yes, truly the pinnacle of software engineering!)
* Now prints random characters when you press a key!

## Installation
(You need to have a i386-elf cross compiler installed. Also I just use absolute file paths, so you need to have the same file system and structure, have the same username etc. (preferably just be me))

### Linux
Run `make all link final`. You can now burn the `voidos.iso` file to a USB drive or a CD, or simulate it, if you have qemu installed, by running `./simulate.sh`. Enjoy its full uselessness!

### Windows
Install linux and run steps for Linux.

### Mac OS X
Buy a Windows PC and see steps for Windows.
