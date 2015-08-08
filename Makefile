# $Id$
# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: Sat Aug  8 20:00:52 EEST 2015
# Copyright: (C) 2015 LUIS COLORADO.  ALL RIGHTS RESERVED.

PREFIX = /usr/local
PACKAGE = ircbot
VERSION = v0.0

RM = rm -f
CFLAGS+= -DPREFIX=\"$(PREFIX)\" -DPACKAGE=\"$(PACKAGE)\" \
		-DVERSION=\"$(VERSION)\"

targets = $(PACKAGE)

all: $(targets)
clean:
	$(RM) $(targets) $($(PACKAGE)_objs)


$(PACKAGE)_objs = main.o input.o config.o
$(PACKAGE)_libs =
$(PACKAGE)_ldflags = 

$(PACKAGE): $($(PACKAGE)_objs)
	$(CC) $(LDFLAGS) $($@_ldflags) -o $@ $($@_objs) $($@_libs)
