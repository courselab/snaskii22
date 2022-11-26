##	Copyright (c) 2022 - CCOS ICMC-USP
##	
##	This file is part of Snaskii22.
##	Snaskii22 is based on Snaskii, available at
##	https://github.com/courselab/snaskii.
##	
##	Snaskii22 is free software: you can redistribute it and/or modify
##	it under the terms of the GNU General Public License as published by
##	the Free Software Foundation, either version 3 of the License, or
##	(at your option) any later version.
##	
##	This program is distributed in the hope that it will be useful,
##	but WITHOUT ANY WARRANTY; without even the implied warranty of
##	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##	GNU General Public License for more details.
##	
##	You should have received a copy of the GNU General Public License
##	along with this program.  If not, see <http://www.gnu.org/licenses/>.

AM_CPPFLAGS = @CPP_FLAGS@ -DDATADIR=\"@datarootdir@\" -DBINDIR=\"@bindir@\"
AM_CFLAGS =   @C_FLAGS@ 
AM_LDFLAGS =  @LD_FLAGS@   

bin_PROGRAMS = snaskii.bin

snaskii_bin_SOURCES = snaskii.c utils.c  utils.h 

bin_SCRIPTS = snaskii

snaskii_bin_CC = @PTHREAD_CC@
snaskii_bin_CFLAGS = @PTHREAD_CFLAGS@ 
snaskii_bin_LDADD = -lncurses $(LIBOBJS) @PTHREAD_LIBS@ 

## This is a provision for build-time test.
##
## Briefly, the installed binary foo should read some installed data files.
## In order to be able to test the project without installing it, we want
## the non installed binary to read the non-installed data files, instead.
## To that end, use a wrapper script foo.sh that evokes the real binary 
## foo.bin with appropriate command-line options to overwrite the data file
## path. The installation procedure, then,copies foo.bin into the binary
## installation path and renames it to foo.

# This will produce the script snaskii, which evokes snaskii.bin

snaskii : snaskii.sh
	cp $< $@
	chmod u+x $@

# This install snaskii.bin and rename it snaskii.

install-exec-hook: 
	cd $(DESTDIR)/$(bindir) && mv $(bin_PROGRAMS) $(bin_SCRIPTS)

# This uninstall the binary

uninstall-hook:
	rm -f $(DESTDIR)/$(bindir)/$(bin_SCRIPTS)

# This removes the wrapper script.

clean-local:
	rm -f $(bin_SCRIPTS)



