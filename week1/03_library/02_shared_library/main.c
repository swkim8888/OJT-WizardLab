#include "hexView.h"

int main(int argc, char* argv[]) {
  if (argc == 1) {
    fputs("사용법: hexView 파일명\n", stderr);
    exit(1);
  }

  hexView(argv[1]);

  return 0;
}

