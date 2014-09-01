CC=gcc

CFLAGS=-g `sdl2-config --cflags` -lm
LDFLAGS=`sdl2-config --libs` -lpng -lm -lSDL2_gfx

SOURCES=savepng.c showSPDI.c
EXECUTABLE=showSPDI

OBJECTS=$(SOURCES:.c=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC)  $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *.a $(EXECUTABLE)
