#include <stdio.h>
#include <windows.h>
#define SIZE 18
#define MAX_STACK 100

typedef struct
{
	int x, y, color;
}move;
move stack[MAX_STACK];
int top = -1;

int board[SIZE][SIZE];
int boardstar[SIZE][SIZE];

int tern;

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

int maxh;
int maxrdb, maxrdw;
int maxrub, maxruw;

void printboard();
void boardbass();
void countall();
void countline(int c, int stx, int sty, int dx, int dy, int stone, int result[SIZE]);
void linelink();
void maxstar();
void save_board(const char* filename);
void load_board(const char* filename);
void push(int x, int y, int color);
void reset_board();


int main()
{
	int x = 0, y = 0;
	char input[20] = "\0";

	boardbass();
	while (1)
	{
		system("cls");
		reset_board();
		countall();
		linelink();
		maxstar();
		printboard();

		if(strcmp(input, "c") == 0)
		{
			printf("좌표 입력: ");
			int result = scanf_s("%d %d", &x, &y);

			if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && result == 2)
			{
				if (board[x][y] == 0)
				{
					board[x][y] = (tern == 0) ? 1 : 2;
					push(x, y, board[x][y]);
					tern = 1 - tern;
					strcpy_s(input, 20, "\0");
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
		else if (strcmp(input, "u") == 0)
		{
			if (top != -1)
			{
				move last = stack[top];
				board[last.x][last.y] = 0;
				top--;
				tern = 1 - tern;
			}
			else
			{
				printf("되돌릴 수 없습니다!\n");
				Sleep(500);
			}
			strcpy_s(input, 20, "\0");
		}
		else if (strcmp(input, "r") == 0)
		{
			if (stack[top + 1].color != 0)
			{
				board[stack[top + 1].x][stack[top + 1].y] = stack[top + 1].color;
				top++;
				tern = 1 - tern;
			}
			else
			{
				printf("되돌릴 수 없습니다!\n");
				Sleep(500);
			}
			strcpy_s(input, 20, "\0");
		}
		else if (strcmp(input, "save") == 0)
		{
			save_board("save_data.txt");
			Sleep(500);
			strcpy_s(input, 20, "\0");
		}
		else if (strcmp(input, "load") == 0)
		{
			load_board("save_data.txt");
			Sleep(500);
			strcpy_s(input, 20, "\0");
		}
		else if (strcmp(input, "\0") == 0)
		{
			printf("명령어 입력: ");
			scanf_s("%s", input, 20);
			while (getchar() != '\n');
		}
		else
		{
			printf("명령어 오류!\n");
			Sleep(500);
			strcpy_s(input, 20, "\0");
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
		printf("흑 돌의 턴입니다!\n");
	}
	else
	{
		printf("백 돌의 턴입니다!\n");
	}
	printf("대각 | 흑 | 백\n우하 | %2d | %2d\n우상 | %2d | %2d\n", maxrdb, maxrdw, maxrub, maxruw);
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
		if (hblack[i] > maxh)
		{
			maxh = hblack[i];
		}
		if (hwhite[i] > maxh)
		{
			maxh = hwhite[i];
		}
	}
	//세로
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
		if (rdblackx[i] > maxrdb)
		{
			maxrdb = rdblackx[i];
		}
		if (rdwhitex[i] > maxrdw)
		{
			maxrdw = rdwhitex[i];
		}
	}
	//대각 우하y
	for (int i = 0; i < SIZE; i++)
	{
		countline(i, 0, i, 1, 1, 1, rdblacky);
		countline(i, 0, i, 1, 1, 2, rdwhitey);
		if (rdblacky[i] > maxrdb)
		{
			maxrdb = rdblacky[i];
		}
		if (rdwhitey[i] > maxrdw)
		{
			maxrdw = rdwhitey[i];
		}
	}

	//대각 우상x
	for (int i = 0; i < SIZE; i++)
	{
		countline(i, i, SIZE - 1, 1, -1, 1, rublackx);
		countline(i, i, SIZE - 1, 1, -1, 2, ruwhitex);
		if (rublackx[i] > maxrub)
		{
			maxrub = rublackx[i];
		}
		if (ruwhitex[i] > maxruw)
		{
			maxruw = ruwhitex[i];
		}
	}
	//대각 우하y
	for (int i = 0; i < SIZE; i++)
	{
		countline(i, 0, i, 1, -1, 1, rublacky);
		countline(i, 0, i, 1, -1, 2, ruwhitey);
		if (rublacky[i] > maxrub)
		{
			maxrub = rublacky[i];
		}
		if (ruwhitey[i] > maxruw)
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

			if (board[x][y] == 1)
			{
				while (x < 17 && board[x + 1][y] == 1)
				{
					cb++;
					x++;
				}
				if (cb == maxh)
				{
					for (int v = 0; v < cb; v++)
					{
						int nx = i + 1 * v;
						boardstar[nx][y] = 1;
					}
				}
				x = i;
			}
			if (board[x][y] == 2)
			{
				while (x < 17 && board[x + 1][y] == 2)
				{
					cw++;
					x++;
				}
				if (cw == maxh)
				{
					for (int v = 0; v < cw; v++)
					{
						int nx = i + 1 * v;
						boardstar[nx][y] = 1;
					}
				}
				x = i;
			}
		}
	}
}

void save_board(const char* filename)
{
	FILE* fp = fopen(filename, "w");

	if (fp == NULL)
	{
		printf("파일 저장 오류!\n");
		return;
	}

	fprintf(fp, "%d\n", tern);

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			fprintf(fp, "%d ", board[i][j]);
		}
		fprintf(fp, "\n");
	}

	for (int i = 0; i < MAX_STACK; i++)
	{
		fprintf(fp, "%d ", stack[i].x);
		fprintf(fp, "%d ", stack[i].y);
		fprintf(fp, "%d ", stack[i].color);
		fprintf(fp, "\n");
	}

	fprintf(fp, "%d\n", top);

	fclose(fp);
	printf("파일 저장 완료!\n");
}

void load_board(const char* filename)
{
	FILE* fp = fopen(filename, "r");

	if (fp == NULL)
	{
		printf("파일 로드 오류!\n");
		return;
	}

	fscanf_s(fp, "%d", &tern);

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			fscanf_s(fp, "%d ", &board[i][j]);
		}
	}

	for (int i = 0; i < MAX_STACK; i++)
	{
		fscanf_s(fp, "%d ", &stack[i].x);
		fscanf_s(fp, "%d ", &stack[i].y);
		fscanf_s(fp, "%d ", &stack[i].color);
	}

	fscanf_s(fp, "%d", &top);

	fclose(fp);
	printf("파일 로드 완료!\n");
}

void push(int x, int y, int color)
{
	if (top < MAX_STACK - 1)
	{
		top++;
		stack[top].x = x;
		stack[top].y = y;
		stack[top].color = color;

	}
}

void reset_board()
{
	for (int i = 0; i < SIZE; i++)
	{
		hblack[i] = 0;
		hablack[i] = 0;
		hwhite[i] = 0;
		hawhite[i] = 0;

		rublackx[i] = 0;
		rdblackx[i] = 0;
		ruwhitex[i] = 0;
		rdwhitex[i] = 0;

		for (int j = 0; j < SIZE; j++)
		{
			vblack[j] = 0;
			vablack[j] = 0;
			vwhite[j] = 0;
			vawhite[j] = 0;

			rublacky[j] = 0;
			rdblacky[j] = 0;
			ruwhitey[j] = 0;
			rdwhitey[j] = 0;
		}
	}

	maxh = 0;
	maxrdb = 0;
	maxrub = 0;
	maxrdw = 0;
	maxruw = 0;
}