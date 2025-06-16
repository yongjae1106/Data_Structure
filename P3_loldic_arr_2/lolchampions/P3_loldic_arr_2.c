#include <stdio.h>
#include <string.h>
#define MAX_CHAMPIONS 300
#define MAX_NAMELEN 20

struct Champions
{
	char name[MAX_NAMELEN];
	char position[10];
	int hp;
	int mp;
	int speed;
	int range;
};

struct Champions ch[MAX_CHAMPIONS];

size_t champion_count = 0;

// testdata.txt 의 값 입력 함수
void champion_default_scan()
{
	char input[200];
	char name[MAX_NAMELEN];
	char position[10];
	int hp = 0, mp = 0, speed = 0, range = 0;

	while (1)
	{
		printf("testdata를 복사하여 입력 (입력완료 시 엔터 후 'q' 입력): \n");
		fgets(input, sizeof(input), stdin);

		input[strcspn(input, "\n")] = '\0';

		if(sscanf_s(input, "%[^\t] %d %d %d %d %s", name, sizeof(name), &hp, &mp, &speed, &range, position, sizeof(position)) >= 6)
		{
			strcpy_s(ch[champion_count].name, MAX_NAMELEN, name);
			strcpy_s(ch[champion_count].position, 10, position);
			ch[champion_count].hp = hp;
			ch[champion_count].mp = mp;
			ch[champion_count].speed = speed;
			ch[champion_count].range = range;
			champion_count++;
		}
		else
		{
			printf("\n입력 오류!\n");
		}
		if (strcmp(input, "q") == 0)
		{
			printf("\n입력 완료!\n");
			break;
		}
	}
}

void count_ch()
{
	for (int i = MAX_CHAMPIONS - 1; i >= 0; i--)
	{
		if (strcmp(ch[i].name, "") != 0)
		{
			champion_count = i + 1;
			return;
		}
	}
}

// 챔피언 검색 함수
void Search_Ch(char* name, int i, int found)
{
	if(i != champion_count)
	{
		if (strcmp(ch[i].name, name) == 0)
		{
			if (strlen(ch[i].name) < 4)
			{
				printf("챔피언이름: %s\t\t", &ch[i].name);
			}
			else
			{
				printf("챔피언이름: %s\t", &ch[i].name);
			}
			printf("hp: %d\tmp: %d\tspeed: %d\trange: %d\tposition: %s\n", ch[i].hp, ch[i].mp, ch[i].speed, ch[i].range, ch[i].position);	

			found = 1;
		}
		Search_Ch(name, ++i, found);
	}
	else
	{
		if (found == 0)
		{
			printf("\n%s를 찾을 수 없습니다\n", name);
			return;
		}
	}

}

// 챔피언 추가 함수
void Insert_Ch(int i)
{
	char name[MAX_NAMELEN], position[10];
	int hp = 0, mp = 0, speed = 0, range = 0;
	if (strcmp(ch[i].name, "") == 0)
	{
		while (1)
		{
			printf("\n챔피언이름 입력: ");
			fgets(name, sizeof(name), stdin);

			name[strcspn(name, "\n")] = '\0';

			if (strlen(name) >= 1)
			{
				strcpy_s(ch[i].name, 20, name);
				break;
			}
			else
			{
				printf("챔피언이름은 1글자 이상이어야 합니다!");
			}
		}

		while (1)
		{
			printf("%s의 hp 입력: ", name);

			if (scanf_s("%d", &hp) != 1)
			{
				printf("입력 오류!\n");
				while (getchar() != '\n');
			}
			else
			{
				ch[i].hp = hp;
				break;
			}
		}

		while (1)
		{
			printf("%s의 mp 입력: ", name);

			if (scanf_s("%d", &mp) != 1)
			{
				printf("입력 오류!\n");
				while (getchar() != '\n');
			}
			else
			{
				ch[i].mp = mp;
				break;
			}
		}

		while (1)
		{
			printf("%s의 speed 입력: ", name);

			if (scanf_s("%d", &speed) != 1)
			{
				printf("입력 오류!\n");
				while (getchar() != '\n');
			}
			else
			{
				ch[i].speed = speed;
				break;
			}
		}

		while (1)
		{
			printf("%s의 range 입력: ", name);

			if (scanf_s("%d", &range) != 1)
			{
				printf("입력 오류!\n");
				while (getchar() != '\n');
			}
			else
			{
				ch[i].range = range;
				break;
			}
		}

		while (getchar() != '\n');

		while (1)
		{
			printf("%s의 position 입력: ", name);
			fgets(position, sizeof(position), stdin);

			position[strcspn(position, "\n")] = '\0';

			if (strcmp(position, "top") == 0 || strcmp(position, "jungle") == 0 || strcmp(position, "mid") == 0 || strcmp(position, "bottom") == 0 || strcmp(position, "support") == 0)
			{
				strcpy_s(ch[i].position, 10, position);
				break;
			}
			else
			{
				printf("입력 오류!\n");
			}
		}

		printf("\n%s 추가 완료!\n", name);

		count_ch();

		return;
	}
	else if (i == MAX_CHAMPIONS - 1)
	{
		printf("챔피언이 가득 찼습니다!");
		return;
	}
	else
	{
		Insert_Ch(++i);
	}


}

// 챔피언 전체 출력 함수
void Printall(int i)
{
	if (champion_count == 0)
	{
		printf("\n챔피언이 없습니다!");
	}
	else
	{
		if (i != champion_count)
		{
			if(strcmp(ch[i].name, "") != 0)
			{
				if (strlen(ch[i].name) < 4)
				{
					printf("챔피언이름: %s\t\t", &ch[i].name);
				}
				else
				{
					printf("챔피언이름: %s\t", &ch[i].name);
				}
				printf("hp: %d\tmp: %d\tspeed: %d\trange: %d\tposition: %s\n", ch[i].hp, ch[i].mp, ch[i].speed, ch[i].range, ch[i].position);
			}

			Printall(++i);
		}
		else
		{
			return;
		}
	}
}

// 선택한 챔피언 삭제 함수
void delete_ch(char* name, int i)
{
		if (i != champion_count)
		{
			if (strcmp(ch[i].name, name) == 0)
			{
				strcpy_s(ch[i].name, MAX_NAMELEN, "\0");
				strcpy_s(ch[i].position, 10, "\0");
				ch[i].hp = 0;
				ch[i].mp = 0;
				ch[i].speed = 0;
				ch[i].range = 0;
				count_ch();
				printf("\n%s가 삭제되었습니다.\n", name);
				return;
			}
			delete_ch(name, ++i);
		}
		else
		{
			printf("\n%s를 찾을 수 없습니다!\n", name);
			return;
		}
}

// 선택한 포지션 전체삭제 함수
void deleteall(char* position, int i, int found)
{

	if (i != champion_count)
	{
		if (strcmp(ch[i].position, position) == 0)
		{
			strcpy_s(ch[i].name, MAX_NAMELEN, "\0");
			strcpy_s(ch[i].position, 10, "\0");
			ch[i].hp = 0;
			ch[i].mp = 0;
			ch[i].speed = 0;
			ch[i].range = 0;

			found = 1;
		}
		deleteall(position, ++i, found);
	}
	else
	{
		if (found == 0)
		{
			printf("%s를 찾지 못했습니다!\n", position);
		}
		else
		{
			count_ch();
			printf("삭제되었습니다!\n");
		}

		return;
	}


}

int FindMaxHpIndex(int i, int hp)
{

	if (i != champion_count)
	{
		if (ch[i].hp > hp)
		{
			hp = ch[i].hp;
		}
		FindMaxHpIndex(++i, hp);
	}
	else
	{
		return hp;
	}
}

// 최대 HP 챔피언 출력 함수
void FindMaxHp(int i)
{
	int hp = FindMaxHpIndex(0, 0);

	if (i != champion_count)
	{
		if (ch[i].hp == hp)
		{
			if (strlen(ch[i].name) < 4)
			{
				printf("챔피언이름: %s\t\t", &ch[i].name);
			}
			else
			{
				printf("챔피언이름: %s\t", &ch[i].name);
			}
			printf("hp: %d\tmp: %d\tspeed: %d\trange: %d\tposition: %s\n", ch[i].hp, ch[i].mp, ch[i].speed, ch[i].range, ch[i].position);
		}
		FindMaxHp(++i);
	}
	else
	{
		return;
	}
}

// HP 내림차순 정렬 함수
void SortByHp(int i)
{
	if (i != champion_count) 
	{
		for (int j = 0; j < champion_count - i; j++) 
		{
			if (ch[j].hp < ch[j + 1].hp) 
			{
				char nameex[30];
				char positionex[10];
				strcpy_s(nameex, 30, ch[j].name);
				strcpy_s(positionex, 10, ch[j].position);
				int hpex = ch[j].hp;
				int mpex = ch[j].mp;
				int speedex = ch[j].speed;
				int rangeex = ch[j].range;
				ch[j].hp = ch[j + 1].hp;
				ch[j + 1].hp = hpex;
				ch[j].mp = ch[j + 1].mp;
				ch[j + 1].mp = mpex;
				ch[j].speed = ch[j + 1].speed;
				ch[j + 1].speed = speedex;
				ch[j].range = ch[j + 1].range;
				ch[j + 1].range = rangeex;
			}
		}
		SortByHp(++i);
	}
	else
	{
		count_ch();
		printf("정렬 완료!\n");
		return;
	}

}




int main()
{
	champion_default_scan();
	while (1)
	{
		char input[100];
		char command[10];
		char name[30];

		printf("\nSearch: 챔피언 검색\nInsert: 챔피언 추가\nDelete: 챔피언 삭제\nDeleteAll: 선택한 포지션 챔피언 삭제\nPrintAll: 챔피언 정보 출력\nFindMaxHp: 체력이 가장 큰 챔피언 출력\nSortByHp: HP 오름차순 정렬\n\n명령어 입력: ");
		fgets(input, sizeof(input), stdin);

		input[strcspn(input, "\n")] = '\0';
		
		if (sscanf_s(input, "%s %[^\n]", command, sizeof(command), name, sizeof(name)) >= 2)
		{
			if (strcmp(command, "Search") == 0)
			{
				Search_Ch(name, 0, 0);
			}
			else if (strcmp(command, "Delete") == 0)
			{
				delete_ch(name, 0);
			}
			else if (strcmp(command, "DeleteAll") == 0)
			{
				deleteall(name, 0, 0);
			}
			else
			{
				printf("\n명령어가 잘못되었습니다.\n");
			}
		}

		else if (strcmp(input, "Insert") == 0)
		{
			Insert_Ch(0);
		}

		else if (strcmp(input, "PrintAll") == 0)
		{
			Printall(0);
		}

		else if (strcmp(input, "FindMaxHp") == 0)
		{
			FindMaxHp(0);
		}

		else if (strcmp(input, "SortByHp") == 0)
		{
			SortByHp(0);
		}

		else if (strcmp(input, "q") == 0)
		{
			break;
		}

		else
		{
			printf("\n명령어가 잘못되었습니다.\n");
		}
	}
}

