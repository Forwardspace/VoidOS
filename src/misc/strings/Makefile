CFLAGS=-ffreestanding -std=c++11 -O2 -Wall -Wextra

GPPDIR=/home/george/Desktop/VoidOS2/VOIDCC/bin/i386-elf-g++

FINOBJ=/home/george/Desktop/VoidOS2/VoidOS/finals

all:
	$(GPPDIR) -c stringfuncts.cpp -o stringfuncts.o $(CFLAGS)

debug:
	$(GPPDIR) -g -c stringfuncts.cpp -o stringfuncts.o $(CFLAGS)

link:
	mv stringfuncts.o $(FINOBJ) 
