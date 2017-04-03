ARCH = 

ifeq ($(ARCH), ARM)
CC = arm-linux-gnueabi-gcc
else ifeq ($(ARCH), WIN32)
CC = x86_64-w64-mingw32-c++-win32 
else
CC = gcc
endif

CFAGS = -W -Wall
TARGET = dairy
RM = rm -f
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all : $(TARGET)

help :
	@echo "Makefile help command"


$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	$(RM) *.o && $(RM) $(TARGET)*
