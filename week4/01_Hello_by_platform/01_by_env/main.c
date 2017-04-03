#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
        FILE *fd;
        int ret;        //system 함수 리턴


        ret = system("/bin/uname -o > Os_check");

        fd = fopen("./Os_check", "r" );
        if(fd != NULL)
        {
                char strTemp[50];
                char *pStr;

                while(!feof(fd))
                {
                        pStr = fgets(strTemp, sizeof(strTemp), fd);
                        //printf("%s", strTemp);
                        //printf("%s", pStr);

                        if(!strncmp(strTemp, "GNU/Linux",9)) {
                                printf("Hello? this is Linux");
                                break;
                        }
    
                        else if(!strncmp(strTemp, "Cygwin", 6)) {
                                printf("Hello? this is Cygwin!!!\n");
			        break;
                        }

                        else {
                                printf("Hello? this is Window!!!");
                                break;
                        }

                }

                fclose(fd);
        }
        else
        {
                //error 처리
        }

                system("rm Os_check");
    
                return 0;
    
}

