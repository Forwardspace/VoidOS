CFLAGS=-ffreestanding -std=c++11 -O2 -Wall -Wextra -fno-exceptions

GPPDIR=/home/george/Desktop/VoidOS2/VOIDCC/bin/i686-elf-g++

FINOBJ=/home/george/Desktop/VoidOS2/VoidOS/finals

all:
	$(GPPDIR) -c simplevga.cpp -o smpvgadriver.o $(CFLAGS)

debug:
	$(GPPDIR) -g -c simplevga.cpp -o smpvgadriver.o $(CFLAGS)

link:
	mv smpvgadriver.o $(FINOBJ) 
