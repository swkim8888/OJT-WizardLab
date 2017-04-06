void make_crc_table(void);
void print_crc_table(void);
unsigned short crc16_ccitt(const void *buf, int len);
char * HDLC_encoding(char* argv, int len);


#define CRC_TABLE_SIZE          256
#define DATA_SIZE               10
#define CRC_SIZE                2
#define INIT_SIZE               1
#define END_SIZE                1
#define T0TAL_SIZE              50
