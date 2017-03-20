CC = gcc
CFAGS = -W -Wall
TARGET = diary_exe
OBJECTS = memo.o main.o calendar.o

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -f  *.o diary_exe
