CFLAGS=-ffreestanding -std=c++11 -O2 -Wall -Wextra

GPPDIR=/home/george/Desktop/VoidOS2/VOIDCC/bin/i386-elf-g++

FINOBJ=/home/george/Desktop/VoidOS2/VoidOS/finals

all:
	$(GPPDIR) -c boot.cpp -o bootcpp.o $(CFLAGS)
	nasm -felf32 boot.asm -o bootasm.o

debug:
	$(GPPDIR) -g -c boot.cpp -o bootcpp.o $(CFLAGS)
	nasm -felf32 boot.asm -o bootasm.o

#Note that this doesn't, of course, link, but it sends the files up for linking
link:
	mv bootcpp.o $(FINOBJ)
	mv bootasm.o $(FINOBJ) 
