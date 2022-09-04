#include <stdio.h>


int main()
{
	//읽기 파일 변수 생성
	FILE* TestFile = fopen("test.jpg","rb");

	//새로 저장할 파일 변수 생성
	FILE* BTestFile = fopen("test2.jpg", "wb");

	//buffer
	char Buffer[1024] = {};


	while (!feof(TestFile))
	{
		size_t ReadSize = fread(Buffer, sizeof(char), sizeof(Buffer), TestFile);
		size_t WriteSize = fwrite(Buffer, sizeof(char), ReadSize, BTestFile);
	}

	fclose(TestFile);
	fclose(BTestFile);


	return 0;
}