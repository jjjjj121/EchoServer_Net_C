#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#include <fstream>

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



	//int sendBytes; //파일을 읽어와서 사이즈를저장할변수
	//long file_size; //파일전체사이즈
	//char buf[256]; //데이터저장버퍼
	//FILE* fp;

	//fp = fopen("test.jpg", "rb"); //바이너리파일 읽기형식으로 열기 
	//fseek(fp, 0, SEEK_END); //끝으로가서 
	//file_size = ftell(fp); //사이즈재고 
	//fseek(fp, 0, SEEK_SET); //처음으로 다시와서

	//snprintf(buf, sizeof(buf), "%d", file_size); //사이즈값을 buf에다가넣기

	//send(ServerSocket, buf, sizeof(buf), 0); //파일전체 사이즈값전송

	//while ((sendBytes = fread(buf, sizeof(char), sizeof(buf), fp)) > 0) send(ServerSocket, buf, sendBytes, 0);
	////파일이끝날때까지 읽고 보내고를 반복
	//fclose(fp); //파일닫기



	int totalNum; //전체다운받은횟수
	int BufferNum = 0; //현재다운받은횟수
	int readBytes; //다운받은데이터의크기
	long file_size; //전체파일사이즈
	char buf[256]; //데이터를저장할 버퍼

	FILE* fp;
	fp = fopen("Recvfile.jpg", "wb"); //바이너리파일 쓰기형식으로 열기

	recv(ServerSocket, buf, 256, 0); //파일사이즈받기 
	file_size = atol(buf); //char->long변환

	//전체사이즈횟수 = 파일전체사이즈 % (1+받고있는데이터)
	totalNum = file_size / 256 + 1;

	while (BufferNum != totalNum)
	{ //만약 전체사이즈횟수와 다운받은횟수가같다면 루프나가기
		readBytes = recv(ServerSocket, buf, 256, 0);
		//데이터와 데이터의크기 받기 
		BufferNum++; //1씩더하기
		fwrite(buf, sizeof(char), readBytes, fp);
		//데이터와 데이터의크기만큼 파일쓰기 
	}
	fclose(fp); //파일닫기






	//size_t fsize, nsize = 0;
	//size_t fsize2;
	//

	////전송할 파일 오픈
	//FILE* MyFile = fopen("test.jpg", "rb");

	///* 파일 크기 계산 */
 //// move file pointer to end
	//fseek(MyFile, 0, SEEK_END);
	//// calculate file size
	//fsize = ftell(MyFile);
	//// move file pointer to first
	//fseek(MyFile, 0, SEEK_SET);

	//char Buffer[1024] = {};

	//while (nsize!= fsize)
	//{

	//
	//	int fpsize = fread(Buffer, 1, 256, MyFile);

	//	nsize += fsize;

	//	send(ServerSocket, Buffer, fpsize, 0);

	//	cout << "send" << endl;

	//}

	//fclose(MyFile);
	//closesocket(ServerSocket);



	WSACleanup();
}