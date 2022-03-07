#
# COMPILER
#
CC := clang
#
# REPRESENTATION [600] SUSv3 / UNIX 03 / POSIX.1-2001
#
PORTABILITY := -D_XOPEN_SOURCE=600
#
# CONSISTENCY
#
WARNINGS := #-Wno-long-long -Wall -pedantic -Werror
#
# INSPECTION
#
DEBUG := -g -ggdb
#
# STRUCTURE
#
CCFLAGS := $(PORTABILITY) -Iinc -Ic-endian-bint/inc $(WARNINGS) $(DEBUG)

LDFLAGS := -lm #-lpthread
#
# DEPENDENCIES
#
HEADERS := inc/*.h

SOURCES := src/*.c
#
# SUBMODULE BINT
#
BINT_HEADERS := c-endian-bint/inc/*.h

BINT_SOURCES := c-endian-bint/src/*.c

BINT_CCFLAGS := $(PORTABILITY) -Ic-endian-bint/inc $(WARNINGS) $(DEBUG)

bix: c-endian-bint/prep/bint $(HEADERS) $(BINT_HEADERS) $(SOURCES) $(BINT_SOURCES) main/bix.c
	$(CC) $(shell c-endian-bint/prep/bint) $(CCFLAGS) -o $@ $(SOURCES) $(BINT_SOURCES) main/bix.c $(LDFLAGS)

c-endian-bint/prep/bint: c-endian-bint/prep/bint.c
	$(CC) -o c-endian-bint/prep/bint c-endian-bint/prep/bint.c

clean:
	rm -f c-endian-bint/bint c-endian-bint/prep/bint bix core
