#ifndef __telnet_client_h_
#define __telnet_client_h_

/* ��ǰһ���ֽ���IAC ʱ�� ��� */
enum{
	CMD_EOF 	= 236,
	CMD_SUSP 	= 237,
	CMD_ABORT 	= 238,
	CMD_EOR 	= 239,
	CMD_SE 		= 240,
	CMD_NOP 	= 241,
	CMD_DM 	= 242,
	CMD_BRK 	= 243,
	CMD_IP		= 244,
	CMD_AO		= 245,
	CMD_AYT	= 246,
	CMD_EC		= 247,
	CMD_EL		= 248,
	CMD_GA		= 249,
	CMD_SB		= 250,
	CMD_WILL	= 251,
	CMD_WONT	= 252,
	CMD_DO		= 253,
	CMD_DONT	= 254,
	CMD_IAC		= 255
};

/* ��Э��ѡ�� */
#define OP_BIN_TRANS	0
#define OP_ECHO			1
#define OP_SUP_GA		3
#define OP_STATUS		5
#define OP_TERM_TYPE	24
#define OP_WIN_SIZE		31
#define OP_TERM_RATE	32
#define OP_FLOW_CTRL	33
#define OP_LINE_MODE	34


#define MODE_CHAR			1
#define MODE_LINE			2
#define MY_TERM_TYPE		"LINUX"
#define CONNECT_TIMEOUT		5

typedef struct
{
	int commit_mode;
	int connected;
	int fd;
}tel_ctrl;


int telnet_init(tel_ctrl *tel_info);
int telnet_connect(char *server_ip,unsigned short server_port,tel_ctrl *tel_info);
int telnet_deal_cmd(char *user_buf,int count,tel_ctrl *tel_info);
int telnet_get(unsigned char *msg_to_user,tel_ctrl *tel_info);
void telnet_free(tel_ctrl *tel_info);


#endif

