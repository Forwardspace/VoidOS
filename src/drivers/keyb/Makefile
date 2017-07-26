CFLAGS=-ffreestanding -std=c++11 -O0 -w#-Wall -Wextra

GPPDIR=/home/george/Desktop/VoidOS2/VOIDCC/bin/i686-elf-g++

FINOBJ=/home/george/Desktop/VoidOS2/VoidOS/finals

all:
	$(GPPDIR) -c keyb.cpp -o keyb.o $(CFLAGS)

debug:
	$(GPPDIR) -g -c keyb.cpp -o keyb.o $(CFLAGS)

link:
	mv *.o $(FINOBJ) 
