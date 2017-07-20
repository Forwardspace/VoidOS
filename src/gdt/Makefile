CFLAGS=-ffreestanding -std=c++11 -O2 -Wall -Wextra

GPPDIR=/home/george/Desktop/VoidOS2/VOIDCC/bin/i386-elf-g++

FINOBJ=/home/george/Desktop/VoidOS2/VoidOS/finals

all:
	$(GPPDIR) -c gdt.cpp -o gdt.o $(CFLAGS)
	nasm -felf32 reloadgdt.asm -o reloadgdt.o

debug:
	$(GPPDIR) -g -c gdt.cpp -o gdt.o $(CFLAGS)
	nasm -felf32 reloadgdt.asm -o reloadgdt.o

#Note that this doesn't, of course, link, but it sends the files up for linking
link:
	mv gdt.o $(FINOBJ)
	mv reloadgdt.o $(FINOBJ) 
