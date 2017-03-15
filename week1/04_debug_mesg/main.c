#include "hexView.h"
#include "log_util.h"

int main(int argc, char* argv[]) {

	char *log_env = getenv("LOG_LEVEL");
	int ret;

	if (argc == 1) {
		fputs("사용법: hexView 파일명\n", stderr);

		if(strcmp(log_env, "ERROR") == 0)
			LOG_ERROR("%s error.", "file parameter input");
			
	
		exit(1);
	}

	if(strcmp(log_env, "TRACE") == 0) {
	       LOG_CALL(ret = hexView(argv[1]));
	}	       
	else {
		hexView(argv[1]);
	}

	return 0;
}

