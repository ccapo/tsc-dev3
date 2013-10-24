SRCDIR = src
INCDIR = include
LIBDIR = lib
CPP = g++
UPX = upx -qq

PROG_BUILD_NUM = data/.build_number
BUILD_DATE = $(shell date +'%Y%m%d')
BUILD_NUM = $(shell cat $(PROG_BUILD_NUM))

#CFLAGS = -O2 -s -w -I$(INCDIR)/tcod -I$(INCDIR)/tsc -I$(INCDIR)/fmodex
#CFLAGS = -O2 -s -w -I$(INCDIR)/tcod -I$(INCDIR)/tsc -DDEV
CFLAGS = -O0 -g -w -I$(INCDIR)/tcod -I$(INCDIR)/tsc -DDEV

CFLAGS += -DBUILD_DATE=$(BUILD_DATE) -DBUILD_VERSION=$(BUILD_NUM)

# Determine if operating system is 32-bit or 64-bit
ifeq ($(shell uname -m),x86_64)

	# These are the definitions specific to 64-bit systems
	#LFLAGS = -L$(LIBDIR)/x86_64 -ltcod -ltcodxx -lfmodex -lm -Wl,-rpath=$(LIBDIR)/x86_64
	LFLAGS = -L$(LIBDIR)/x86_64 -ltcod -ltcodxx -lm -Wl,-rpath=$(LIBDIR)/x86_64

else

	# These are the definitions specific to 32-bit systems
	#LFLAGS = -L$(LIBDIR)/i386 -ltcod -ltcodxx -lfmodex -lm -Wl,-rpath=$(LIBDIR)/i386
	LFLAGS = -L$(LIBDIR)/i386 -ltcod -ltcodxx -lm -Wl,-rpath=$(LIBDIR)/i386

endif

.SUFFIXES: .o .hpp .cpp

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

SOURCES = $(wildcard $(SRCDIR)/*.cpp)

HEADERS = $(wildcard $(INCDIR)/tsc/*.hpp)

OBJECTS = $(SOURCES:.cpp=.o)

all: build_number_file_present clean tsc clean_objects increment_build_number
#all: tsc

tsc: $(HEADERS) $(OBJECTS)
	$(CPP) $(CFLAGS) $(OBJECTS) -o $@ $(LFLAGS)
	@rm -f $(OBJECTS)
#	$(UPX) $@

test: src/old/Test.o
	$(CPP) $(CFLAGS) src/old/Test.o -o $@ $(LFLAGS)
	@rm -f src/old/Test.o

clean_objects:
	@rm -f $(OBJECTS)

clean:
	@rm -f $(OBJECTS)
	@rm -f tsc

build_number_file_present:
	@if ! test -f $(PROG_BUILD_NUM); then echo 0 > $(PROG_BUILD_NUM); fi

increment_build_number:
	@bash -c "echo $$(( $(BUILD_NUM) + 1 ))" > $(PROG_BUILD_NUM)
