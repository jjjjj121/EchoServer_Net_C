#define _CRT_SECURE_NO_WARNINGS


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


	SOCKADDR_IN ClientADDR;
	int ClientAddrLen = sizeof(ClientADDR);
	SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientADDR, &ClientAddrLen);

	if (ClientSocket == SOCKET_ERROR)
	{
		cout << "accept failed." << endl;
		exit(-1);
	}



	//int totalNum; //��ü�ٿ����Ƚ��
	//int BufferNum = 0; //����ٿ����Ƚ��
	//int readBytes; //�ٿ������������ũ��
	//long file_size; //��ü���ϻ�����
	//char buf[256]; //�����͸������� ����

	//FILE* fp;
	//fp = fopen("Recvfile.jpg", "wb"); //���̳ʸ����� ������������ ����

	//recv(ClientSocket, buf, 256, 0); //���ϻ�����ޱ� 
	//file_size = atol(buf); //char->long��ȯ

	////��ü������Ƚ�� = ������ü������ % (1+�ް��ִµ�����)
	//totalNum = file_size / 256 + 1;
	//
	//while (BufferNum != totalNum) 
	//{ //���� ��ü������Ƚ���� �ٿ����Ƚ�������ٸ� ����������
	//	readBytes = recv(ClientSocket, buf, 256, 0);
	//	//�����Ϳ� ��������ũ�� �ޱ� 
	//	BufferNum++; //1�����ϱ�
	//	fwrite(buf, sizeof(char), readBytes, fp);
	//	//�����Ϳ� ��������ũ�⸸ŭ ���Ͼ��� 
	//}
	//fclose(fp); //���ϴݱ�


	int sendBytes; //������ �о�ͼ� ����������Һ���
	long file_size; //������ü������
	char buf[256]; //�������������
	FILE* fp;

	fp = fopen("test.jpg", "rb"); //���̳ʸ����� �б��������� ���� 
	fseek(fp, 0, SEEK_END); //�����ΰ��� 
	file_size = ftell(fp); //��������� 
	fseek(fp, 0, SEEK_SET); //ó������ �ٽÿͼ�

	snprintf(buf, sizeof(buf), "%d", file_size); //������� buf���ٰ��ֱ�

	send(ClientSocket, buf, sizeof(buf), 0); //������ü ���������

	while ((sendBytes = fread(buf, sizeof(char), sizeof(buf), fp)) > 0) send(ClientSocket, buf, sendBytes, 0);
	//�����̳��������� �а� ������ �ݺ�
	fclose(fp); //���ϴݱ�



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