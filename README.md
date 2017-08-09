# VoidOS
A simple OS, don't expect much.
## Version 0.0.10

(Nearing version 0.1.0)

Added simple paging. (Mapped first 20 page tables, identity paging for now)  
No int 14 handler yet, though...

### Possible uses
* Still none
### Features
* Printing on screen
* Scrolling (Yes, truly the pinnacle of software engineering!)
* Now prints semi-random characters when you gets()!

## Installation
(You need to have a i686-elf cross compiler installed. Also I just use absolute file paths, so you need to have the same file system and structure, have the same username etc. (preferably just be me))

### Linux
Run `make all link final`. You can now burn the `voidos.iso` file to a USB drive or a CD, or simulate it, if you have qemu installed, by running `./simulate.sh`. Enjoy its full uselessness!

### Windows
Install linux and run steps for Linux.

### Mac OS X
Buy a Windows PC, kill your old mac with fire and see steps for Windows.
