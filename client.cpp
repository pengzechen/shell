
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#pragma comment(lib,"ws2_32.lib")
#include <Winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main(int argc, char * argv[])
{
	WSADATA wsaData;
	SOCKET sClient;
	int iPort = 5050;

	struct sockaddr_in ser; //服务器端地址
	
	if(argc<2){
		printf("Usage: client [IP]\n"); //命令行提示
		return -1;
	}
	
	WSAStartup(MAKEWORD(2,2),&wsaData);
	ser.sin_family = AF_INET; //初始化服务器地址信息
	ser.sin_port = htons(iPort); //端口转换为网络字节序
	ser.sin_addr.s_addr = inet_addr(argv[1]); //IP 地址转换为网络字节序
	sClient = socket(AF_INET,SOCK_STREAM,0); //创建客户端流式套接字


	connect(sClient, (struct sockaddr *)&ser, sizeof(ser));
	char send_str[256] = "cd";
	while(1){


		send(sClient, send_str, sizeof(send_str), 0);

		char buf[1024*10]; //接收缓冲区
		recv(sClient,buf,sizeof(buf),0); //从服务器端接收数据
		printf("%s",buf); // 输出接收数据
		memset(buf, 0, 1024*10);

		memset(send_str, 0 ,256);
		std::cin.getline(send_str, 256);
	}

	closesocket(sClient); //关闭 socket
	WSACleanup();
	return 0;
}