#include <stdio.h>
#include <windows.h>
#define SIZE 18

int board[SIZE][SIZE];
int boardstar[SIZE][SIZE];

int hblack[SIZE];
int vblack[SIZE];
int hablack[SIZE];
int vablack[SIZE];

int hwhite[SIZE];
int vwhite[SIZE];
int hawhite[SIZE];
int vawhite[SIZE];

int rdblackx[SIZE];
int rdwhitex[SIZE];
int rublackx[SIZE];
int ruwhitex[SIZE];

int rdblacky[SIZE];
int rdwhitey[SIZE];
int rublacky[SIZE];
int ruwhitey[SIZE];

int maxhb, maxhw;
int maxrdb, maxrdw;
int maxrub, maxruw;

int tern;

void boardbass();
void printboard();
void countall();
void countline(int c, int stx, int sty, int dx, int dy, int stone, int result[SIZE]);
void linelink();
void maxstar();

int main()
{
	int x = 0, y = 0;

	boardbass();
	while (1)
	{
		system("cls");
		countall();
		linelink();
		maxstar();
		printboard();
		printf("좌표 입력: ");
		int result = scanf_s("%d %d", &x, &y);

		if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && result == 2)
		{
			if(board[x][y] == 0)
			{
				if (tern == 0)
				{
					board[x][y] = 1;
					tern = 1;
				}
				else if (tern == 1)
				{
					board[x][y] = 2;
					tern = 0;
				}
			}
			else
			{
				printf("이미 돌이 있습니다!\n");
				while (getchar() != '\n');
				Sleep(500);
			}
		}
		else
		{
			printf("좌표 오류!\n");
			while (getchar() != '\n');
			Sleep(500);
		}
	}
}

void boardbass()
{
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			board[x][y] = 0;
		}
	}
}
void printboard()
{
	printf("   0 1 2 3 4 5 6 7 8 91011121314151617\n");
	for (int y = 0; y < SIZE; y++)
	{
		printf("%2d ", y);
		for (int x = 0; x < SIZE; x++)
		{
			if (boardstar[x][y] == 1)
			{
				printf("$ ");
			}
			else if (boardstar[x][y] == 2)
			{
				printf("# ");
			}
			else if (board[x][y] == 1)
			{
				printf("B ");
			}
			else if (board[x][y] == 2)
			{
				printf("W ");
			}
			else if (board[x][y] == 0)
			{
				printf("+ ");
			}
		}
		printf(" B%2d  W%2d | aB%2d aW%2d", hblack[y], hwhite[y], hablack[y], hawhite[y]);
		printf("\n");
	}
	printf(" B");
	for (int i = 0; i < SIZE; i++)
	{
		printf("%2d", vblack[i]);
	}
	printf("\n");
	printf(" W");
	for (int i = 0; i < SIZE; i++)
	{
		printf("%2d", vwhite[i]);
	}
	printf("\n");

	printf("aB");
	for (int i = 0; i < SIZE; i++)
	{
		printf("%2d", vablack[i]);
	}
	printf("\n");
	printf("aW");
	for (int i = 0; i < SIZE; i++)
	{
		printf("%2d", vawhite[i]);
	}
	printf("\n");

	if (tern == 0)
	{
		printf("흑 돌 턴입니다!\n");
	}
	else if (tern == 1)
	{
		printf("백 돌 턴입니다!\n");
	}
	printf("대각 | 흑 | 백\n우하 | %2d | %2d\n우상 | %2d | %2d\n", maxrdb, maxrdw, maxrub, maxruw);
}
void countall()
{
	for (int y = 0; y < SIZE; y++)
	{
		int cb = 0;
		int cw = 0;
		for (int x = 0; x < SIZE; x++)
		{
			if (board[x][y] == 1)
			{
				cb++;
			}
			else if (board[x][y] == 2)
			{
				cw++;
			}
		}
		hablack[y] = cb;
		hawhite[y] = cw;
		cb = 0;
		cw = 0;
	}
	for (int x = 0; x < SIZE; x++)
	{
		int cb = 0;
		int cw = 0;
		for (int y = 0; y < SIZE; y++)
		{
			if (board[x][y] == 1)
			{
				cb++;
			}
			else if (board[x][y] == 2)
			{
				cw++;
			}
		}
		vablack[x] = cb;
		vawhite[x] = cw;
		cb = 0;
		cw = 0;
	}

}
void countline(int c, int stx, int sty, int dx, int dy, int stone, int result[SIZE])
{
	int x = stx;
	int y = sty;
	int count = 0;

	while (x >= 0 && x < SIZE && y >= 0 && y < SIZE)
	{
		if (board[x][y] == stone)
		{
			count++;
			if (count > result[c])
			{
				result[c] = count;
			}
		}
		else
		{
			count = 0;
		}

		x += dx;
		y += dy;
	}
}
void linelink()
{
	//가로
	for (int i = 0; i < SIZE; i++)
	{
		countline(i, 0, i, 1, 0, 1, hblack);
		countline(i, 0, i, 1, 0, 2, hwhite);
		if (maxhb < hblack[i])
		{
			maxhb = hblack[i];
		}
		else if (maxhw < hwhite[i])
		{
			maxhw = hwhite[i];
		}
	}
	//가로
	for (int i = 0; i < SIZE; i++)
	{
		countline(i, i, 0, 0, 1, 1, vblack);
		countline(i, i, 0, 0, 1, 2, vwhite);
	}


	//대각 우하x
	for (int i = 0; i < SIZE; i++)
	{
		countline(i, i, 0, 1, 1, 1, rdblackx);
		countline(i, i, 0, 1, 1, 2, rdwhitex);
		if (maxrdb < rdblackx[i])
		{
			maxrdb = rdblackx[i];
		}
		else if (maxrdw < rdwhitex[i])
		{
			maxrdw = rdwhitex[i];
		}
	}
	//대각 우하y
	for (int i = 0; i < SIZE; i++)
	{
		countline(i, 0, i, 1, 1, 1, rdblacky);
		countline(i, 0, i, 1, 1, 2, rdwhitey);
		if (maxrdb < rdblacky[i])
		{
			maxrdb = rdblacky[i];
		}
		else if (maxrdw < rdwhitey[i])
		{
			maxrdw = rdwhitey[i];
		}
	}

	//대각 우상x
	for (int i = 0; i < SIZE; i++)
	{
		countline(i, i, SIZE - 1, 1, -1, 1, rublackx);
		countline(i, i, SIZE - 1, 1, -1, 2, ruwhitex);
		if (maxrub < rublackx[i])
		{
			maxrub = rublackx[i];
		}
		else if (maxruw < ruwhitex[i])
		{
			maxruw = ruwhitex[i];
		}
	}
	//대각 우상y
	for (int i = 0; i < SIZE; i++)
	{
		countline(i, 0, i, 1, -1, 1, rublacky);
		countline(i, 0, i, 1, -1, 2, ruwhitey);
		if (maxrub < rublacky[i])
		{
			maxrub = rublacky[i];
		}
		else if (maxruw < ruwhitey[i])
		{
			maxruw = ruwhitey[i];
		}
	}
}
void maxstar()
{
	for (int y = 0; y < SIZE; y++)
	{
		for (int i = 0; i < SIZE; i++)
		{
			boardstar[i][y] = 0;
		}
	}
	for (int y = 0; y < SIZE; y++)
	{
		for (int i = 0; i < SIZE; i++)
		{
			int x = i;
			int cb = 1;
			int cw = 1;

			if(board[x][y] == 1)
			{
				while (x < 17 && board[x + 1][y] == 1)
				{
					cb++;
					x++;
				}
				if (cb == maxhb)
				{
					for (int v = 0; v < cb; v++)
					{
						int nx = i + 1 * v;
						boardstar[nx][y] = 1;
					}
				}
				x = i;
			}
			else if (board[x][y] == 2)
			{
				while (x < 17 && board[x + 1][y] == 2)
				{
					cw++;
					x++;
				}
				if (cw == maxhw)
				{
					for (int v = 0; v < cw; v++)
					{
						int nx = i + 1 * v;
						boardstar[nx][y] = 2;
					}
				}
				x = i;
			}

			if (board[16][y] != 1 && board[17][y] == 1 && maxhb == 1)
			{
				boardstar[17][y] = 1;
			}
			else if (board[16][y] != 2 && board[17][y] == 2 && maxhb == 1)
			{
				boardstar[17][y] = 2;
			}
		}
	}
}
