#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hdlc.h"

static unsigned short crctable[256];

/*
 *RC16 CCITT table.
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

    for ( i = 0; i < CRC_TABLE_SIZE; i++ ) {
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
 * crc calculator
 */
unsigned short crc16_ccitt(const void *buf, int len)
{
        int counter;
        unsigned short crc = 0;

        for( counter = 0; counter < len; counter++)
                crc = (crc<<8) ^ crctable[((crc>>8) ^ *(char *)buf++)&0x00FF];

        return crc;
}

/*
 * HDLC encoding function 
 */
char*     HDLC_encoding(char* data_buf, int len)
{
        //unsigned char data_buf[DATA_SIZE] = {0} ;       // 데이터 버퍼
        unsigned char crc_buf[CRC_SIZE] = {0};          // crc buffer
        static unsigned char Total_buf[TOTAL_SIZE] = {0};      // total buffer
        unsigned short crc;   // crc cost
        int to_crc_low_len = 0;		// length from init buffer to the low crc buffer
        int to_crc_high_len = 0;	// length from init buffer to the high crc buffer
	int j=0;
        
        for (int i=0; i < (int)len; i++)
        {
		// if buffer is '0x7D' then next buffer must be '0x5D'
		if(data_buf[i] == 0x7D)  {
			Total_buf[i + j + 1] = 0x7D;
			j++;
			Total_buf[i + j + 1] = 0x5D;
		}
		// if buffer is '0x7E' then next buffer must be '0x5E'
		else if(data_buf[i] == 0x7E) {                                                  
			Total_buf[i + j + 1] = 0x7D;                                                
			j++;                                                    
			Total_buf[i + j + 1] = 0x5E;                                                
		}
		else {
			Total_buf[j+i+1] =data_buf[i];
		}
        }
        
        // calculate crc cost with data.
 	    crc = crc16_ccitt(data_buf, len);

        // split crc cost to two character buffer 
        crc_buf[0] = (crc & 0xFF00) >> 8;
        crc_buf[1] = (crc & 0x00FF);
	
	printf("crc[0] : %02X, crc[1] : %02X\n ", crc_buf[0], crc_buf[1]);

	// let's bind whole buffer to total buffer.
        // total buffer consist of 
        // init buffer(7E) +
        // data buffer(with 5D, 5E or not ) +
        // crc buffer + end buffer (7E)

        // this is init buffer
        Total_buf[0] = 0x7E;
        
        // j is crc indication variable. so left buffer has lower crc cost
        // and right buffer has upper crc cost. 
        if (crc_buf[0] == 0x7E) {
		Total_buf[len + CRC_SIZE - 1 + j] = 0x7D;
		Total_buf[len + CRC_SIZE - 1 + j + 1] = 0x5E;
		to_crc_low_len = len + CRC_SIZE -1 +j +1;
	}
        else if (crc_buf[0] == 0x7D) {
		Total_buf[len + CRC_SIZE - 1 + j] = 0x7D;
		Total_buf[len + CRC_SIZE - 1 + j + 1] = 0x5D;
		to_crc_low_len = len + CRC_SIZE -1 +j +1 ;
	}
	else {
		Total_buf[len + CRC_SIZE - 1 + j] = crc_buf[0];
		to_crc_low_len = len + CRC_SIZE -1 +j;
	}

        if (crc_buf[1] == 0x7E) {
		Total_buf[to_crc_low_len + 1 ] = 0x7D;
		Total_buf[to_crc_low_len + 2] = 0x5E;
		to_crc_high_len = to_crc_low_len + 2;
	}
        else if (crc_buf[1] == 0x7D) {
		Total_buf[to_crc_low_len + 1] = 0x7D;
		Total_buf[to_crc_low_len + 2] = 0x5D;
		to_crc_low_len = to_crc_low_len + 2 ;
	}
	else {
		Total_buf[to_crc_low_len + 1] = crc_buf[1];
		to_crc_high_len = to_crc_low_len + 1;
	}
     
        // this is end buffer.
        Total_buf[to_crc_high_len + 1] = 0x7E;

        return Total_buf;
}


/*
 * HDLC decoding function 
 */
char*     HDLC_decoding(char* data_buf, int len)
{
     	unsigned char crc_buf[CRC_SIZE] = {0};          // crc buffer
        unsigned char Total_buf[TOTAL_SIZE] = {0};      // total buffer
        unsigned char Temp_buf[TOTAL_SIZE] = {0};	// temp buffer
//	//unsigned short 8crc;   // crc cost
        //static int data_flag = 0; 
	//static int i = 0;
	int org_data_len = 0;
	int j=0;
	

	for (int i = 0; i < len; i++)
	{
		if(data_buf[i] != 0x7E) {
			if(data_buf[i] == 0x7D && data_buf[i+1] == 0x5D)
			{
				Total_buf[j] = 0x7D;
				j++; i++;
			}
			else if (data_buf[i] == 0x7D && data_buf[i+1] == 0x5E)
			{	Total_buf[j] = 0x7E;
				j++; i++;
			}
			else {
				Total_buf[j] = data_buf[i];
				j++;
			}
		}
	}

	for (int i = 0; i< j - CRC_SIZE ; i++)
	{
		printf("[%02X] ", (unsigned char)Total_buf[i]);
	}
	printf("\n");
	printf("CRC[0] : %02X, CRC[1] : %02X", Total_buf[j - 2], Total_buf[j - 1]);
	printf("\n");

}
        

/*
 *
 */

void decoded_file_gen(const char * file_r, const char * file_w)
{
	unsigned char *buffer;
	unsigned char *p;
	unsigned char temp[TOTAL_SIZE] = {0};
	int size;
	int count;
	int init_end_flags = 0;
	int j = 0;
	
	FILE *pFile_r = fopen(file_r, "r");
	//FILE *pFile_w = fopen(file_w, "wt");

	fseek(pFile_r, 0, SEEK_END);
	size = ftell(pFile_r);

	buffer = malloc(size + 1);

	memset(buffer, 0, size + 1);

	fseek(pFile_r, 0, SEEK_SET);
	count = fread(buffer, size, 1, pFile_r);



	printf ("size: %d, count: %d\n", size, count);
	
	for(int i = 0; i < size; i++)
	{
		temp[j] = buffer[i]; 
		j++;

		if(buffer[i] == 0x7E)
			init_end_flags++;

		if(init_end_flags == 2)
		{
			init_end_flags = 0;
			//printf("%s\n ", temp);
		 	HDLC_decoding(temp, j);
			memset(temp, 0x00, j);
			j = 0;
		}

	}

	
	

	fclose(pFile_r);

	free(buffer);

}


unsigned int data_length(char* data_buf, int opt)
{
	int init_end_flags = 0;

	
	for(int i = 0; i < TOTAL_SIZE; i++)
	{
		if(data_buf[i]  == 0x7E)
			init_end_flags++;

		if(init_end_flags == 2)
		{
			switch(opt) {
				case HDLC_DATA :
					return i+1;

				case ORG_CRC_DATA :
					return i + 1 -2;

				case ORG_DATA :
					return i + 1 -4;
			}
		}
	}
}

					
	




void data_viewer(char * data_buf, int len)
{
	for (int i = 0; i < len; i++)
	{
		printf("[%02X] ", (unsigned char)data_buf[i]);
	}
    printf("\n");
}
