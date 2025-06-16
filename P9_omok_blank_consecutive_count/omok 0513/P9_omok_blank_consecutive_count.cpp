#include <stdio.h>
#include <windows.h>

#define SIZE 19
#define EMPTY 0
#define BLACK 1
#define WHITE 2

int board[SIZE][SIZE];
int directions[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} }; // 하, 우, 우하, 좌하
int tern;

typedef struct
{
    int x, y;
}Point;
Point maxp[SIZE * SIZE];
int maxcount;
int maxidx;

void checkmax()
{
    maxcount = 0;
    maxidx = 0;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == EMPTY) continue;

            int color = board[i][j];

            for (int d = 0; d < 4; d++)
            {
                int count = 1;
                int idx = 0;
                Point temp[SIZE];
                temp[idx++] = { i,j };

                for (int step = 1; step < 5; step++)
                {
                    int nx = i + directions[d][0] * step;
                    int ny = i + directions[d][1] * step;
                    if (nx < 0 || ny < 0 || nx >= SIZE || ny >= SIZE) break;
                    if (board[nx][ny] == color)
                    {
                        count++;
                        temp[idx++] = { nx,ny };
                    }
                }
                for (int step = 1; step < 5; step++)
                {
                    int nx = i - directions[d][0] * step;
                    int ny = i - directions[d][1] * step;
                    if (nx < 0 || ny < 0 || nx >= SIZE || ny >= SIZE) break;
                    if (board[nx][ny] == color)
                    {
                        count++;
                        temp[idx++] = { nx,ny };
                    }
                }

                if (maxcount < count)
                {
                    maxcount = count;
                    maxidx = idx;
                    for (int k = 0; k < idx; k++)
                    {
                        maxp[k] = temp[k];
                    }
                }
            }
        }
    }
    printf("\n최대 돌 개수: %d\n좌표: \n", maxcount);
    for (int i = 0; i < maxidx; i++)
    {
        printf("%d %d\n", maxp[i].x, maxp[i].y);
    }
}

// 보드 출력
void printBoard()
{
    printf("  ");
    for (int i = 0; i < SIZE; i++) printf("%2d", i);
    printf("\n");

    for (int i = 0; i < SIZE; i++)
    {
        printf("%2d", i);
        for (int j = 0; j < SIZE; j++)
        {
            char symbol = '+';
            if (board[i][j] == BLACK) symbol = 'B';
            else if (board[i][j] == WHITE) symbol = 'W';
            printf(" %c", symbol);
        }
        printf("\n");
    }
}

// 한 방향으로 연속된 돌 개수 세기
int countConsecutive(int x, int y, int dx, int dy, int color)
{
    int count = 0;
    for (int i = 0; i < 5; i++)
    {
        int nx = x + dx * i;
        int ny = y + dy * i;
        if (nx < 0 || ny < 0 || nx >= SIZE || ny >= SIZE) break;
        if (board[nx][ny] == color) count++;
        else break;
    }
    return count;
}

void checkdefence()
{
    const char* colorch[3] = { "EMPTY","BLACK","WHITE" };
    
    for (int color = BLACK; color <= WHITE; color++)
    {
        printf("\n%s돌 공격 위치\n", colorch[color]);

        int found = 0;

        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if (board[i][j] != EMPTY) continue;
                int max = 0;
                board[i][j] = color;

                for (int d = 0; d < 4; d++)
                {
                    int cnt = countConsecutive(i, j, directions[d][0], directions[d][1], color) + countConsecutive(i, j, -directions[d][0], -directions[d][1], color) - 1;
                    if (max < cnt)
                    {
                        max = cnt;
                    }
                }
                
                if (max >= 3)
                {
                    printf("%d돌 %d %d\n", max, i, j);
                    found = 1;
                }

                board[i][j] = EMPTY;
            }
        }
        if (!found)
        {
            printf("없음\n");
        }
    }
}

int main()
{
    char coor[2] = { 0 };

    while (1)
    {
        system("cls");
        printBoard();
        checkmax();
        checkdefence();
        printf("\n좌표 입력: ");
        scanf_s("%d %d", &coor[0], &coor[1]);

        if (board[coor[0]][coor[1]] == 0)
        {
            board[coor[0]][coor[1]] = (tern == 0) ? 1 : 2;
            tern = 1 - tern;
        }
    }

    return 0;
}
