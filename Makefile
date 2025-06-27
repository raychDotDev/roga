CC=clang
CFLAGS=-Wall -Werror -Wno-implicit-function-declaration --target=x86_64-w64-mingw32 -Iinclude -static -g -municode #-mwindows

LDFLAGS=-Iinclude -Llib -lSDL2.dll -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lwinmm -lgdi32
TARGET=game

EXTENSION=.exe

BINDIR=./bin
SRCDIR=./src
OBJDIR=./obj
INCDIR=./include
LIBDIR=./lib
ASSETDIR=./assets

SRC=$(wildcard $(SRCDIR)/*.c $(SRCDIR)/**/*.c)
OBJ=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

init:
	mkdir -p $(SRCDIR)
	mkdir -p $(BINDIR)
	mkdir -p $(OBJDIR)
	mkdir -p $(INCDIR)
	mkdir -p $(LIBDIR)
	mkdir -p $(ASSETDIR)

all: $(TARGET)

rebuild: clean $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(BINDIR)/$(TARGET)$(EXTENSION) $(CFLAGS) $(LDFLAGS)
	cp $(LIBDIR)/*.dll $(BINDIR)/ || true
	cp -R $(ASSETDIR)/ $(BINDIR)/

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@, hacks)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(BINDIR)/*.* $(OBJDIR)/*.o $(OBJDIR)/**/*.o
	rm -rf $(OBJDIR)/*.* $(OBJDIR)/**/*.*
	rm -rf $(BINDIR)/assets/*.* $(BINDIR)/assets/**/*.* || true

run:
	$(BINDIR)/$(TARGET)$(EXTENSION) $(ARGS)

debug:
	lldb $(BINDIR)/$(TARGET)$(EXTENSION) $(ARGS)
