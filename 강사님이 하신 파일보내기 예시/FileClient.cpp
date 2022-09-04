#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS 

#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")


int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	FILE* OutputFP = fopen("test2.jpg", "wb");

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(SOCKADDR_IN));
	ServerSockAddr.sin_family = AF_INET;
	ServerSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServerSockAddr.sin_port = htons(50501);
	connect(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(SOCKADDR_IN));

	char Buffer[4096] = { 0, };
	int RecvLength = 0;
	do
	{
		RecvLength = recv(ServerSocket, Buffer, sizeof(Buffer), 0);
		size_t WriteSize = fwrite(Buffer, sizeof(char), RecvLength, OutputFP);
	} while (RecvLength > 0);

	fclose(OutputFP);

	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}