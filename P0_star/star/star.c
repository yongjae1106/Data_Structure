#include <stdio.h>
#include <windows.h>
#define _CRT_SECURITY_NO_WARNINGS

int main()
{
	int line;

	printf("출력할 줄 수 입력: ");
	scanf_s("%d", &line);

	for(int i = 1; i <= line; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			printf("%d", j);
			Sleep(1000);
		}
		printf("\n");
	}

	printStar();
	printStars(4);

	return 0;
}

int printStar()
{
	printf("*");
	printf("\n");

	return 0;
}

int printStars(int count)
{
	for (int i = 0; i < count; i++)
	{
		printf("*");
	}
	printf("\n");

	return count;
}