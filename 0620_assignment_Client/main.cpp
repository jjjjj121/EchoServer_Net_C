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
	ServerSockADDR.sin_addr.s_addr = inet_addr("127.0.0.1"); //�ڱ��ڽ��� ��Ÿ���� ip
	ServerSockADDR.sin_port = htons(20000);

	if (connect(ServerSocket, (SOCKADDR*)&ServerSockADDR, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		cout << "Connect Failed" << endl;
		exit(-1);
	}



	//int sendBytes; //������ �о�ͼ� ����������Һ���
	//long file_size; //������ü������
	//char buf[256]; //�������������
	//FILE* fp;

	//fp = fopen("test.jpg", "rb"); //���̳ʸ����� �б��������� ���� 
	//fseek(fp, 0, SEEK_END); //�����ΰ��� 
	//file_size = ftell(fp); //��������� 
	//fseek(fp, 0, SEEK_SET); //ó������ �ٽÿͼ�

	//snprintf(buf, sizeof(buf), "%d", file_size); //������� buf���ٰ��ֱ�

	//send(ServerSocket, buf, sizeof(buf), 0); //������ü ���������

	//while ((sendBytes = fread(buf, sizeof(char), sizeof(buf), fp)) > 0) send(ServerSocket, buf, sendBytes, 0);
	////�����̳��������� �а� ������ �ݺ�
	//fclose(fp); //���ϴݱ�



	int totalNum; //��ü�ٿ����Ƚ��
	int BufferNum = 0; //����ٿ����Ƚ��
	int readBytes; //�ٿ������������ũ��
	long file_size; //��ü���ϻ�����
	char buf[256]; //�����͸������� ����

	FILE* fp;
	fp = fopen("Recvfile.jpg", "wb"); //���̳ʸ����� ������������ ����

	recv(ServerSocket, buf, 256, 0); //���ϻ�����ޱ� 
	file_size = atol(buf); //char->long��ȯ

	//��ü������Ƚ�� = ������ü������ % (1+�ް��ִµ�����)
	totalNum = file_size / 256 + 1;

	while (BufferNum != totalNum)
	{ //���� ��ü������Ƚ���� �ٿ����Ƚ�������ٸ� ����������
		readBytes = recv(ServerSocket, buf, 256, 0);
		//�����Ϳ� ��������ũ�� �ޱ� 
		BufferNum++; //1�����ϱ�
		fwrite(buf, sizeof(char), readBytes, fp);
		//�����Ϳ� ��������ũ�⸸ŭ ���Ͼ��� 
	}
	fclose(fp); //���ϴݱ�






	//size_t fsize, nsize = 0;
	//size_t fsize2;
	//

	////������ ���� ����
	//FILE* MyFile = fopen("test.jpg", "rb");

	///* ���� ũ�� ��� */
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