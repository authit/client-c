CC=gcc
CFLAGS=-c -Wall -D_FILE_OFFSET_BITS=64
LDFLAGS=$(shell gpgme-config --libs)
LDFLAGS+=$(shell gpg-error-config --libs)
LDFLAGS+=$(shell libassuan-config --libs)
LDFLAGS+=--static
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=test-client

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(EXECUTABLE)
