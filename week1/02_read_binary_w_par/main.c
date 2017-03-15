#include <stdio.h>
#include <stdlib.h>


int hexView(const char* filename);


int main(int argc, char* argv[]) {
  if (argc == 1) {
    fputs("사용법: hexView 파일명\n", stderr);
    exit(1);
  }

  hexView(argv[1]);

  return 0;
}


int hexView(const char* filename) {  // 헥사 뷰어 함수의 본체
  FILE *in;
  size_t offset = 0; // 번지
  char buf16[16];    // 헥사 값이 16바이트, 즉, 한줄씩 저장될 버퍼
  size_t buf16Len;   // 한줄에 들어있는 헥사 값의 개수, 즉, 길이

  // GCC에서 파일 열기
  if ((in = fopen( filename, "r")) == NULL) {
    fputs("파일 오픈 에러\n", stderr);
    exit(1);
  }

  // 파일을 16바이트씩, 끝까지 읽으며 루프 돌리기
  while ( (buf16Len = fread(buf16, sizeof(char), sizeof(buf16), in)) != 0 ) {
    printf("%08X:  ", (unsigned int)offset); // Offset (번지) 출력

    // 헥사 부분의 헥사 값 16개 출력 (8개씩 2부분으로)
    for (int i = 0; i < (int) buf16Len; i++) {
      if (i == 8) printf(" "); // 8개씩 분리
      printf("%02X ", (unsigned char) buf16[i]); // 헥사 값 출력
    }

    // 한 줄이 16 바이트가 되지 않을 때, 헥사 부분과 문자 부분 사이에 공백들 삽입
    for (int i = 0; i <= (16 - (int) buf16Len) * 3; i++)
      printf(" ");
    if (buf16Len < 9) printf(" "); // 한줄이 9바이트보다 적을 때는 한칸 더 삽입

    // 문자 부분 출력
    for (int i = 0; i < (int) buf16Len; i++) {
      if (buf16[i] >= 0x20 && buf16[i] <= 0x7E) // 특수 문자 아니면 출력
        printf("%c", buf16[i]);
      else printf("."); // 특수문자, 그래픽문자 등은 마침표로 출력
    }

    offset += 16; // 번지 값을 16 증가
    printf("\n"); // 줄바꿈
  }


  if (offset == 0) printf("%08X:  ",(unsigned int) offset); // 0바이트 파일일 경우 처리
  fclose(in); // 파일 닫기

  return 0;
}
