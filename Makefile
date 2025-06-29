CC=gcc
CFLAGS += -Wall
CFLAGS += -Werror 
CFLAGS += -Wno-implicit-function-declaration 
CFLAGS += -Iinclude 
CFLAGS += -g 
CFLAGS += -fopenmp 
CFLAGS += -municode 
CFLAGS += -static
# CFLAGS += -O2
SDL_LIBS=$(shell sdl2-config --static-libs) -lSDL2_image -lSDL2_ttf -lSDL2_mixer
LDFLAGS=-Iinclude $(SDL_LIBS)
TARGET=game

EXTENSION=.exe

BINDIR=./bin
SRCDIR=./src
OBJDIR=./obj
INCDIR=./include
ASSETDIR=./assets

SRC=$(wildcard $(SRCDIR)/*.c $(SRCDIR)/**/*.c)
OBJ=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

init:
	mkdir -p $(SRCDIR)
	mkdir -p $(BINDIR)
	mkdir -p $(OBJDIR)
	mkdir -p $(INCDIR)
	mkdir -p $(ASSETDIR)

all: $(TARGET)

rebuild: clean $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(BINDIR)/$(TARGET)$(EXTENSION) $(CFLAGS) $(LDFLAGS)
	cp -R $(ASSETDIR)/ $(BINDIR)/

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@, hacks)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -r $(BINDIR)/*.* $(OBJDIR)/*.o $(OBJDIR)/**/*.o || true
	rm -rf $(OBJDIR)/*.* $(OBJDIR)/**/*.* || true
	rm -rf $(BINDIR)/assets/*.* $(BINDIR)/assets/**/*.* || true

run:
	$(BINDIR)/$(TARGET)$(EXTENSION) $(ARGS)
runme:
	$(BINDIR)/$(TARGET)$(EXTENSION) --mapedit
debug:
	gdb $(BINDIR)/$(TARGET)$(EXTENSION) $(ARGS)
