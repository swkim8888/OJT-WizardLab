void make_crc_table(void);
void print_crc_table(void);
unsigned short crc16_ccitt(const void *buf, int len);
char * HDLC_encoding(char* data_buf, int len);
unsigned char * HDLC_decoding(char* data_buf, int len);
//char * data_crc_checker();
void decoded_file_gen(const char * file_r, const char * file_w);
unsigned int data_length(char* data_buf, int opt);
void data_viewer(char * data_buf, int len);

#define CRC_TABLE_SIZE          256
#define DATA_SIZE               16
#define CRC_SIZE                2
#define INIT_SIZE               1
#define END_SIZE                1
#define TOTAL_SIZE              50


#define HDLC_DATA               1
#define ORG_CRC_DATA            2
#define ORG_DATA                3

