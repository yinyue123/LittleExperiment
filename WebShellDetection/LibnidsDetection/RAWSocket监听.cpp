#define RCVALL_ON 1
#define MAX_ADDR_LEN 16
#define MAX_PROTO_TEXT_LEN 16 //��Э������(��"TCP")��󳤶�
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

typedef struct iphdr          //����IP�ײ�
{
    unsigned char h_lenver; //4λ�ײ�����+4λIP�汾��
    unsigned char tos; //8λ��������TOS
    unsigned short total_len; //16λ�ܳ��ȣ��ֽڣ�
    unsigned short ident; //16λ��ʶ
    unsigned short frag_and_flags; //3λ��־λ
    unsigned char ttl; //8λ����ʱ�� TTL
    unsigned char proto; //8λЭ�� (TCP, UDP ������)
    unsigned short checksum; //16λIP�ײ�У���
    unsigned int sourceIP; //32λԴIP��ַ
    unsigned int destIP; //32λĿ��IP��ַ
}IPHeader;


typedef struct _tcphdr    //����TCP�ײ�
{
 USHORT th_sport; //16λԴ�˿�
 USHORT th_dport; //16λĿ�Ķ˿�
 unsigned int  th_seq; //32λ���к�
 unsigned int  th_ack; //32λȷ�Ϻ�
 unsigned char th_lenres; //4λ�ײ�����/6λ������
 unsigned char th_flag; //6λ��־λ
 USHORT th_win; //16λ���ڴ�С
 USHORT th_sum; //16λУ���
 USHORT th_urp; //16λ��������ƫ����
}TCP_HEADER;




typedef struct _udphdr //����UDP�ײ�
{
    unsigned short uh_sport; //16λԴ�˿�
    unsigned short uh_dport; //16λĿ�Ķ˿�
    unsigned short uh_len; //16λ����
    unsigned short uh_sum; //16λУ���
}UDP_HEADER;




typedef struct _icmphdr   //����ICMP�ײ�
{
 BYTE   i_type;    //8λ����
 BYTE   i_code;    //8λ����
 USHORT i_cksum;   //16λУ��� 
 USHORT i_id;    //ʶ��ţ�һ���ý��̺���Ϊʶ��ţ�
 USHORT i_seq;    //�������к� 
 ULONG  timestamp;   //ʱ���
}ICMP_HEADER;
//functions
int DecodeTcpPack(char *, int); //TCP�������
int DecodeUdpPack(char *, int); //UDP�������
int DecodeIcmpPack(char *, int); //ICMP�������
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
  //Դ��ַ
   saSource.sin_addr.s_addr = iph->sourceIP;
   strncpy(szSourceIP, inet_ntoa(saSource.sin_addr), MAX_ADDR_LEN);
  //Ŀ�ĵ�ַ
   saDest.sin_addr.s_addr = iph->destIP;
   strncpy(szDestIP, inet_ntoa(saDest.sin_addr), MAX_ADDR_LEN);
  iTTL = iph->ttl;
  //����IP�ײ��ĳ���
  int IpHeadLen = 4 * (iph->h_lenver & 0xf);
  //����Э�����ͷֱ������Ӧ�ĺ���
  
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
//TCP�������
int DecodeTcpPack(char * TcpBuf, int iBufSize)
{
 unsigned char FlagMask;FlagMask = 1;
 int i;
 TCP_HEADER *tcph;
 
 tcph = (TCP_HEADER*)TcpBuf;
 //����TCP�ײ�����
 int TcpHeadLen = tcph->th_lenres>>4;
 TcpHeadLen *= sizeof(unsigned long);
 char *TcpData=TcpBuf+TcpHeadLen; 
 iSourcePort = ntohs(tcph->th_sport);
 iDestPort   = ntohs(tcph->th_dport);
 
 //���
 printf("TCP  ");
 printf("%15s:%5d ->%15s:%5d  ", szSourceIP, iSourcePort, szDestIP, iDestPort);
 printf("TTL=%3d  ", iTTL);
 if(fflag==1)
 
 //�ж�TCP��־λ
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
//UDP�������
int DecodeUdpPack(char * UdpBuf, int iBufSize)
{
 UDP_HEADER *udph;
 udph = (UDP_HEADER*)UdpBuf;
 iSourcePort = ntohs(udph->uh_sport);
 iDestPort   = ntohs(udph->uh_dport);
 //���
 printf("UDP  ");
 printf("%15s:%5d ->%15s:%5d  ", szSourceIP, iSourcePort, szDestIP, iDestPort);
 printf("TTL=%3d ", iTTL);
 printf("Len=%4d ", ntohs(udph->uh_len));
 printf("bytes=%4d", iBufSize);
 printf("\n");
 return 0;
}
//ICMP�������
int DecodeIcmpPack(char * IcmpBuf, int iBufSize)
{
 ICMP_HEADER * icmph;
 icmph = (ICMP_HEADER * )IcmpBuf;
 int iIcmpType = icmph->i_type;
 int iIcmpCode = icmph->i_code;
 //���
 printf("ICMP ");
 printf("%15s       ->%15s        ", szSourceIP, szDestIP);
 printf("TTL=%3d ", iTTL);
 printf("Type%2d,%d ",iIcmpType,iIcmpCode);
 printf("bytes=%4d", iBufSize);
 printf("\n"); 
 return 0;
} 