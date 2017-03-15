#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#define CRC_TABLE_SIZE  256
#define DATA_SIZE	10
#define CRC_SIZE	2
#define INIT_SIZE	1
#define END_SIZE	1
#define TOTAL_SIZE	(DATA_SIZE + CRC_SIZE + INIT_SIZE + END_SIZE)

/*
 *declare function
 */
int HDLC_encoding(char** argv);
void make_crc_table(void);
void print_crc_table();
unsigned short crc16_ccitt(const void *buf, int len);



static unsigned short crctable[256];




int main(int argc, char** argv)
{
	make_crc_table();
	//print_crc_table();
	HDLC_encoding(argv);
	return 0;
}





int HDLC_encoding(char** argv) 
{
	unsigned char buffLen[DATA_SIZE];	//길이
	unsigned char crc_buf[CRC_SIZE];	//
	unsigned char Total_buf[TOTAL_SIZE];	//
	unsigned int crc;
	FILE *fp;
	int buffer;
	

	if((fp = fopen(argv[1], "r"))==NULL)
	{
		fputs("file open error ! \n", stdout);
		exit(1);
	}

	//test!!!! 10 바이트씩 끝까지 읽기
	while ((buffer = fread(buffLen, sizeof(char), sizeof(buffLen), fp)) != 0)
	{
		for (int i=0; i < (int)buffer; i++)
		{
			//printf("[%02X] ", (unsigned char)buffLen[i]);
			//crc16_ccitt(buffLen, 10);
			Total_buf[i+1] =buffLen[i];

		}

		//return crc16 code and split 2 arays
		crc = crc16_ccitt(buffLen, DATA_SIZE);
		crc_buf[0] = (crc & 0xFF00) >> 8;
		crc_buf[1] = (crc & 0x00FF);

		Total_buf[0] = 0x7E;
		Total_buf[TOTAL_SIZE -1] = 0x7E;
		Total_buf[DATA_SIZE + CRC_SIZE -1] = crc_buf[0];
		Total_buf[DATA_SIZE + CRC_SIZE] = crc_buf[1];

		
		for(int i = 0; i < TOTAL_SIZE; i++)
			printf("[%02X] ", (unsigned char)Total_buf[i]);
		



		printf("\n");
	}



	fclose(fp);
	return 0;
			
}


/*
 *make CRC16 CCITT table.
 *table for a byte-wise 16-bit CRC calculation on the polynomial:
 *  x^16 + x^12 + x^5 + x^0
 */
void make_crc_table( void ) {
    int i, j;
    unsigned long poly, c;

    /* terms of polynomial defining this crc (except x^16): */
    static const char p[] = {0,5,12};
   // static const char p[] = {0,2,15};


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
 *Print crc table
 */
void print_crc_table(void)
{
    for (int i=0; i< CRC_TABLE_SIZE; i++)
        {
                printf("0x%04X", crctable[i]);
                if(i != CRC_TABLE_SIZE)
                {
                        printf(", ");
                        if( ( i%8) == 7)
                                printf("\n");
                }
        }
}


/*
 *crc calculator
 */  
unsigned short crc16_ccitt(const void *buf, int len)
{
        int counter;
        unsigned short crc = 0;
	
	for( counter = 0; counter < len; counter++)
                crc = (crc<<8) ^ crctable[((crc>>8) ^ *(char *)buf++)&0x00FF];
	
	return crc;
}



