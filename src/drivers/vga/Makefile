CFLAGS=-ffreestanding -std=c++11 -O2 -Wall -Wextra

GPPDIR=/home/george/Desktop/VoidOS2/VOIDCC/bin/i386-elf-g++

FINOBJ=/home/george/Desktop/VoidOS2/VoidOS/finals

all:
	$(GPPDIR) -c simplevga.cpp -o smpvgadriver.o $(CFLAGS)

debug:
	$(GPPDIR) -g -c simplevga.cpp -o smpvgadriver.o $(CFLAGS)

link:
	mv smpvgadriver.o $(FINOBJ) 
