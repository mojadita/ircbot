# $Id$
# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: Sat Aug  8 20:00:52 EEST 2015
# Copyright: (C) 2015 LUIS COLORADO.  ALL RIGHTS RESERVED.

PREFIX = /usr/local
PACKAGE = ircbot
VERSION = v0.0
DEFAULT_PORT = 6667

RM = rm -f
CFLAGS+= -DPREFIX=\"$(PREFIX)\" -DPACKAGE=\"$(PACKAGE)\" \
		-DVERSION=\"$(VERSION)\" -DDEFAULT_PORT=$(DEFAULT_PORT) \
		-DDEBUG=1 -O0 -g3
LDFLAGS+= -g3

targets = $(PACKAGE) test_callback test_atoms

all: $(targets)
clean:
	$(RM) $(targets) $(OBJS)
depend:
	mkdep $(CFLAGS) $(SOURCES)


$(PACKAGE)_objs = main.o input.o config.o input_cb.o
OBJS+=$($(PACKAGE)_objs)
$(PACKAGE)_src = $($(PACKAGE)_objs:.o=.c)
SOURCES += $($(PACKAGE)_src)
$(PACKAGE)_libs = -lavl
$(PACKAGE)_ldflags = 

$(PACKAGE): $($(PACKAGE)_objs)
	$(CC) $(LDFLAGS) $($@_ldflags) -o $@ $($@_objs) $($@_libs)

test_callback_objs = test_callback.o config.o callback.o
OBJS+=$(test_callback_objs)
test_callback_src = $(test_callback_objs:.o=.c)
SOURCES += $(test_callback_src)
test_callback_libs = -lpthread
test_callback_ldflags = -pthread

test_callback: $(test_callback_objs)
	$(CC) $(LDFLAGS) $($@_ldflags) -o $@ $($@_objs) $($@_libs)

test_atoms_objs = test_atoms.o atoms.o
OBJS+=$(test_atoms_objs)
test_atoms_src = $(test_atoms_objs:.o=.c)
SOURCES += $(test_atoms_src)
test_atoms_libs = -lavl
test_callback_ldflags =

test_atoms: $(test_atoms_objs)
	$(CC) $(LDFLAGS) $($@_ldflags) -o $@ $($@_objs) $($@_libs)

.include ".depend"
