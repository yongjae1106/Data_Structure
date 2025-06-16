#include <stdio.h>
#include <string.h>
#define NAME_MAX 30
#define POSI_MAX 30
#define CH_MAX 30

struct champions
{
	char name[NAME_MAX];
	char posi[POSI_MAX];
	int hp, mp, speed, range;
};

struct champions ch[CH_MAX];

int ch_c;

void countCh();
void inputCh();
void Search_R(char* name, int i, int found);
void Insert_R(int i);
void Delete_R(char* name, int i, int found);
void DeleteAll_R(char* posi, int i, int found);
void PrintAll_R(int i);
int MaxHp(int i, int maxhp);
void FindMaxHp_R(int i);
void SortByHp_R(int i);

int main()
{
	char input[100];
	char vname[NAME_MAX];
	char com[20];

	inputCh();

	while (1)
	{
		printf("명령어 입력: ");
		fgets(input, 100, stdin);
		input[strcspn(input, "\n")] = '\0';

		if (sscanf_s(input, "%s %[^\n]", com, 20, vname, NAME_MAX) >= 2)
		{
			if (strcmp(com, "Search_R") == 0)
			{
				Search_R(vname, 0, 0);
			}
			else if (strcmp(com, "Delete_R") == 0)
			{
				Delete_R(vname, 0, 0);
			}
			else if (strcmp(com, "DeleteAll_R") == 0)
			{
				DeleteAll_R(vname, 0, 0);
				PrintAll_R(0);
			}
		}
		else if (strcmp(input, "Insert_R") == 0)
		{
			Insert_R(0);
		}
		else if (strcmp(input, "PrintAll_R") == 0)
		{
			PrintAll_R(0);
		}
		else if (strcmp(input, "FindMaxHp_R") == 0)
		{
			FindMaxHp_R(0);
		}
		else if (strcmp(input, "SortByHp_R") == 0)
		{
			SortByHp_R(0);
			PrintAll_R(0);
		}
	}
}

void countCh()
{
	for (int i = CH_MAX; i >= 0; i--)
	{
		if (strcmp(ch[i].name, "\0") != 0)
		{
			ch_c = i + 1;
			return;
		}
	}
}

void inputCh()
{
	char input[200];
	char name[NAME_MAX];
	char posi[POSI_MAX];
	int hp = 0, mp = 0, speed = 0, range = 0, i = 0;

	while (1)
	{
		printf("textdata.txt 복사(입력 완료 시 엔터 후 'q'입력):\n");
		fgets(input, 200, stdin);
		input[strcspn(input, "\n")] = '\0';

		if (sscanf_s(input, "%[^\t] %d %d %d %d %s", name, NAME_MAX, &hp, &mp, &speed, &range, posi, POSI_MAX) >= 6)
		{
			strcpy_s(ch[i].name, NAME_MAX, name);
			strcpy_s(ch[i].posi, POSI_MAX, posi);

			ch[i].hp = hp;
			ch[i].mp = mp;
			ch[i].speed = speed;
			ch[i].range = range;

			i++;
		}
		else if (strcmp(input, "q") == 0)
		{
			countCh();
			printf("챔피언 추가 완료!\n");
			return;
		}
	}
}

void Search_R(char* name, int i, int found)
{
	if (i < ch_c)
	{
		if (strcmp(ch[i].name, name) == 0)
		{
			printf("챔피언이름: %s\thp: %d\tmp: %d\tspeed: %d\trange: %d\tposition: %s\n", ch[i].name, ch[i].hp, ch[i].mp, ch[i].speed, ch[i].range, ch[i].posi);
			found = 1;
		}
		Search_R(name, ++i, found);
	}
	else
	{
		if (found == 0)
		{
			printf("챔피언을 찾지 못했습니다!\n");
		}
		return;
	}
}

void Delete_R(char* name, int i, int found)
{
	if (i < ch_c)
	{
		if (strcmp(ch[i].name, name) == 0)
		{
			strcpy_s(ch[i].name, NAME_MAX, "\0");
			found = 1;
		}
		Delete_R(name, ++i, found);
	}
	else
	{
		if (found == 0)
		{
			printf("챔피언을 찾을 수 없습니다!\n");
		}
		else
		{
			printf("챔피언 삭제 완료!\n");
		}
		return;
	}
}

void DeleteAll_R(char* posi, int i, int found)
{
	if (i < ch_c)
	{
		if (strcmp(ch[i].posi, posi) == 0)
		{
			strcpy_s(ch[i].name, NAME_MAX, "\0");
			found = 1;
		}
		DeleteAll_R(posi, ++i, found);
	}
	else
	{
		if (found == 0)
		{
			printf("position을 찾을 수 없습니다!\n");
		}
		else
		{
			printf("챔피언 삭제 완료!\n");
		}
		return;
	}
}

void Insert_R(int i)
{
	char name[NAME_MAX];
	char posi[POSI_MAX];
	int hp = 0, mp = 0, speed = 0, range = 0;
	if (i < CH_MAX)
	{
		if (strcmp(ch[i].name, "\0") == 0)
		{
			while (1)
			{
				printf("챔피언이름: ");
				fgets(name, NAME_MAX, stdin);
				name[strcspn(name, "\n")] = '\0';

				if (strlen(name) >= 1)
				{
					strcpy_s(ch[i].name, NAME_MAX, name);
					break;
				}
				else
				{
					printf("입력오류! (한 자 이상 입력)\n");
				}
			}
			while (1)
			{
				printf("hp 입력: ");
				if (scanf_s("%d", &hp) != 1)
				{
					while (getchar() != '\n')
					printf("입력오류! (숫자입력)\n");
				}
				else
				{
					while (getchar() != '\n')
					ch[i].hp = hp;
					break;
				}
			}
			while (1)
			{
				printf("mp 입력: ");
				if (scanf_s("%d", &mp) != 1)
				{
					while (getchar() != '\n')
					printf("입력오류! (숫자입력)\n");
				}
				else
				{
					while (getchar() != '\n')
					ch[i].mp = mp;
					break;
				}
			}
			while (1)
			{
				printf("speed 입력: ");
				if (scanf_s("%d", &speed) != 1)
				{
					while (getchar() != '\n')
					printf("입력오류! (숫자입력)\n");
				}
				else
				{
					while (getchar() != '\n')
					ch[i].speed = speed;
					break;
				}
			}
			while (1)
			{
				printf("range 입력: ");
				if (scanf_s("%d", &range) != 1)
				{
					while (getchar() != '\n')
					printf("입력오류! (숫자입력)\n");
				}
				else
				{
					while (getchar() != '\n')
					ch[i].range = range;
					break;
				}
			}
			while (1)
			{
				printf("position 입력: ");
				fgets(posi, NAME_MAX, stdin);
				posi[strcspn(posi, "\n")] = '\0';

				if (strcmp(posi, "top") == 0 || strcmp(posi, "jungle") == 0 || strcmp(posi, "mid") == 0 || strcmp(posi, "bottom") == 0 || strcmp(posi, "support") == 0)
				{
					strcpy_s(ch[i].posi, POSI_MAX, posi);
					break;
				}
				else
				{
					printf("입력오류! (position 입력)\n");
				}
			}
			printf("챔피언 추가 완료!");
			countCh();
			return;
		}
		Insert_R(++i);
	}
}

void PrintAll_R(int i)
{
	if (i < ch_c)
	{
		if (strcmp(ch[i].name, "\0") != 0)
		{
			printf("챔피언이름: %s\thp: %d\tmp: %d\tspeed: %d\trange: %d\tposition: %s\n", ch[i].name, ch[i].hp, ch[i].mp, ch[i].speed, ch[i].range, ch[i].posi);
		}

		PrintAll_R(++i);
	}
	else
	{
		return;
	}
}
int MaxHp(int i, int maxhp)
{
	if (i < ch_c)
	{
		if (ch[i].hp > maxhp)
		{
			maxhp = ch[i].hp;
		}
		MaxHp(++i, maxhp);
	}
	else
	{
		return maxhp;
	}
}
void FindMaxHp_R(int i)
{
	int maxhp = MaxHp(0, 0);

	if (i < ch_c)
	{
		if (ch[i].hp == maxhp)
		{
			printf("챔피언이름: %s\thp: %d\tmp: %d\tspeed: %d\trange: %d\tposition: %s\n", ch[i].name, ch[i].hp, ch[i].mp, ch[i].speed, ch[i].range, ch[i].posi);
		}

		FindMaxHp_R(++i);
	}
	else
	{
		return;
	}
}
void SortByHp_R(int i)
{
	char tpname[NAME_MAX];
	char tpposi[POSI_MAX];
	int tphp = 0, tpmp = 0, tpspeed = 0, tprange = 0;
	if (i < ch_c)
	{
		for (int j = 0; j < ch_c - i; j++)
		{
			if (ch[j].hp < ch[j + 1].hp)
			{
				strcpy_s(tpname, NAME_MAX, ch[j].name);
				strcpy_s(tpposi, POSI_MAX, ch[j].posi);
				tphp = ch[j].hp;
				tpmp = ch[j].mp;
				tpspeed = ch[j].speed;
				tprange = ch[j].range;

				strcpy_s(ch[j].name, NAME_MAX, ch[j + 1].name);
				strcpy_s(ch[j + 1].name, NAME_MAX, tpname);
				strcpy_s(ch[j].posi, POSI_MAX, ch[j + 1].posi);
				strcpy_s(ch[j + 1].posi, POSI_MAX, tpposi);
				ch[j].hp = ch[j + 1].hp;
				ch[j + 1].hp = tphp;
				ch[j].mp = ch[j + 1].mp;
				ch[j + 1].mp = tpmp;
				ch[j].speed = ch[j + 1].speed;
				ch[j + 1].speed = tpspeed;
				ch[j].range = ch[j + 1].range;
				ch[j + 1].range = tprange;

			}
		}
		SortByHp_R(++i);
	}
	else
	{
		printf("정렬 완료!\n");
		return;
	}
}