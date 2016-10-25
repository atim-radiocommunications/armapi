########################################################################
# Created date: 22.09.2016
########################################################################

########################################################################
#
# Copyright (c) 2016 ATIM
# 
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
########################################################################

########################################################################
# Start of user section
#

# Name of output file
OUTPUT_FILE = arminfo

# User of install
USER=root
# Ip of install
IP=pi.local
# Directory of install
DIRECTORY=/usr/bin
# tty used
TTY=/dev/ttyAMA0

# Toolchain
TARGET  =
CC      = $(TARGET)gcc
OBJCOPY = $(TARGET)objcopy
AS      = $(TARGET)as
SIZE    = $(TARGET)size
OBJDUMP = $(TARGET)objdump
GDB 	= $(TARGET)gdb

# Folder of armapi
ARMAPI = ../../../bindings/c

#################################
# Start define flags
#

# Default flags for C 
UCFLAGS  = -W -Wall -Wextra -std=gnu99
# Default flags for linkage
ULDFLAGS = 

# Release flags additional for C 
RCFLAGS  = -O2
# Release flags additional for linkage 
RLDFLAGS = 

# Debug flags additional for C 
DCFLAGS  = -g3
# Debug flags additional for linkage 
DLDFLAGS = 

#
# End define flags
#################################

# List C source files
CSRC += main.c
CSRC += $(ARMAPI)/arm.c
CSRC += $(ARMAPI)/armport/armport_unix.c

# List of directories to include
UINCDIR += $(ARMAPI)/

# List of user define
UDEFS = TTY=\"$(TTY)\"

# List of release define in more
RDEFS = 

# List of debug define in more
DDEFS =

# List of libraries directory
ULIBDIR =

# List of libraries
ULIBS = 

#
# End of user defines
########################################################################

########################################################################
# Start build define
#

# Binary objects directory
OBJS = .obj/
# Binary C objects directory
DCOBJS = $(OBJS)/bin/bin/bin

# C list of binary objects
COBJS=$(patsubst %.c,$(DCOBJS)/%.o, $(CSRC))

# List of include directory
INCDIR = $(patsubst %,-I%, $(UINCDIR))
# List of include library
LIBDIR = $(patsubst %,-L%, $(ULIBDIR))

# List of library
LIBS = $(patsubst %,-l%, $(ULIBS))

# List of define
_UDEFS = $(patsubst %,-D%, $(UDEFS))
_RDEFS = $(patsubst %,-D%, $(RDEFS))
_DDEFS = $(patsubst %,-D%, $(DDEFS))

#
# End build define
########################################################################

########################################################################
# Start rules section
#

all:release

# Build define for release
#.PHONY: release
release:ASFLAGS = $(RASFLAGS) $(UASFLAGS)
release:CFLAGS  = $(RCFLAGS) $(UCFLAGS) $(_UDEFS) $(_RDEFS) $(INCDIR)
release:LDFLAGS = $(RLDFLAGS) $(ULDFLAGS)
release:$(OUTPUT_FILE)

# Build define for debug
#.PHONY: debug
debug:ASFLAGS = $(DASFLAGS) $(UASFLAGS)
debug:CFLAGS  = $(DCFLAGS) $(UCFLAGS) $(_UDEFS) $(_DDEFS) $(INCDIR)
debug:LDFLAGS = $(DLDFLAGS) $(ULDFLAGS)
debug:$(OUTPUT_FILE)

# Build sources to generate output file
$(OUTPUT_FILE): $(ASOBJS) $(COBJS)
	$(CC) -o $@ $(ASOBJS) $(COBJS) $(LDFLAGS) $(LIBS)

# Build C sources
.PRECIOUS: $(DCOBJS)/%.o
$(DCOBJS)/%.o: %.c
	@mkdir -p $(patsubst /%,%, $(@D))
	$(CC) $(CFLAGS) $< -c -o $@
	
# Install on rpi
installscp:
	scp $(OUTPUT_FILE) $(USER)@$(IP):$(DIRECTORY)
install:
	cp $(OUTPUT_FILE) $(DIRECTORY)
	
#uninstall
uninstall:
	rm $(DIRECTORY)/$(OUTPUT_FILE)
	
# Clean projet
clean:
	rm -fr $(OBJS)
	rm -f $(OUTPUT_FILE)

#
# End rules section
########################################################################
