# Makefile.am - Top-level makefile for 'scope'.
#
# $Revision: 1.2 $  $Date: 2002/09/06 17:45:35 $
#
# Copyright (c) 2002 by Matt J. Gumbley

# Make aclocal look in config subdir for *.m4 macros when automatically
# rebuilding configure script when configure.in file changes.
ACLOCAL=aclocal -I config

SUBDIRS=src

BINARIES=scope

EXTRA_DIST=

tags:
	( cd src ; make tags )
