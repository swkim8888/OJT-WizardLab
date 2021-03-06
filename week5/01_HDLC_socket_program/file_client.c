#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "hdlc.h"

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sd;
	FILE *fp;
	
	char buf[TOTAL_SIZE] = {0};
	int read_cnt;
	struct sockaddr_in serv_adr;
	
	if(argc!=3) {
		printf("Usage: %s <IP> <port> \n", argv[0]);
		exit(1);
	}

	fp=fopen("receive.dat", "wb");
	sd=socket(PF_INET, SOCK_STREAM, 0);

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_adr.sin_port=htons(atoi(argv[2]));

	connect(sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr));

	while((read_cnt = read(sd, buf, TOTAL_SIZE))!=0)
	{
		//data_viewer(buf, strlen(buf));
		fwrite((void*)buf, 1, read_cnt, fp);
		memset(buf, 0x00, TOTAL_SIZE);
	}

	puts("Received file data");
	write(sd, "thank you", 10);
	fclose(fp);
	close(sd);

	decoded_file_gen("receive.dat", "aaaaaa");	

	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
