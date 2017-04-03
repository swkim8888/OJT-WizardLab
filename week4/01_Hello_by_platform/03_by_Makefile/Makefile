ARCH = 

ifeq ($(ARCH), ARM)
CC = arm-linux-gnueabi-gcc
else ifeq ($(ARCH), WIN32)
CC = x86_64-w64-mingw32-c++-win32 
else
ARCH = Linux
CC = gcc
endif

CFAGS = -W -Wall
TARGET = dairy
MD = mkdir -p
RM = rm -f
BUILDDIR = output
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all : clean $(TARGET)
	$(MD) $(BUILDDIR)_$(ARCH) && cp $(TARGET)_$(ARCH) $(BUILDDIR)_$(ARCH)
	$(RM) $(TARGET)_$(ARCH)

help :
	@echo "--- Makefile help command ---"
	@echo "	build for ARM processor : make ARCH=ARM"
	@echo "	build for Window system : make ARCH=WIN32"
	@echo "	build for Linux system : make ARCH=Linux or make


$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@_$(ARCH) $^

clean :
	$(RM) *.o && $(RM) -R $(BUILDDIR)*
