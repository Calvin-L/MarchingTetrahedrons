PROGRAM=MarchingTetrahedrons

all: $(PROGRAM)

SOURCES = $(shell find . -name "*.cpp")

OBJS = $(addprefix ./,$(addsuffix .o,$(basename $(notdir $(SOURCES)))))

PKG_CONFIG=gl glu
PKG_CONFIG_CFLAGS=`pkg-config --cflags $(PKG_CONFIG)`
PKG_CONFIG_LIBS=`pkg-config --libs $(PKG_CONFIG)`

CFLAGS= -O2 -g -Wall
DEFS=

LDFLAGS= -Wl,-z,defs -Wl,--as-needed -Wl,--no-undefined
LIBS=-lglut

$(PROGRAM): $(OBJS)
	g++ $(LDFLAGS) $+ -o $@ $(LIBS) $(PKG_CONFIG_LIBS)

%.o: %.cpp
	g++ -o $@ -c $+ $(CFLAGS) $(DEFS) $(PKG_CONFIG_CFLAGS)

%.o: %.c
	gcc -o $@ -c $+ $(CFLAGS) $(DEFS) $(PKG_CONFIG_CFLAGS)

clean:
	rm -f $(OBJS)
	rm -f $(PROGRAM)
	rm -f *.o *.a *~
