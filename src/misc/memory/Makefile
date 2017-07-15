CFLAGS=-ffreestanding -std=c++11 -O2 -Wall -Wextra

GPPDIR=/home/george/Desktop/VoidOS2/VOIDCC/bin/i386-elf-g++

FINOBJ=/home/george/Desktop/VoidOS2/VoidOS/finals

all:
	$(GPPDIR) -c memfuncts.cpp -o memfuncts.o $(CFLAGS)

debug:
	$(GPPDIR) -g -c memfuncts.cpp -o memfuncts.o $(CFLAGS)

link:
	mv memfuncts.o $(FINOBJ) 
