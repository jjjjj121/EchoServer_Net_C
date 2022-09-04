#define _CRT_SECURE_NO_WARNINGS


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


	SOCKADDR_IN ClientADDR;
	int ClientAddrLen = sizeof(ClientADDR);
	SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientADDR, &ClientAddrLen);

	if (ClientSocket == SOCKET_ERROR)
	{
		cout << "accept failed." << endl;
		exit(-1);
	}



	//int totalNum; //전체다운받은횟수
	//int BufferNum = 0; //현재다운받은횟수
	//int readBytes; //다운받은데이터의크기
	//long file_size; //전체파일사이즈
	//char buf[256]; //데이터를저장할 버퍼

	//FILE* fp;
	//fp = fopen("Recvfile.jpg", "wb"); //바이너리파일 쓰기형식으로 열기

	//recv(ClientSocket, buf, 256, 0); //파일사이즈받기 
	//file_size = atol(buf); //char->long변환

	////전체사이즈횟수 = 파일전체사이즈 % (1+받고있는데이터)
	//totalNum = file_size / 256 + 1;
	//
	//while (BufferNum != totalNum) 
	//{ //만약 전체사이즈횟수와 다운받은횟수가같다면 루프나가기
	//	readBytes = recv(ClientSocket, buf, 256, 0);
	//	//데이터와 데이터의크기 받기 
	//	BufferNum++; //1씩더하기
	//	fwrite(buf, sizeof(char), readBytes, fp);
	//	//데이터와 데이터의크기만큼 파일쓰기 
	//}
	//fclose(fp); //파일닫기


	int sendBytes; //파일을 읽어와서 사이즈를저장할변수
	long file_size; //파일전체사이즈
	char buf[256]; //데이터저장버퍼
	FILE* fp;

	fp = fopen("test.jpg", "rb"); //바이너리파일 읽기형식으로 열기 
	fseek(fp, 0, SEEK_END); //끝으로가서 
	file_size = ftell(fp); //사이즈재고 
	fseek(fp, 0, SEEK_SET); //처음으로 다시와서

	snprintf(buf, sizeof(buf), "%d", file_size); //사이즈값을 buf에다가넣기

	send(ClientSocket, buf, sizeof(buf), 0); //파일전체 사이즈값전송

	while ((sendBytes = fread(buf, sizeof(char), sizeof(buf), fp)) > 0) send(ClientSocket, buf, sendBytes, 0);
	//파일이끝날때까지 읽고 보내고를 반복
	fclose(fp); //파일닫기



	//FILE* MyFile = nullptr;

	//MyFile = fopen("RecvFile.jpg", "wb");
	//char Buffer[1024] = { 0, };
	//int RevLenght = 256;


	//while (RevLenght != 0)
	//{

	//	RevLenght = recv(ClientSocket, Buffer, sizeof(Buffer), 0);

	//	fwrite(Buffer, sizeof(char), RevLenght, MyFile);

	//}



	//fclose(MyFile);


	closesocket(ClientSocket);
	closesocket(ServerSocket);

	cout << ServerSocket << endl;
	//Windows Only
	WSACleanup();

	return 0;
}