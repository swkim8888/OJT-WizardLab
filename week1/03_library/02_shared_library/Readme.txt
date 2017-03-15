#### Make Shared library ####

gcc -fPIC -c hexView.c
gcc -shared -Wl,-soname,libhexview.so.1 -o libhexview.so.1.0.1 hexView.o
cp libhexview.so.1.0.1 /usr/local/lib/
sudo ln -s /usr/local/lib/libhexview.so.1.0.1 /usr/local/lib/libhexview.so
gcc -o main main.c -L/usr/local/lib -lhexview
cat /usr/local/lib > /etc/ld.so.conf
ldconfig
