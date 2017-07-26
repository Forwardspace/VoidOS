OBJS=$(wildcard *.o)

GPPDIR=/home/george/Desktop/VoidOS2/VOIDCC/bin/i686-elf-g++
FINALDIR=/home/george/Desktop/VoidOS2/VoidOS/build/isodir/boot

LNKSCRIPT=../linkerscript.ld

link:
	$(GPPDIR) -T $(LNKSCRIPT) -o voidos.bin -ffreestanding -fno-rtti -fno-exceptions -O2 -nostdlib $(OBJS) -lgcc
	mv voidos.bin $(FINALDIR) 
	rm $(OBJS) 
