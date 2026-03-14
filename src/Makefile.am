# Makefile.am - Builds 'scope' program.
#
# $Revision: 1.2 $  $Date: 2002/09/06 17:33:09 $
#
# Copyright (c) 2002 by Matt J. Gumbley

AM_CFLAGS=-Wall

bin_PROGRAMS=scope

scope_SOURCES=asy.c asy.h defs.h global.h scope.c util.c util.h

tags: ctags
ctags:
	rm -f TAGS tags
	ctags *.[ch]

