CFLAGS=-ffreestanding -std=c++11 -O0 -w#-Wall -Wextra

GPPDIR=/home/george/Desktop/VoidOS2/VOIDCC/bin/i686-elf-g++

FINOBJ=/home/george/Desktop/VoidOS2/VoidOS/finals

all:
	$(GPPDIR) -c page.cpp -o page.o $(CFLAGS)
	nasm -felf32 pagemisc.asm -o pagemisc.o

debug:
	$(GPPDIR) -g -c page.cpp -o page.o $(CFLAGS)
	nasm -felf32 pagemisc.asm -o pagemisc.o

link:
	mv *.o $(FINOBJ) 
