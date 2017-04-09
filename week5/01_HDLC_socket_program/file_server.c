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
	int serv_sd, clnt_sd;
	FILE * fp;
	char buf[TOTAL_SIZE];
	int read_cnt;

	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;

	if(argc!=2) {
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}

	printf("Servier start !!!\n");

	// make crc table();	
	make_crc_table();
	//print_crc_table();

	fp=fopen("file_server.c", "rb");
	serv_sd=socket(PF_INET, SOCK_STREAM, 0);

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));

	bind(serv_sd, (struct sockaddr*)&serv_adr, sizeof(serv_adr));
	listen(serv_sd, 5);

	clnt_adr_sz=sizeof(clnt_adr);
	clnt_sd=accept(serv_sd, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

	/*while(1)
	{
		read_cnt=fread((void*)buf, 1, 16, fp);
		if(read_cnt < 16)
		{
			//write(clnt_sd, buf, read_cnt);
			write(clnt_sd, buf, strlen(buf));
			printf("%s",buf);
			break;
		}
		//write(clnt_sd, buf, TOTAL_SIZE);
		//write(clnt_sd, buf, strlen(buf));
		printf("%s",buf);
		
	}*/

	while((read_cnt = fread((void*)buf, 1, 16, fp)) != 0)
	{
		unsigned char *p;
		
		printf("Data : <%d>, [%s]\n", (int)strlen(buf), buf);
		printf("Decoded Hex : ");
		data_viewer(buf, strlen(buf)); printf("\n\n"); 

		p = HDLC_encoding(buf, strlen(buf));
		printf("Decoded data : <%d> [%s]\n", (int)strlen(p) , p);
		printf("Decoded Hex : ");
		data_viewer(p, strlen(p)); printf("\n\n"); 

		write(clnt_sd, p, strlen(p));
		
		memset(p, 0x00, strlen(p));
		memset(buf, 0x00, strlen(buf));
		
	}

	shutdown(clnt_sd, SHUT_WR);
	read(clnt_sd, buf, TOTAL_SIZE);
	printf("Message from client: %s \n", buf);

	fclose(fp);
	close(clnt_sd); close(serv_sd);
	return 0;
}

void error_handlling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

