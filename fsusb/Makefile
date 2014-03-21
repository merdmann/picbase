# $Id: Makefile 258 2011-01-15 16:38:47Z merdmann $ 
#
# This file is part of fsusb_picdem
#
# fsusb_picdem is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# fsusb_picdem is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with fsusb_picdem; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301, USA

OPTS=-Wall -D_GNU_SOURCE
OBJS=fsusb.o rjlhex.o memimg.o

CC=gcc
CFLAGS=$(OPTS)
LDFLAGS=-lusb

# Needed for static linking under OS X:
# LDFLAGS=-lusb -lIOKit -framework CoreFoundation

all: ../bin/fsusb

../bin/fsusb: main.o $(OBJS)
	$(CC) $(CFLAGS) -o ../bin/fsusb main.o $(OBJS) $(LDFLAGS)

deps:


clean:
	$(RM) ../bin/fsusb *.o *~ 
