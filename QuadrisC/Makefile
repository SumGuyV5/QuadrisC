# 'make'				builds Release and Debug executable file $(EXECUTABLE)
# 'make Debug'			builds a Debug executable file
# 'make Release'		builds a Release executable file
# 'make rebuild'		rebuilds executable file
# 'make debug-install'	installs the Debug executable file in $(INSTALLDIR)
# 'make install'		installs the Release executable file in $(INSTALLDIR)
# 'make uninstall'		removies the files from $(INSTALLDIR)
# 'make dpkg'			makes a ubuntu deb installer.
# 'make depend'			runs makedepend on the $(SRCS) files.
# 'make clean'			removes the .o files and executable file.
# 'make cleanall'		removes the $(ODIR) and the $(BDIR).

# define the C compiler to use
CC = gcc

CFG = Release
# define any compile-time flags
CFLAGS = -D_GNU_SOURCE=1 -D_REENTRANT -Wall -g

# define any directories containing header files other than /usr/include
#
INCLUDES = -IHeaderFiles -I/usr/include/SDL

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS =

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lSDL -lSDLmain -lSDL_mixer -lSDL_ttf

# define the C source files
SRCS = $(wildcard SourceFiles/*.c)#SourceFiles/Block.c SourceFiles/Game.c SourceFiles/Globals.c SourceFiles/Score.c SourceFiles/Sound.c SourceFiles/TextType.c SourceFiles/Timer.c SourceFiles/Video.c #SourceFiles/main.c

# define the executable file 
EXECUTABLE = QuadrisC

ODIR = obj
BDIR = bin

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
_OBJS = $(SRCS:.c=.o)
OBJS = $(patsubst %,$(ODIR)/$(CFG)/%,$(_OBJS))

FOLDERS = $(ODIR)/$(CFG)/SourceFiles\
		  $(BDIR)/$(CFG)

INSTALLDIR = /usr/games/quadrisc/

DEBVERSION = 1.1.0
DEBDIR = ../quadrisc-$(DEBVERSION)
DEBMENU = /usr/share/applications

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: clean cleanall

all: Release Debug

Debug: CFG = Debug
Debug: CFLAGS = -D_GNU_SOURCE=1 -D_REENTRANT -g -Wall -D_DEBUG
Debug: OBJS = $(patsubst %,$(ODIR)/$(CFG)/%,$(_OBJS))
Debug: FOLDERS = $(ODIR)/$(CFG)/SourceFiles\
		$(BDIR)/$(CFG)
Debug: build

Release: CFG = Release
Release: CFLAGS = -D_GNU_SOURCE=1 -D_REENTRANT -Wall -g
Release: OBJS = $(patsubst %,$(ODIR)/$(CFG)/%,$(_OBJS))
Release: FOLDERS = $(ODIR)/$(CFG)/SourceFiles\
		  $(BDIR)/$(CFG)
Release: build

build: Folders $(EXECUTABLE)
	@echo $(OBJS)	
	@echo  $(CFG) Compile

rebuild: clean build

debug-install: CFG = Debug
debug-install: install-build

install: CFG = Release
install: install-build

install-build:
	mkdir -p $(INSTALLDIR)
	mv $(BDIR)/$(CFG)/$(EXECUTABLE) $(INSTALLDIR)/$(EXECUTABLE)
	cp -r Resource/ $(INSTALLDIR)/
	rm -r -f $(INSTALLDIR)/Resource/.svn
	@echo $(EXECUTABLE) Installed.

uninstall:
	rm -r -f $(INSTALLDIR)

dpkg: CFG = Release
dpkg:
	mkdir -p $(DEBDIR)/$(INSTALLDIR)
	mkdir -p $(DEBDIR)/$(DEBMENU)
	cp -r DEBIAN $(DEBDIR)/
	cp -r quadrisc.desktop $(DEBDIR)/$(DEBMENU)
	cp -r $(BDIR)/$(CFG)/$(EXECUTABLE) $(DEBDIR)/$(INSTALLDIR)/
	cp -r Resource/ $(DEBDIR)/$(INSTALLDIR)/
	rm -rf $(DEBDIR)/$(INSTALLDIR)/Resource/.svn
	rm -rf $(DEBDIR)/DEBIAN/.svn
	dpkg-deb --build $(DEBDIR)	

Folders:
	$(foreach var, $(FOLDERS), mkdir -p $(var);)

$(EXECUTABLE): Source
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BDIR)/$(CFG)/$@ $(OBJS) $(LFLAGS) $(LIBS)
	@echo $(BDIR)/$(CFG)/$@ file made

Source:
	$(foreach var, $(OBJS), $(CC) $(CFLAGS) $(INCLUDES) -c $(patsubst $(ODIR)/$(CFG)/%.o, %.c, $(var)) -o $(var);)
	@echo file made

depend: 
	makedepend $(INCLUDES) $(SRCS)

clean:
	rm -f */*/*/*.o
	rm -f */*/$(EXECUTABLE)
	@echo Clean done

cleanall: clean
	rm -rf $(ODIR)
	rm -rf $(BDIR)
	rm -rf $(DEBDIR)
	rm -rf $(DEBDIR).deb
	@echo Clean all done
