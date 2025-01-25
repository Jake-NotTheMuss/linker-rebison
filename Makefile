
all:
	cd dumptable && sh gen-tables.sh
	cd rebison && $(MAKE)
