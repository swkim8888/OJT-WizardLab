#include <stdio.h>
#define CRC16 0xA001 /* X16 + X15 + X2 + 1 */
 
unsigned short calcCRC ( unsigned short data ) /* CRC16_IBM */
{
    int i;    
    unsigned short crc = 0;
    for ( i = 8; i; i-- )
    {   
        if ( ( data ^ crc ) & 0x0001 )
            crc = ( crc >> 1 ) ^ CRC16;
        else
            crc >>= 1;
        data >>= 1;
    }   
    return crc;
}
 
int main ( int argc, char *argv[] )
{
    int i;
    printf( "const unsigned int CRCtbl [ 256 ] = {\n" );
    for ( i = 0; i < 256; i++ )    
    {   
        printf( "0x%04X", calcCRC( i ) );
        if ( i != 255 )
        {
            printf ( ", " );
            if ( ( i % 8 ) == 7 ) 
                printf( "\n" );
        }
    }   
    printf( " };\n" );
}


