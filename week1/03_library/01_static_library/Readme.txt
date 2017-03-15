#### Make Static library ####

gcc -c hexView.c
ar rc libmyhexview.a hexView.o
gcc -o main main.c -L./ -lmyhexview



