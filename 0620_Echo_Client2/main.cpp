#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN ServerSockADDR;
	memset(&ServerSockADDR, 0, sizeof(SOCKADDR_IN));
	ServerSockADDR.sin_family = PF_INET;
	ServerSockADDR.sin_addr.s_addr = inet_addr("127.0.0.1"); //자기자신을 나타내는 ip
	ServerSockADDR.sin_port = htons(20000);

	if (connect(ServerSocket, (SOCKADDR*)&ServerSockADDR, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		cout << "Connect Failed" << endl;
		exit(-1);
	}

	char Message[] = "세번째 메세지3333333";
	send(ServerSocket, Message, strlen(Message), 0);
	char MessageRev[1024] = { 0, };
	int RevLenght = recv(ServerSocket, MessageRev, sizeof(MessageRev), 0);

	cout << MessageRev << endl;


	WSACleanup();
}