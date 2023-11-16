CFILES   = $(wildcard *.c)
OBJDIR   = obj
OBJFILES = $(addprefix $(OBJDIR)/, $(CFILES:.c=.o))
TARGET   = yvc

CC = gcc

$(TARGET): $(OBJFILES)
	$(CC) -o $@ $^

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) -c -o $@ $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(TARGET)
