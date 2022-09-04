#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")
using namespace std;

int main()
{
	//Windsow
	//winsock ���̺귯�� �ʱ�ȭ
	WSAData wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "WSAStartup Failed." << endl;
		exit(-1);
	}

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0); //TCP/IP �� ���� �վ���

	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "Create socket failed." << endl;
		exit(-1);
	}

	SOCKADDR_IN ServerSockADDR;

	memset(&ServerSockADDR, 0, sizeof(SOCKADDR_IN)); // sin.zero[]�� 0����  �� ä��ž� addr_inũ�⸸ŭ

	ServerSockADDR.sin_addr.s_addr = htonl(INADDR_ANY); //��ī�尡 1���ϱ�  �ƹ��ų� ����� �� ��ī�尡 �������� any�� ���� ���Ѵ�.
	ServerSockADDR.sin_port = htons(20000);
	ServerSockADDR.sin_family = PF_INET; // ipv4, 6 ���ڴ�.

	//bind(ServerSocket, (SOCKADDR*)&ServerSockADDR, 0); //ũ�Ⱑ �ȸ±� ������ (SOCKADDR*)�� ����ȯ ���ش�. ���� ��ī�忡 ������ ����(����)�� ������ ��

	if (bind(ServerSocket, (SOCKADDR*)&ServerSockADDR, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		cout << "bind failed." << endl;
		exit(-1); //-1�� ������ ���� exit(return)�� ����.
	}

	if (listen(ServerSocket, 0) == SOCKET_ERROR)
	{
		cout << "listen failed." << endl;
		exit(-1);
	}

	while (1)
	{
		SOCKADDR_IN ClientADDR;
		int ClientAddrLen = sizeof(ClientADDR);
		SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientADDR, &ClientAddrLen);

		if (ClientSocket == SOCKET_ERROR)
		{
			cout << "accept failed." << endl;
			exit(-1);
		}

		char Message[1024] = { 0, };
		int RevLenght = recv(ClientSocket, Message, sizeof(Message), 0);
		int SendLength = send(ClientSocket, Message, strlen(Message), 0);



		closesocket(ClientSocket);
	}

	closesocket(ServerSocket);

	cout << ServerSocket << endl;
	//Windows Only
	WSACleanup();

	return 0;
}