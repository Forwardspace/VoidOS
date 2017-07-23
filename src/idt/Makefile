CFLAGS=-ffreestanding -std=c++11 -O2 -Wall -Wextra

GPPDIR=/home/george/Desktop/VoidOS2/VOIDCC/bin/i386-elf-g++

FINOBJ=/home/george/Desktop/VoidOS2/VoidOS/finals

all:
	$(GPPDIR) -c idtload.cpp -o idtload.o $(CFLAGS)
	$(GPPDIR) -c isrs.cpp -o isrs.o $(CFLAGS)
	nasm -felf32 isrs.asm -o asmisrs.o

debug:
	$(GPPDIR) -g -c idtload.cpp -o idtload.o $(CFLAGS)
	$(GPPDIR) -g -c isrs.cpp -o isrs.o $(CFLAGS)
	nasm -felf32 isrs.asm -o asmisrs.o

#Note that this doesn't, of course, link, but it sends the files up for linking
link:
	mv *.o $(FINOBJ)
