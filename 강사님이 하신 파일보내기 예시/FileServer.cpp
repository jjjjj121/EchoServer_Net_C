#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")


int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);


	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(SOCKADDR_IN));
	ServerSockAddr.sin_family = AF_INET;
	ServerSockAddr.sin_addr.s_addr = INADDR_ANY;
	ServerSockAddr.sin_port = htons(50501);
	bind(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(SOCKADDR_IN));

	listen(ServerSocket, 0);

	while (1)
	{
		FILE* InputFP = fopen("test.jpg", "rb");

		SOCKADDR_IN ClientSocketAddr;
		memset(&ClientSocketAddr, 0, sizeof(SOCKADDR_IN));
		int ClientSockAddrLength = sizeof(SOCKADDR_IN);

		SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientSocketAddr, &ClientSockAddrLength);
		printf("%s connected\n", inet_ntoa(ClientSocketAddr.sin_addr));
		printf("file send started.\n");
		char Buffer[4096] = { 0, };
		while (!feof(InputFP))
		{
			size_t ReadSize = fread(Buffer, sizeof(char), sizeof(Buffer), InputFP);
			send(ClientSocket, Buffer, ReadSize, 0);
		}
		printf("file send completed.\n");

		fclose(InputFP);
		closesocket(ClientSocket);
	}
	closesocket(ServerSocket);

	WSACleanup();

	//클라이언트
	//FILE* OutputFP = fopen("test2.txt", "wb");
	//size_t WriteSize = fwrite(Buffer, sizeof(char), ReadSize, OutputFP);
	//fclose(OutputFP);
 	return 0;
}