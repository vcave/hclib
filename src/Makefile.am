SUBDIRS =

# Includes folders
INCLUDES_DIR = -I$(top_srcdir)/inc -I$(top_srcdir)/src/inc

# cflags: important to define that otherwise we inherit default values too
# NOTE: Disabled -Werror because OCR uses #warning to warn about extension API
CFLAGS = $(PHASER_CFLAGS) -Wall -g -O3
LDFLAGS = $(PHASER_LDFLAGS)

# build the hclib library
lib_LTLIBRARIES = libhclib.la

# These are populated in sub-folder's Makefile.inc
noinst_LTLIBRARIES =
libhclib_la_LIBADD =

include crt/Makefile.inc
include ocr/Makefile.inc

# build hclib
libhclib_la_SOURCES = runtime-hclib.c runtime-callback.c hclib.c ddf.c forasync.c accumulator.c

libhclib_la_CFLAGS= $(CFLAGS) $(INCLUDES_DIR)

MAINTAINERCLEANFILES = Makefile.in
