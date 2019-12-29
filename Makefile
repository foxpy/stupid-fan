CC = clang
CFLAGS = -Wall -Wextra -pedantic -std=c99
DFLAGS = -DDEBUG -O0 -g
RFLAGS = -D_FORTIFY_SOURCE=2 -O2

BUILDDIR = bin
SRCDIR = src
EXECUTABLE = stupid-fan
TARGET = $(BUILDDIR)/$(EXECUTABLE)

PREFIX := /usr/local

SOURCES = $(shell find $(SRCDIR) -name *.c)
HEADERS = $(shell find $(SRCDIR) -name *.h)
OBJECTS = $(SOURCES:%=$(BUILDDIR)/%.o)

debug: CFLAGS += $(DFLAGS)
debug: $(TARGET)

release: CFLAGS += $(RFLAGS)
release: $(TARGET)
	strip $^

$(BUILDDIR)/%.c.o: %.c $(HEADERS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

install:
	install -Dm755 $(TARGET) '$(PREFIX)/bin/$(EXECUTABLE)'

uninstall:
	rm '$(PREFIX)/bin/$(EXECUTABLE)'

clean:
	rm -fv $(TARGET) $(OBJECTS)
