#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>

#include "common.h"
#include "telnet_client.h"
#include "redirect.h"

static void create_sub_op(unsigned char op,unsigned char num,char *in_str,unsigned char *out_str,int *option_len)
{
	int string_size=0;

	*out_str++ = op;
	*out_str++ = num;
	while((*(out_str+string_size)=*(in_str+string_size)) != '\0'){
		string_size++;
	};
	out_str += string_size;
	*out_str++ = CMD_IAC;
	*out_str++ = CMD_SE;

	*option_len = 4+string_size;
}

static int get_cmd_option(unsigned char *buf,unsigned char *cmd,unsigned char *option,int *used_len,int spare_len)
{
	int i=0;
	
	if((*buf != CMD_IAC) || ((*buf == CMD_IAC) &&(*(buf+1) == CMD_IAC))){
		for(i=0;i<spare_len;i++){
			output_to_user("%c",buf[i]);
		}
		return -1;
	}
	i++;

	*cmd = *(buf+i++);
	if(*cmd == CMD_SB){
		while(i<spare_len){
			*option++ = *(buf+i);
			if((*(buf+i-1) == CMD_IAC) && (*(buf+i) == CMD_SE)){
				i++;
				break;
			}
			i++;
		}
	}
	else{
		*option++ = *(buf+i++);
	}

	*used_len = i;

	return 0;
}

static void create_ret_pack(unsigned char *buf,unsigned char cmd,unsigned char *option,int *used_len)
{
	unsigned char cmd_send=0;
	int option_len=0,i;
	unsigned char op[32];
	
	*buf++ = CMD_IAC;
	switch (cmd){
		case CMD_DO:
			switch (*option){
				case OP_ECHO:
				case OP_SUP_GA:
				case OP_BIN_TRANS:
				case OP_TERM_TYPE:
					cmd_send = CMD_WILL;
					op[0] = *option;
					break;
				default:
					op[0] = *option;
					cmd_send = CMD_WONT;
					break;				
			}
			option_len = 1;
			break;
		case CMD_WILL:
			switch (*option){
				//case OP_ECHO:   //关闭好一点，免得看起来都隔了一行
				case OP_SUP_GA:
				case OP_BIN_TRANS:
				case OP_TERM_TYPE:
					cmd_send = CMD_DO;
					op[0] = *option;
					break;
				default:
					cmd_send = CMD_DONT;
					op[0] = *option;
					break;				
			}
			option_len = 1;
			break;
		case CMD_DONT:
			cmd_send = CMD_WONT;
			op[0] = *option;
			option_len = 1;
			break;
		case CMD_WONT:
			cmd_send = CMD_DONT;
			op[0] = *option;
			option_len = 1;
			break;
		case CMD_SB:
			switch (*option){
				case OP_TERM_TYPE:
					cmd_send = CMD_SB;
					create_sub_op(OP_TERM_TYPE,0,MY_TERM_TYPE,op,&option_len);
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
	*buf++ = cmd_send;
	for(i=0;i<option_len;i++){
		*(buf+i) = op[i];
	}
	*used_len = 1+1+option_len;
}

/* 根据自己的情况与服务器协商 */
static void negotiate(unsigned char *buf,unsigned char *msg_to_svr,int buf_len,int *p_msglen,tel_ctrl *tel_info)
{
	int tmp_len=0,used_len=0,spare_len;
	int used_len1=0,total_len=0;
	unsigned char cmd=0;
	unsigned char option[32];

	spare_len = buf_len;
	while(spare_len>0){
		if(get_cmd_option(buf+used_len,&cmd,option,&tmp_len,spare_len) == -1){//解析出一次命令
			break;
		}
		used_len += tmp_len;
		spare_len -= tmp_len;	
		/* 把这个命令的处理结果追加到准备发送到服务器的buffer */
		create_ret_pack(msg_to_svr+total_len,cmd,option,&used_len1);
		total_len += used_len1;
	}
	*p_msglen = total_len;
}

static int send_by_line(int fd,char *send_buf,int count)
{
	int n_send,retval;

	n_send = send(fd,send_buf,count,0);
	if(n_send < 0){
		return -1;
	}
	retval = send(fd,"\r\n",2,0);

	if(retval > 0){
		return n_send;
	}

	return -1;
}

static int send_by_char(int fd,char *send_buf,int count)
{
	int n_send,retval,total=0;

	while(count--){
		n_send = send(fd,send_buf++,1,0);
		total += n_send;
		if(n_send < 0){
			return -1;
		}
	}
	retval = send(fd,"\r\n",2,0);

	if(retval < 0){
		return -1;
	}
	
	return total;
}

static int telnet_send(char *send_buf,int count,tel_ctrl *tel_info)
{
	int n_send;

	if(tel_info->commit_mode == MODE_LINE){
		n_send = send_by_line(tel_info->fd,send_buf,count);
	}
	else if(tel_info->commit_mode == MODE_CHAR){
		n_send = send_by_char(tel_info->fd,send_buf,count);
	}
	else{
		n_send = send_by_char(tel_info->fd,send_buf,count);
	}

	return n_send;
}

int telnet_init(tel_ctrl *tel_info)
{
	tel_info->commit_mode = MODE_LINE;
	tel_info->connected = FALSE;
	tel_info->fd = -1;

	return 0;
}

int telnet_connect(char *server_ip,unsigned short server_port,tel_ctrl *tel_info)
{
	int sockfd,retval,len;
	struct sockaddr_in svr_addr;
	time_t pretime,nowtime;

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	len = sizeof(svr_addr);
	memset(&svr_addr,0,len);
	svr_addr.sin_family = AF_INET;
	svr_addr.sin_port = htons(server_port);
	svr_addr.sin_addr.s_addr = inet_addr(server_ip);

	setlock(sockfd,FALSE);
	pretime = time(NULL);
	do{
		retval = connect(sockfd,(struct sockaddr *)&svr_addr,len);
		nowtime = time(NULL);
		if((nowtime - pretime) > CONNECT_TIMEOUT){
			retval = -1;
			break;
		}
	}while(retval == -1);
	setlock(sockfd,TRUE);
	
	if(retval != 0){
		return -1;
	}

	tel_info->fd = sockfd;
	tel_info->connected = TRUE;
	return 0;
}

int telnet_deal_cmd(char *user_buf,int count,tel_ctrl *tel_info)
{
	int n_send,retval=0;

	n_send = telnet_send(user_buf,count,tel_info);
	
	//printf("%s+11\n",user_buf);
	
	if((user_buf[0]=='e') && (user_buf[1]=='x') && (user_buf[2]=='i') && (user_buf[3]=='t')){
		tel_info->connected = FALSE;
	}

	if(n_send < 0){
		retval = -1;
	}

	return retval;
}

int telnet_get(unsigned char *msg_to_user,tel_ctrl *tel_info)
{
	int n_recv;
	unsigned char buf[128];
	unsigned char msg_to_svr[128];
	int msg_len;

	*msg_to_user = '\0';

	setlock(tel_info->fd,FALSE);
	n_recv = recv(tel_info->fd,buf,128-1,0);
	if(n_recv <= 0){
		setlock(tel_info->fd,TRUE);
		return -1;
	}
	buf[n_recv] = '\0';
	setlock(tel_info->fd,TRUE);

	int i=0;
	if((buf[i] == CMD_IAC) && (buf[i+1] != CMD_IAC)){//如果是服务器在和我们协商
		negotiate(buf,msg_to_svr,n_recv,&msg_len,tel_info);
		telnet_send((char *)msg_to_svr,msg_len,tel_info);
	}
	else{			//如果是服务器返回的数据
		for(i=0;i<n_recv;i++){
			*(msg_to_user+i) = buf[i];
		}
		msg_to_user[n_recv] = '\0';
	}

	return 0;
}

void telnet_free(tel_ctrl *tel_info)
{ 
	tel_info->connected = FALSE;
	if(tel_info->fd){
		shutdown(tel_info->fd,2);
		close(tel_info->fd);
	}
}

