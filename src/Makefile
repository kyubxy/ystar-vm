CFILES   = $(wildcard *.c)
OBJFILES = $(CFILES:.c=.o)
TARGET   = yvc

ODIR = obj

CC = gcc

$(TARGET): $(OBJFILES)
	$(CC) -o $@ $(ODIR)/$^

%.o: %.c
	$(CC) -c -o $(ODIR)/$@ $^

.PHONY: clean
clean:
	rm -f $(OBJFILES) $(TARGET)