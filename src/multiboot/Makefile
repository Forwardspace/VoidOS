CFLAGS=-ffreestanding -std=c++11 -O2 -fno-exceptions -w#-Wall -Wextra

GPPDIR=/home/george/Desktop/VoidOS2/VOIDCC/bin/i386-elf-g++

FINOBJ=/home/george/Desktop/VoidOS2/VoidOS/finals

all:
	$(GPPDIR) -c modload.cpp -o modload.o $(CFLAGS)

debug:
	$(GPPDIR) -g -c modload.cpp -o modload.o $(CFLAGS)

#Note that this doesn't, of course, link, but it sends the files up for linking
link:
	mv modload.o $(FINOBJ)

