#include <stdio.h>
#include <windows.h>
#include <wchar.h>
#include <locale.h>
#include <fcntl.h>

wchar_t omok[19][19];  // wchar_t �迭

void print()
{
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            wprintf(L"%lc ", omok[i][j]);  // %lc ���
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

    _setmode(_fileno(stdout), _O_U16TEXT);  // Windows���� �����ڵ� ��� ��� ����

    // 19x19 ���� �ʱ�ȭ
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
        wprintf(L"��: %d\t\t\t\t��: %d\n", black, white);
        wprintf(L"��ǥ �Է�: ");
        scanf_s("%d%d", &coor[0], &coor[1]);

        if (omok[coor[0]][coor[1]] == L'��' || omok[coor[0]][coor[1]] == L'��')  // L'' ���
        {
            wprintf(L"\n�̹� ���� ���� �ֽ��ϴ�.");
            Sleep(1500);
        }
        else
        {
            if (val1 == 0) {
                omok[coor[0]][coor[1]] = L'��';
                val1 = 1;
                black++;
            }
            else
            {
                omok[coor[0]][coor[1]] = L'��';
                val1 = 0;
                white++;
            }
        }
    }
}
