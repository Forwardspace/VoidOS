OBJS=$(wildcard *.o)

GPPDIR=/home/george/Desktop/VoidOS2/VOIDCC/bin/i686-elf-g++
FINALDIR=/home/george/Desktop/VoidOS2/VoidOS/build/isodir/boot

LNKSCRIPT=../linkerscript.ld

CRTIN=../src/crt
CRTOU=/home/george/Desktop/VoidOS2/VOIDCC/lib/gcc/i686-elf/5.4.0

link:
	$(GPPDIR) -T $(LNKSCRIPT) -o voidos.bin -ffreestanding -fno-rtti -fno-exceptions -O2 -nostdlib $(CRTIN)/crti.o $(CRTOU)/crtbegin.o $(OBJS) $(CRTOU)/crtend.o $(CRTIN)/crtn.o -lgcc
	mv voidos.bin $(FINALDIR) 
	rm $(OBJS) 
