/*
 * 程序说明：
 * 1.程序需要以超级权限运行
 * 2.当使用PHPSPY和Read_group两种木马时，程序可以抓到他们包，分析如果有木马特征，则报警，并区分出他们两个
 * 
 * 编译
 * gcc PhpspyCheck.c -o PhpspyCheck -lnids -lpcap -lnet
 * 
 * 注意:
 * 编译时注意后面三个的排列顺序，lnids在第一个位置，其余两个位置随意
 * 前五个头文件需要包含，负责可能编译好的程序会读取IP的时候会出BUG，并且出现warning
 * 标准输出库相关的头文件需要包含，负责出现warning
 * 需要选择监听的网卡设备
 * 需要关闭网络奇偶校验，负责有些机器网卡完成奇偶校验，所得的包奇偶校验为0,数据包被丢弃
 * 有时候使用printf()函数，程序可能不会马上将结果显示出来，可以使用 fprintf(stdout,"...");fflush(stdout);两个函数将需要刷新的内容马上显示出来
 *
 * 抓包，获取特征
 * sudo tcpdump -i eth0  host 115.159.155.95 and port 80 -w phpspy.cap
 * wireshark phpspy.cap
 * 右键一个流，Follow TCP stream
 *
 * 查看两个流的不同
 * 先用vim将其保存起来
 * 再使用vimdiff命令查看其不同

*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nids.h"

int check(char* temp)
{
	char* Check[2][4]={
		{
			"Powered by",
			"PhpSpy 2013 final",
			"Copyright (C) 2004-2013",
			"All Rights Reserved."
		},{
			"PhpSpy 2013 final",
			"optimized for Korean by",
			"http://imfast.kr",
			"substr_sql"
		}};
	int count[2];
	int times[2];
	int i,j;
	count[0]=count[1]=4;
	times[0]=times[1]=0;
	i=j=0;
	for(i=0;i<2;i++)
		for(j=0;j<count[i];j++)
		{
			if(strstr(temp,Check[i][j]))
				times[i]++;
		}
	if(times[0]==count[0])
		return 1;
	else if(times[1]==count[1])
		return 2;
	return 0;
}

void http_protocol_callback(struct tcp_stream* tcp_http_connection,void** param)
{
	char address_content[1024];
	char content[65535];
	int whichOne=0;
	struct tuple4 ip_and_port=tcp_http_connection->addr;
	if(tcp_http_connection->nids_state == NIDS_JUST_EST)
	{
		if(tcp_http_connection->addr.dest != 80)
			return;
		tcp_http_connection->client.collect++;
		tcp_http_connection->server.collect++;
//		printf("建立连接...\n");
		return;
	}	
	if(tcp_http_connection->nids_state == NIDS_CLOSE)
	{
//		printf("链接正常关闭...\n");
		return;
	}
	if(tcp_http_connection->nids_state == NIDS_RESET)
	{
//		printf("连接被RST关闭...\n");	
		return;
	}
	if(tcp_http_connection->nids_state == NIDS_DATA)
	{
		struct half_stream* hlf;
		if(tcp_http_connection->client.count_new)
		{
//			printf("浏览器接受数据");
			hlf=&tcp_http_connection->client;
		}
		else
		{
//			printf("服务器接受数据");
			hlf=&tcp_http_connection->server;
		}
		memcpy(content,hlf->data,hlf->count_new);
		content[hlf->count_new]='\0';
		if(!(whichOne=check(content)))
			return ;
		if(whichOne==1){
			printf("Phpspy2013 is runing\n");
		}
		else if(whichOne==2){
			printf("read_group is runing\n");
		}
		strcpy(address_content,inet_ntoa(*((struct in_addr *) &(ip_and_port.saddr))));
		sprintf(address_content+strlen(address_content),":%i",ip_and_port.source);
		strcat(address_content,tcp_http_connection->client.count_new?"<----":"---->");
		strcat(address_content,inet_ntoa(*((struct in_addr *) &(ip_and_port.daddr))));
		sprintf(address_content+strlen(address_content),":%i",ip_and_port.dest);
		strcat(address_content,"\n");
		printf("%s",address_content);

	}
	return;
}

void main() 
{
/*	char input[10];
	printf("请输入你要监听的网卡:");
	scanf("%s",input);
	nids_params.device=input;*/
	nids_params.device="wlan0";
	if(!nids_init())
	{
		printf("error: %s\n",nids_errbuf);
		exit(1);
	}
	struct nids_chksum_ctl temp;
	temp.netaddr=0;
	temp.mask=0;
	temp.action=1;
	nids_register_chksum_ctl(&temp,1);

	nids_register_tcp(http_protocol_callback);
	nids_run();
}
