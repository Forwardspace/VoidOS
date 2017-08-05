CFLAGS=-ffreestanding -std=c++11 -O0 -w#-Wall -Wextra

GPPDIR=/home/george/Desktop/VoidOS2/VOIDCC/bin/i686-elf-g++

FINOBJ=/home/george/Desktop/VoidOS2/VoidOS/finals

all:
	$(GPPDIR) -c alloc.cpp -o alloc.o $(CFLAGS)
	$(GPPDIR) -c new.cpp -o new.o $(CFLAGS)

debug:
	$(GPPDIR) -g -c alloc.cpp -o alloc.o $(CFLAGS)
	$(GPPDIR) -g -c new.cpp -o new.o $(CFLAGS)

link:
	mv *.o $(FINOBJ) 
