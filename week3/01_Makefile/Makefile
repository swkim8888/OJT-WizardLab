CC = gcc
CFAGS = -W -Wall
DATE = date +%Y%m%d
TARGET = dairy
TARGET_GDB = $(TARGET)_$(shell $(DATE))
MD = mkdir -p
RM = rm -f
BUILDDIR = output
TESTDIR = debug

#OBJECTS = memo.o main.o calendar.o
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c)) 

all : $(TARGET)
	$(MD) $(BUILDDIR) && cp $(TARGET) $(BUILDDIR)
	$(RM) $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

test: $(TARGET_GDB)
	$(MD) $(TESTDIR) && cp $(TARGET_GDB) $(TESTDIR)
	$(RM) $(TARGET_GDB)       

$(TARGET_GDB) : $(OBJECTS)
	$(CC) $(CFLAGS) -v -g -o $@ $^	

clean :
	$(RM)  *.o && $(RM) $(BUILDDIR)/$(TARGET)

clean_test :
	$(RM) $(TESTDIR)/$(TARGET)*

