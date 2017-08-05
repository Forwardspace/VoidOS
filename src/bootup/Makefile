CFLAGS=-ffreestanding -std=c++11 -O0 -Wall -Wextra -fno-exceptions

GPPDIR=/home/george/Desktop/VoidOS2/VOIDCC/bin/i686-elf-g++

FINOBJ=/home/george/Desktop/VoidOS2/VoidOS/finals

all:
	$(GPPDIR) -c boot.cpp -o bootcpp.o $(CFLAGS)
	#$(GPPDIR) -c icxxabi.cpp -o icxxabi.o $(CFLAGS)
	nasm -felf32 boot.asm -o bootasm.o

debug:
	$(GPPDIR) -g -c boot.cpp -o bootcpp.o $(CFLAGS)
	#$(GPPDIR) -g -c icxxabi.cpp -o icxxabi.o $(CFLAGS)
	nasm -felf32 boot.asm -o bootasm.o

#Note that this doesn't, of course, link, but it sends the files up for linking
link:
	mv *.o $(FINOBJ)
