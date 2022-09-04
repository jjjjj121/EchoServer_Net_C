#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")
using namespace std;

int main()
{
	//Windsow
	//winsock 라이브러리 초기화
	WSAData wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		cout << "WSAStartup Failed." << endl;
		exit(-1);
	}

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0); //TCP/IP 쓸 소켓 뚫어줘

	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "Create socket failed." << endl;
		exit(-1);
	}

	SOCKADDR_IN ServerSockADDR;

	memset(&ServerSockADDR, 0, sizeof(SOCKADDR_IN)); // sin.zero[]에 0으로  다 채울거애 addr_in크기만큼

	ServerSockADDR.sin_addr.s_addr = htonl(INADDR_ANY); //랜카드가 1개니까  아무거나 써라라는 뜻 랜카드가 여러개면 any를 쓰지 못한다.
	ServerSockADDR.sin_port = htons(20000);
	ServerSockADDR.sin_family = PF_INET; // ipv4, 6 쓰겠다.

	//bind(ServerSocket, (SOCKADDR*)&ServerSockADDR, 0); //크기가 안맞기 때문에 (SOCKADDR*)로 형변환 해준다. 실제 랜카드에 가상의 구멍(소켓)을 연결한 것

	if (bind(ServerSocket, (SOCKADDR*)&ServerSockADDR, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		cout << "bind failed." << endl;
		exit(-1); //-1은 비정상 종료 exit(return)과 같아.
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