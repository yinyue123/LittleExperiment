#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include <linux/icmp.h>
#include <strings.h>
#include <netinet/ip_icmp.h>
#include <stdlib.h>

#include <sys/ioctl.h>	//GetLocalIp
#include <net/if.h>	//GetLocalIp

#include<netdb.h>	//scanport
#include<unistd.h>	//scanport
#include<fcntl.h>	//scanport
#include<time.h> 	//scanport

int flag = 1;

// scanport

//参数是目标机的IP  
int scanport(char *ip, char *result)  
{  
	struct sockaddr_in server;  
	int ret;  
	int len;  
	int scanport[4] = { 21, 22, 23, 80 }; 
	int sockfd;  
	int i;
	char temp[20];

	fd_set rset;  
	fd_set wset;   
	struct servent *sp;  
	
	*result = '\0';

	for(i=0; i<4; i++)  
	{
		if (-1==(sockfd=socket(AF_INET,SOCK_STREAM,0)))  
		{  
			perror("can not create socket\n");  
			exit(1);  
		}  

		memset(&server,0,sizeof(struct sockaddr_in));  
		server.sin_family = AF_INET;  
		server.sin_addr.s_addr = inet_addr(ip);  
		server.sin_port = htons(scanport[i]);  

		int flag1 = fcntl(sockfd, F_GETFL,0);  
		fcntl(sockfd,F_SETFL, flag1|O_NONBLOCK);  
		struct timeval tm;  
		tm.tv_sec = 0;
		tm.tv_usec = 50000;
	
		//connect为非阻塞，连接不成功立即返回-1  
		if (!connect(sockfd,(struct sockaddr*)&server,sizeof(struct sockaddr))){
			sp=getservbyport(htons(scanport[i]),"tcp");
			sprintf(temp, "tcp port %d open:%s\n ",scanport[i],sp->s_name);
			strcat(result, temp);
		}//假如连接不成功，则运行select,直到超时
		else {  
			FD_ZERO(&rset);  
			FD_ZERO(&wset);  
			FD_SET(sockfd, &rset);  
			FD_SET(sockfd, &wset);  
			int error; //错误代码  
			int len = sizeof(error);   
			//5秒后查看socket的状态变化   
			if (select(sockfd+1,&rset,&wset,NULL,&tm)>0){  
				getsockopt(sockfd, SOL_SOCKET, SO_ERROR,&error, &len );  
				if(error == 0){
					sprintf(temp, "Port %d is opened\n", scanport[i]);
					strcat(result,temp);
				}
			}  
		}  
		close(sockfd);  
	}  
	return 0;  
}

// scanip
void err_sys(const char *errmsg)  
{
	perror(errmsg);
//	exit(1);  
}

uint16_t in_cksum(uint16_t *addr, int len)  
{
	int nleft = len;
	uint32_t sum = 0;
	uint16_t *w = addr;
	uint16_t answer = 0;
	while (nleft > 1) {
		sum += *w++;
		nleft -= 2;
	}  

	if (nleft == 1) {
		*(unsigned char *)(&answer) = *(unsigned char *)w ;
		sum += answer;
	}

	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;
	return(answer);  
}

void send_echo_req(int sockfd, struct sockaddr_in *dstaddr)  
{
	char buf[100];
	size_t len = sizeof(struct icmp);
	struct icmp *icmp;
	socklen_t dstlen = sizeof(struct sockaddr_in);
//printf("send\n");
	bzero(buf, sizeof(buf));
	icmp = (struct icmp *)buf;
	icmp->icmp_type = ICMP_ECHO;//8
	icmp->icmp_code = 0;
	icmp->icmp_id = getpid();
	icmp->icmp_seq = 1;
	icmp->icmp_cksum = in_cksum((uint16_t *) icmp, sizeof(struct icmp));
	if (sendto(sockfd, buf, len, 0, (struct sockaddr *)dstaddr, dstlen) == -1)
		err_sys("sendto");  
}

int recv_echo_reply(int sockfd)  
{
	int i;
	char buf[100];
	ssize_t n;
	struct ip *ip;
	struct icmp *icmp;
	
	struct timeval tv;
	fd_set readfds;

	for(i = 0; i < 2; i++) {
		//alarm(5); /* set timeout */
//printf("recv\n");
		FD_ZERO(&readfds);
		FD_SET(sockfd, &readfds);
		tv.tv_sec = 0;
		tv.tv_usec = 200000;	//50000
		select(sockfd+1,&readfds,NULL,NULL,&tv);
		if(FD_ISSET(sockfd,&readfds))
		{

			if ((n = read(sockfd, buf, sizeof(buf))) == -1)
				err_sys("read");
			ip = (struct ip *)buf;

			if (ip->ip_p != IPPROTO_ICMP) {
				fprintf(stderr, "protocol error.");
				exit(1);
			}

			icmp = (struct icmp *)(buf + sizeof(struct ip));

			if (icmp->icmp_type == ICMP_ECHOREPLY) {
			/*if (icmp->icmp_id != getpid()) {
				fprintf(stderr, "not this process.");
				exit(1);
			} else {
				printf("destination host is alive.\n");
				break;
			}*/
			return 1;
			}
		}
	}	
	return 0;
}

int ping(char* ip)
{
	static int sockfd;
	struct sockaddr_in dstaddr;
//	struct timeval timeout = {0,10};
	if(flag){
	if ((sockfd = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1)
		err_sys("socket");
		flag = 0;
	}

	bzero(&dstaddr, sizeof(dstaddr));
	dstaddr.sin_family = AF_INET;
	dstaddr.sin_port = htons(0);
	
//	int flag=0;

//	flag = setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO,&timeout, sizeof(struct timeval ));
	
//	printf("##### flag : %d, SOCKET_ERROR : ",flag);

	if (inet_pton(AF_INET, ip, &dstaddr.sin_addr) <= 0)
		err_sys("inet_pton");

	send_echo_req(sockfd, &dstaddr);
	return recv_echo_reply(sockfd); 
} 

int getNum(int num, int flag2)
{
	return num+(flag2/2)*((flag2%2)?-1:1);
}

//save result
void add(char* buf)
{
	static FILE *fp;
	static int times=0;
	if(times == 0)
	{
		if((fp = fopen("scan.log","w")) == NULL)
		{
			printf("Open log file error!\n");
		}
	}
	if(fprintf(fp, "%s\n", buf) < 0)
	{
		printf("Write log error\n");
	}
	if(!(times++ % 10))
	{
		fflush(fp);
	}
	printf("%s\n", buf);
	if(!strcmp(buf,"finish"))
		fclose(fp);
}

int scan(char* temp)
{
	int ip[4];
	int i,j,k;
	int start, stop;
	char ipbuf[16],	msgbuf[80], cpy[16];
	strcpy(cpy,temp);
	ip[0]=atoi(strtok(cpy, "."));
	ip[1]=atoi(strtok(NULL, "."));
	ip[2]=atoi(strtok(NULL, "."));
	if(ip[0] == 10)
		start = 0, stop = 255;
	else if(ip[0] == 172)
		start = 16, stop = 31;
	else if(ip[0] == 192)
		start = 168, stop = 168;
	for(i=1; (getNum(ip[1], i)>=start && getNum(ip[1], i)<=stop) || (getNum(ip[1], i+1)>=start && getNum(ip[1], i+1)<=stop); i++)
		if(getNum(ip[1], i)>=start && getNum(ip[1], i)<=stop)
			for(j=1; (getNum(ip[2], j)>=0 && getNum(ip[2], j)<=255) || (getNum(ip[2], j+1)>=0 && getNum(ip[2], j+1)<=255); j++)		
				if(getNum(ip[2], j)>=0 && getNum(ip[2], j)<=255)
					if((ip[3]=1) /*&& ping(ipbuf)*/)
						for(ip[3]=1; ip[3]<255; ip[3]++)
						{
							sprintf(ipbuf,"%d.%d.%d.%d", ip[0], getNum(ip[1], i), getNum(ip[2], j), ip[3]);
							//printf("test\n");
							//printf("\t\t%s\n", ipbuf);
							
/*							struct timeval delay;
							delay.tv_sec = 0;
							delay.tv_usec=20000;
							select(0, NULL, NULL, NULL, &delay);*/
							if(ping(ipbuf))
							{
								add(ipbuf);
								scanport(ipbuf, msgbuf);
								add(msgbuf);
							}
//							if(ip[3] == 254)
//								ip[3] = 1;
						}

}

// getLocalIP
char* GetLocalIp()  
{        
    int MAXINTERFACES=16;  
    char *ip = NULL;  
    int fd, intrface, retn = 0;    
    struct ifreq buf[MAXINTERFACES];    
    struct ifconf ifc;    
 
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) >= 0)    
    {    
        ifc.ifc_len = sizeof(buf);    
        ifc.ifc_buf = (caddr_t)buf;    
        if (!ioctl(fd, SIOCGIFCONF, (char *)&ifc))    
        {    
            intrface = ifc.ifc_len / sizeof(struct ifreq);    
 
            while (intrface-- > 0)    
            {    
                if (!(ioctl (fd, SIOCGIFADDR, (char *) &buf[intrface])))    
                {    
                    ip=(inet_ntoa(((struct sockaddr_in*)(&buf[intrface].ifr_addr))->sin_addr));    
                    break;  
                }                        
            }  
        }    
        close (fd);    
        return ip;    
    }  
}

int main()
{
	scan(GetLocalIp());
	add("finish");
}
