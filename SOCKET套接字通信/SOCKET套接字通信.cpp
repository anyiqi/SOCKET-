#include <iostream>
#include<winsock.h>
#include<windows.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
int main()
{

    WSADATA wsaDate;
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    if ((WSAStartup(MAKEWORD(2,2),&wsaDate))!= 0)
    {
        printf("初始化失败");
        return 0;
    }
    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_port=htons(6969);//端口；
    addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//IP地址。//0.0.0.0//监听本机所有端口//127.0.0.1//回环网络
    SOCKET client = socket(AF_INET, SOCK_STREAM, 0);
    if (SOCKET_ERROR == client)
    {
        printf("Socket()error%d", WSAGetLastError());
        return 0;
    }
    if (connect(client, (struct sockaddr*)&addr, sizeof(addr))==INVALID_SOCKET)
    {
        printf("链接失败%d",GetLastError());
        return  -1;
    }
    else
    {
        recv(client, buf, sizeof(buf), 0);
        printf("%s", buf);
    }

    char bufs[] = "开始发送";
    send(client, bufs, sizeof(bufs), 0);
    while (true)
    {
        cin >> bufs;
        send(client, bufs, sizeof(bufs), 0);
    }
    closesocket(client);
    WSACleanup();
    system("pause");
    return 0;
    cout << "Hello World!\n";
}