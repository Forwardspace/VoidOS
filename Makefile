all:
	cd src && $(MAKE) all

debug:
	cd src && $(MAKE) debug

link:
	#This is it: finally complete the compilation!
	cd finals && $(MAKE) link

final:
	#You know what, I just love Makefiles...
	cd build && $(MAKE) final
