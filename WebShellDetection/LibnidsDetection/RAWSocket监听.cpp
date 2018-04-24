#define RCVALL_ON 1
#define MAX_ADDR_LEN 16
#define MAX_PROTO_TEXT_LEN 16 //子协议名称(如"TCP")最大长度
#define WINSOCK_VERSION MAKEWORD(2, 2)
#pragma comment(lib,"Ws2_32.lib")

#include <stdio.h>
#include <winsock2.h>
#include "mstcpip.h"
#include <conio.h>

///////////////////////////////////////////

#define PACKAGE_SIZE sizeof(IPHeader)+1000
int  iTTL,iLEN,iBYTES;
char szSourceIP[MAX_ADDR_LEN], szDestIP[MAX_ADDR_LEN];
int  iSourcePort,iDestPort;
int  fflag=0;//file flag

typedef struct iphdr          //定义IP首部
{
    unsigned char h_lenver; //4位首部长度+4位IP版本号
    unsigned char tos; //8位服务类型TOS
    unsigned short total_len; //16位总长度（字节）
    unsigned short ident; //16位标识
    unsigned short frag_and_flags; //3位标志位
    unsigned char ttl; //8位生存时间 TTL
    unsigned char proto; //8位协议 (TCP, UDP 或其他)
    unsigned short checksum; //16位IP首部校验和
    unsigned int sourceIP; //32位源IP地址
    unsigned int destIP; //32位目的IP地址
}IPHeader;


typedef struct _tcphdr    //定义TCP首部
{
 USHORT th_sport; //16位源端口
 USHORT th_dport; //16位目的端口
 unsigned int  th_seq; //32位序列号
 unsigned int  th_ack; //32位确认号
 unsigned char th_lenres; //4位首部长度/6位保留字
 unsigned char th_flag; //6位标志位
 USHORT th_win; //16位窗口大小
 USHORT th_sum; //16位校验和
 USHORT th_urp; //16位紧急数据偏移量
}TCP_HEADER;




typedef struct _udphdr //定义UDP首部
{
    unsigned short uh_sport; //16位源端口
    unsigned short uh_dport; //16位目的端口
    unsigned short uh_len; //16位长度
    unsigned short uh_sum; //16位校验和
}UDP_HEADER;




typedef struct _icmphdr   //定义ICMP首部
{
 BYTE   i_type;    //8位类型
 BYTE   i_code;    //8位代码
 USHORT i_cksum;   //16位校验和 
 USHORT i_id;    //识别号（一般用进程号作为识别号）
 USHORT i_seq;    //报文序列号 
 ULONG  timestamp;   //时间戳
}ICMP_HEADER;
//functions
int DecodeTcpPack(char *, int); //TCP解包函数
int DecodeUdpPack(char *, int); //UDP解包函数
int DecodeIcmpPack(char *, int); //ICMP解包函数
////////////////////////////////////////
int main(int argc, char *argv[])
{
	DWORD dwErr;
	//sockaddr_in saSource,saDest;
	WSAData wsaData;
	WSAStartup(WINSOCK_VERSION, &wsaData);
	SOCKET sock=socket(AF_INET,SOCK_RAW,IPPROTO_IP);
	if(sock == SOCKET_ERROR)
	{
		dwErr = WSAGetLastError();
		printf("Error socket() = %d",dwErr);
		closesocket( sock );
		return 0;
	}
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	char name[256];
	PHOSTENT hostinfo;
	if( gethostname ( name, sizeof(name)) == 0)
	{
		if((hostinfo = gethostbyname( name )) !=NULL)
		{
			memcpy(&(addr.sin_addr.S_un.S_addr),(struct in_addr *)*hostinfo->h_addr_list,sizeof((struct in_addr *)*hostinfo->h_addr_list ));
		}
	}
	addr.sin_family = AF_INET;
	if(bind (sock, (struct sockaddr *)&addr,sizeof(addr)) == SOCKET_ERROR)
	{
		dwErr = WSAGetLastError();
		printf("bind() = %d",dwErr);
		closesocket(sock);
	}
	DWORD num;
    int on = RCVALL_ON;
	if(WSAIoctl(sock, SIO_RCVALL, &on, sizeof(on), NULL, 0, &num, NULL, NULL) == SOCKET_ERROR)
	{
		dwErr = WSAGetLastError();
		printf( "Error WSAIoctl = %ld " , dwErr ) ;
		closesocket( sock ) ;
	}

//////////////////////////////////////////////////////////
    struct sockaddr_in from;
	char buf[PACKAGE_SIZE];
	int fromlen;
    int size;
	sockaddr_in saSource,saDest;
	    while(!kbhit())
    {
        memset(buf, 0, sizeof(num));
        memset(&from, 0, sizeof(from));
        fromlen = sizeof(from);
  size=recvfrom(sock, buf, PACKAGE_SIZE, 0, (struct sockaddr*)&from, &fromlen);
        if(size == SOCKET_ERROR)
  {
   if(WSAGetLastError() == WSAEMSGSIZE)
            {
//                HandleError("recvfrom");
                continue;
            }
        }
  IPHeader *iph=(IPHeader *)buf;
  /**/
  //源地址
   saSource.sin_addr.s_addr = iph->sourceIP;
   strncpy(szSourceIP, inet_ntoa(saSource.sin_addr), MAX_ADDR_LEN);
  //目的地址
   saDest.sin_addr.s_addr = iph->destIP;
   strncpy(szDestIP, inet_ntoa(saDest.sin_addr), MAX_ADDR_LEN);
  iTTL = iph->ttl;
  //计算IP首部的长度
  int IpHeadLen = 4 * (iph->h_lenver & 0xf);
  //根据协议类型分别调用相应的函数
  
        switch(iph->proto)
        {
        case IPPROTO_ICMP:
   DecodeIcmpPack(buf+IpHeadLen, size);
            break;
        case IPPROTO_IGMP:
            printf("IGMP ");
   printf("%15s:      ->%15s:       ", szSourceIP, szDestIP);
            printf("%d",size);
            printf("%s\n", buf);
            break;
        case IPPROTO_TCP:
   DecodeTcpPack((buf+IpHeadLen),size);
            break;
        case IPPROTO_UDP:
   DecodeUdpPack(buf+IpHeadLen, size);
            break;
        default:
            printf("unknown datagram from %s\n", inet_ntoa(from.sin_addr));
            printf("%s\n", buf);
   break;
        }//end switch
  
       // Sleep(200);
    }//end while
    closesocket(sock);
    WSACleanup();
    printf("Stopped!\n");
 getch();
    return 0;
}//end of main
//TCP解包程序
int DecodeTcpPack(char * TcpBuf, int iBufSize)
{
 unsigned char FlagMask;FlagMask = 1;
 int i;
 TCP_HEADER *tcph;
 
 tcph = (TCP_HEADER*)TcpBuf;
 //计算TCP首部长度
 int TcpHeadLen = tcph->th_lenres>>4;
 TcpHeadLen *= sizeof(unsigned long);
 char *TcpData=TcpBuf+TcpHeadLen; 
 iSourcePort = ntohs(tcph->th_sport);
 iDestPort   = ntohs(tcph->th_dport);
 
 //输出
 printf("TCP  ");
 printf("%15s:%5d ->%15s:%5d  ", szSourceIP, iSourcePort, szDestIP, iDestPort);
 printf("TTL=%3d  ", iTTL);
 if(fflag==1)
 
 //判断TCP标志位
 for( i=0; i<6; i++ )
 {
  if((tcph->th_flag) & FlagMask)
   printf("1");
  else printf("0");
  FlagMask=FlagMask<<1;
 }
 printf("  bytes=%4d", iBufSize);
 printf("\n");
 return 0;
}
//UDP解包程序
int DecodeUdpPack(char * UdpBuf, int iBufSize)
{
 UDP_HEADER *udph;
 udph = (UDP_HEADER*)UdpBuf;
 iSourcePort = ntohs(udph->uh_sport);
 iDestPort   = ntohs(udph->uh_dport);
 //输出
 printf("UDP  ");
 printf("%15s:%5d ->%15s:%5d  ", szSourceIP, iSourcePort, szDestIP, iDestPort);
 printf("TTL=%3d ", iTTL);
 printf("Len=%4d ", ntohs(udph->uh_len));
 printf("bytes=%4d", iBufSize);
 printf("\n");
 return 0;
}
//ICMP解包程序
int DecodeIcmpPack(char * IcmpBuf, int iBufSize)
{
 ICMP_HEADER * icmph;
 icmph = (ICMP_HEADER * )IcmpBuf;
 int iIcmpType = icmph->i_type;
 int iIcmpCode = icmph->i_code;
 //输出
 printf("ICMP ");
 printf("%15s       ->%15s        ", szSourceIP, szDestIP);
 printf("TTL=%3d ", iTTL);
 printf("Type%2d,%d ",iIcmpType,iIcmpCode);
 printf("bytes=%4d", iBufSize);
 printf("\n"); 
 return 0;
} 