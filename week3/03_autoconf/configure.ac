dnl 시작 매크로
AC_INIT(like, 0.0.1, swkim@wizardlab.co.kr)

dnl 체크할 프로그램
AC_PROG_CC                      # C 컴파일러를 결정
AC_PROG_CPP                     # C 전처리기를 결정

dnl 체크할 프로그램
AC_CHECK_LIB([c], [memcpy])     # libc를 체크
AC_CHECK_LIB([m], [sin])        # libm를 체크ㅑ

dnl 체크할 헤더 파일            #괄호에 있는 헤더 파일들을 체크
AC_CHECK_HEADERS([fcntl.h stdlib.h string.h sys/ioctl.h termios.h unistd.h])
AC_HEADER_DIRENT                # dirent.h 체크

dnl 체크할 데이터 타입 및 구조체
AC_TYPE_SIZE_T                  # size_t 타입 체크
AC_STRUCT_TM                    # sturnct tm을 체크

dnl 체크할 라이브러리 함수
AC_CHECK_FUNCS([strchr strdup ststr])   # 괄호 안의 함수들을 체크할
AC_FUNC_MALLOC                           # malloc 함수 체크

dnl 최조적으로 생성할 파일명
AC_CONFIG_FILES([Makefile])              # 최종적으로 Makefile 생성
AC_OUTPUT
