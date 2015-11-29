########################################################################
#
#	Makfile.
#
# - author 	:	Antoine Maleyrie : antoine.maleyrie@atim.com
# - version	:	0.1
# - date 	:	24.10.2015
#
########################################################################

########################################################################
# Start of user section
#

# Name of output file
OUTPUT_FILE = armfuser

# Toolchain
CC      = gcc
GDB 	= gdb
FLEX	= flex
BISON	= bison

#################################
# Start define flags
#

# Default flags for C 
UCFLAGS  = -W -std=gnu99
# Default flags for linkage
ULDFLAGS = 

# Release flags additional for C 
RCFLAGS  = -O2
# Release flags additional for linkage 
RLDFLAGS = 

# Debug flags additional for C 
DCFLAGS  = -O2 -g
# Debug flags additional for linkage 
DLDFLAGS = 

#
# End define flags
#################################

# List C source files
CSRC += src/grammar.c
CSRC += src/lexicon.c
CSRC += src/main.c
CSRC += src/entity.c

# List of directories to include
UINCDIR +=.

# List of user define
UDEFS =

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
OBJS = .obj
# Binary C objects directory
DCOBJS = $(OBJS)

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

# Build sources to generate elf file
$(OUTPUT_FILE): $(COBJS)
	$(CC) -o $@ $(LDFLAGS) $(LIBS) $(COBJS)

# Build C sources
.PRECIOUS: $(DCOBJS)/%.o
$(DCOBJS)/%.o: %.c
	@mkdir -p $(patsubst /%,%, $(@D))
	$(CC) $(CFLAGS) $< -c -o $@
	
# Generate c parser file
.PRECIOUS: %.c
%.c: %.y
	$(BISON) --graph -d -o$@ $<
#	dot -Tpdf src/grammar.dot -o grammar.pdf
	
# Generate c lexical file
.PRECIOUS: %.c
%.c: %.l
	$(FLEX) -o$@ $<
	
# convert the armapi from c source to cpp source
run:
	@./$(OUTPUT_FILE)
	
# Run gdb for debug.
gdb:debug
	$(GDB) $(OUTPUT_FILE)
	
# Run cgdb for debug with color.
cgdb:debug
	cgdb -d $(GDB) $(OUTPUT_FILE)

	
# Clean projet
clean:
	rm -fr $(OBJS)
	rm -f $(OUTPUT_FILE)
	rm -f src/grammar.h
	rm -f src/grammar.c
	rm -f src/grammar.dot
	rm -f src/lexicon.c

#
# End rules section
########################################################################
