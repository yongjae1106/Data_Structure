#include <stdio.h>
#include <windows.h>

char board[19][19];

void board_stl()
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			board[i][j] = '+';
		}
	}
}

void print()
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	int coor[2];
	int color_dol = 0;
	int white = 0, black = 0;

	board_stl();

	while (1)
	{
		system("cls");
		print();

		printf("Èæ: %d\t\t\t\t¹é: %d\n", black, white);

		printf("ÁÂÇ¥ ÀÔ·Â: ");
		scanf_s("%d%d", &coor[0], &coor[1]);

		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 19; j++)
			{
				if (i == coor[0] && j == coor[1])
				{
					if (color_dol == 0)
					{
						board[i][j] = 'B';
						color_dol = 1;
						black++;
					}
					else
					{
						board[i][j] = 'W';
						color_dol = 0;
						white++;
					}
				}
			}
		}
	}
}