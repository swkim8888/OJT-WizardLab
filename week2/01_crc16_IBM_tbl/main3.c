#include <stdio.h>

#define CRC16_INIT_VALUE     0xffff
#define CRC16_XOR_VALUE        0x0000

static unsigned short crctable[256];

/*
   Generate a table for a byte-wise 16-bit CRC calculation on the polynomial:
   x^16 + x^12 + x^5 + x^0
*/

void make_crc_table( void ) {
    int i, j;
    unsigned long poly, c;
    /* terms of polynomial defining this crc (except x^16): */
    static const char p[] = {0,5,12};

    /* make exclusive-or pattern from polynomial (0x1021) */
    poly = 0L;
    for ( i = 0; i < sizeof( p ) / sizeof( char); i++ ) {
        poly |= 1L << p[i];
    }

    for ( i = 0; i < 256; i++ ) {
        c = i << 8;
        for ( j = 0; j < 8; j++ ) {
            c = ( c & 0x8000 ) ? poly ^ ( c << 1 ) : ( c << 1 );
        }
        crctable[i] = (unsigned short) c;
    }
}

/*
unsigned short crc16_ccitt(const void *buf, int len)
{
	register int counter;
	register unsigned short crc = 0;
	for( counter = 0; counter < len; counter++)
		crc = (crc<<8) ^ crc16tab[((crc>>8) ^ *(char *)buf++)&0x00FF];
	return crc;
}
*/

void main()
{
	int i;
	make_crc_table();

	for (i=0; i< 256; i++)
	{
		printf("0x%04X", crctable[i]);
		if(i != 255)
		{
			printf(", ");
			if( ( i%8) == 7)
				printf("\n");
		}
	}

}
