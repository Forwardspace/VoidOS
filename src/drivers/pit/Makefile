CFLAGS=-ffreestanding -std=c++11 -O2 -Wall -Wextra -fno-exceptions

GPPDIR=/home/george/Desktop/VoidOS2/VOIDCC/bin/i686-elf-g++

FINOBJ=/home/george/Desktop/VoidOS2/VoidOS/finals

all:
	$(GPPDIR) -c pit.cpp -o pit.o $(CFLAGS)

debug:
	$(GPPDIR) -g -c pit.cpp -o pit.o $(CFLAGS)

#Note that this doesn't, of course, link, but it sends the files up for linking
link:
	mv pit.o $(FINOBJ)

