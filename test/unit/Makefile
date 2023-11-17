CC = gcc
CFLAGS = -I../../src
LIBS = -lcunit
TARGET = runtests

SRCDIR = ../../src

SOURCES = main.c stackSuite.c $(SRCDIR)/stack.c
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
