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
		-DDEBUG=1

targets = $(PACKAGE)

all: $(targets)
clean:
	$(RM) $(targets) $($(PACKAGE)_objs)
depend:
	mkdep $(CFLAGS) $($(PACKAGE)_objs:.o=.c)


$(PACKAGE)_objs = main.o input.o config.o
$(PACKAGE)_libs = -lavl
$(PACKAGE)_ldflags = 

$(PACKAGE): $($(PACKAGE)_objs)
	$(CC) $(LDFLAGS) $($@_ldflags) -o $@ $($@_objs) $($@_libs)

.include ".depend"
