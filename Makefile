PROGRAM=MarchingTetrahedrons

all: $(PROGRAM)

SOURCES = $(shell find . -name "*.cpp")

OBJS = $(SOURCES:.cpp=.o)

PKG_CONFIG=gl glu
PKG_CONFIG_CFLAGS=$(shell pkg-config --cflags $(PKG_CONFIG))
PKG_CONFIG_LIBS=$(shell pkg-config --libs $(PKG_CONFIG))

CXX=g++
CC=gcc
RM=rm -f
CFLAGS= -O2 -g -Wall
DEFS=

LDFLAGS= -Wl,-z,defs -Wl,--as-needed -Wl,--no-undefined
LIBS=-lglut

$(PROGRAM): $(OBJS)
	$(CXX) $(LDFLAGS) $+ -o $@ $(LIBS) $(PKG_CONFIG_LIBS)

%.o: %.cpp
	$(CXX) -o $@ -c $+ $(CFLAGS) $(DEFS) $(PKG_CONFIG_CFLAGS)

%.o: %.c
	$(CC) -o $@ -c $+ $(CFLAGS) $(DEFS) $(PKG_CONFIG_CFLAGS)

clean:
	$(RM) $(OBJS)
	$(RM) $(PROGRAM)
	$(RM) *.o *.a *~
