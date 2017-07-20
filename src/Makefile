all:
	cd bootup && $(MAKE) all && $(MAKE) link
	cd drivers && $(MAKE) all
	cd misc && $(MAKE) all
	cd gdt && $(MAKE) all && $(MAKE) link
debug:
	cd bootup && $(MAKE) debug && $(MAKE) link
	cd drivers && $(MAKE) debug
	cd misc && $(MAKE) debug
	cd gdt && $(MAKE) debug && $(MAKE) link
