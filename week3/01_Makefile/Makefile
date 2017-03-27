# 컴파일러
CC = gcc

# 컴파일러 플래그
CFAGS = -W -Wall

# 날짜 저장
DATE = date +%Y%m%d

# 출력 파일 이름
TARGET = dairy

# 출력 파일 이름 + 날짜
TARGET_GDB = $(TARGET)_$(shell $(DATE))

# 폴더 생성 명렁어
MD = mkdir -p

# 파일 삭제 명령어
RM = rm -f

#빌드 결과 폴더명
BUILDDIR = output

#디버그용 빌드 결과 저장 폴더명
TESTDIR = debug

#OBJECTS = memo.o main.o calendar.o
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c)) 

#make all 
all : $(TARGET)
	@echo "build all"
	$(MD) $(BUILDDIR) && cp $(TARGET) $(BUILDDIR)
	$(RM) $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# make test
test: $(TARGET_GDB)
	@echo "Buld all for debug and attach build date to the target name"
	$(MD) $(TESTDIR) && cp $(TARGET_GDB) $(TESTDIR)
	$(RM) $(TARGET_GDB)       

$(TARGET_GDB) : $(OBJECTS)
	$(CC) $(CFLAGS) -v -g -o $@ $^	

# make clean
clean :
	@echo "clean object file and target file"
	$(RM)  *.o && $(RM) $(BUILDDIR)/$(TARGET)

clean_test :
	@echo "clean debug target file all"
	$(RM) $(TESTDIR)/$(TARGET)

