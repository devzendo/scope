#
# Flags for Linux builds

CC = gcc
CFLAGS = -g -Wall -DUNIX -DLINUX -ansi -fomit-frame-pointer -fno-strength-reduce -DVERSION=$(VERSION)

PROGS = scope 

all : $(PROGS) 


install : $(PROGS)
	install $(PROGS) $(PREFIX)/bin

scope : scope.o asy.o util.o
	$(CC) -o scope scope.o asy.o util.o

remove: 
	@./uninstall $(PREFIX) $(PROGS)

celan:
clean:
	@echo Cleaning...
	rm -f *.o *.bak core fred

realclean:
	@echo Really Cleaning...
	@make clean
	rm -f $(PROGS)


