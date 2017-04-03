#include<stdio.h>

#ifdef __linux__

int main()
{
        printf("I'm Linux");

        return 0;
}

#elif (_WIN32) || (__CYGWIN__)

int main()
{
        printf("I'm Window");

        return 0;
}


#endif

