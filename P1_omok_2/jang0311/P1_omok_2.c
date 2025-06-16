#include <stdio.h>
#include <windows.h>
#include <wchar.h>
#include <locale.h>
#include <fcntl.h>

wchar_t omok[19][19];  // wchar_t 배열

void print()
{
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            wprintf(L"%lc ", omok[i][j]);  // %lc 사용
        }
        wprintf(L"\n");
    }
}

int main()
{
    int coor[2];
    int val1 = 0;
    int black = 0;
    int white = 0;

    _setmode(_fileno(stdout), _O_U16TEXT);  // Windows에서 유니코드 출력 모드 설정

    // 19x19 보드 초기화
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            omok[i][j] = L'+';
        }
    }

    while (1)
    {
        system("cls");
        print();
        wprintf(L"흑: %d\t\t\t\t백: %d\n", black, white);
        wprintf(L"좌표 입력: ");
        scanf_s("%d%d", &coor[0], &coor[1]);

        if (omok[coor[0]][coor[1]] == L'●' || omok[coor[0]][coor[1]] == L'○')  // L'' 사용
        {
            wprintf(L"\n이미 돌이 놓여 있습니다.");
            Sleep(1500);
        }
        else
        {
            if (val1 == 0) {
                omok[coor[0]][coor[1]] = L'●';
                val1 = 1;
                black++;
            }
            else
            {
                omok[coor[0]][coor[1]] = L'○';
                val1 = 0;
                white++;
            }
        }
    }
}
