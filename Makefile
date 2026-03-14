#
# The main Makefile for the Scope serial line analyser.
# MJG 25/01/99
# Last edit 20/02/02

.EXPORT_ALL_VARIABLES:

#
# Where to put the program/man page? Change this to wherever you like...
#
PREFIX = /usr/local

#
# Flags for Linux builds
#
# (nothing special)

VERSION = 0.02
NAME = scope-$(VERSION)
DATE = `/bin/date +%d-%m-%Y`

all : 
	@cd src && make

install :
	@cd src && make install

remove :
	@cd src && make remove

clean:
	@echo Cleaning...
	@cd src && make clean

realclean:
	@echo Really Cleaning...
	@cd src && make realclean

archive :
	@make clean
	@cd ..; rm -f $(NAME).tar.gz; tar zchvf $(NAME).tar.gz $(NAME)


backup :
	@make archive
	@echo "Insert zip disk, press return"
	@read TRASH
	@mount /zip
	@cp ../$(NAME).tar.gz /zip/$(NAME)-$(DATE).tar.gz
	@umount /zip

test:
	@echo "Date is $$DATE"
