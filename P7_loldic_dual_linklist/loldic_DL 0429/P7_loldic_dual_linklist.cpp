#include <iostream>
#include <stdlib.h>
#include <cstring>
#define NAME_MAX 30

using namespace std;

struct Node
{
	char name[NAME_MAX];
	char posi[NAME_MAX];
	int hp, mp, speed, range;
	Node* next;
	Node* prev;
	
};

void initList();
void insert(char* namev, int hpv, int mpv, int speedv, int rangev, char* posiv);
void scandata();
void PrintAll_DL(int dir);
void Insert_DL();
void Search_DL(char* namev);
void Delete_DL(char* namev);
void DeleteAll_DL(char* posiv);
void FindMaxHp_DL();
void SortByHp_DL();

Node* head;
Node* tail;

int main()
{
	char input[300];
	char namev[NAME_MAX];
	char com[30];

	initList();

	scandata();

	while (1)
	{
		printf("명령어 입력: ");
		gets_s(input, 300);

		if (sscanf_s(input, "%s %[^\n]", com, 30, namev, NAME_MAX) >= 2)
		{
			if (strcmp(com, "Search_DL") == 0)
			{
				Search_DL(namev);
			}
			else if (strcmp(com, "Delete_DL") == 0)
			{
				Delete_DL(namev);
			}
			else if (strcmp(com, "DeleteAll_DL") == 0)
			{
				DeleteAll_DL(namev);
			}
		}
		else if(strcmp(input, "PrintAll_DL_L") == 0)
		{
			PrintAll_DL(1);
		}
		else if (strcmp(input, "PrintAll_DL_R") == 0)
		{
			PrintAll_DL(0);
		}
		else if (strcmp(input, "Insert_DL") == 0)
		{
			Insert_DL();
		}
		else if (strcmp(input, "FindMaxHp_DL") == 0)
		{
			FindMaxHp_DL();
		}
		else if (strcmp(input, "SortByHp_DL") == 0)
		{
			SortByHp_DL();
		}
		else
		{
			printf("입력 오류!\n");
		}
	}

}

void initList()
{
	head = new Node;
	tail = new Node;

	head->prev = nullptr;
	head->next = tail;

	tail->prev = head;
	tail->next = nullptr;
}

void insert(char* namev, int hpv, int mpv, int speedv, int rangev, char* posiv)
{
	Node* current = new Node;
	strcpy_s(current->name, NAME_MAX, namev);
	strcpy_s(current->posi, NAME_MAX, posiv);
	current->hp = hpv;
	current->mp = mpv;
	current->speed = speedv;
	current->range = rangev;

	current->prev = tail->prev;
	tail->prev = current;
	current->prev->next = current;
	current->next = tail;
}

void scandata()
{
	char input[300];
	char namev[NAME_MAX];
	char posiv[NAME_MAX];
	int hpv, mpv, speedv, rangev;

	while (1)
	{
		printf("textdata.txt 입력 (완료 시 엔터 후 'q'입력): \n");
		gets_s(input, 300);
		
		if (sscanf_s(input, "%[^\t]%d\t%d\t%d\t%d\t%s", namev, NAME_MAX, &hpv, &mpv, &speedv, &rangev, posiv, NAME_MAX) >= 6)
		{
			insert(namev, hpv, mpv, speedv, rangev, posiv);
		}
		else if (input[0] == 'q')
		{
			printf("입력 완료!\n");
			return;
		}
		else
		{
			printf("입력 오류!\n");
		}
	}
}

void PrintAll_DL(int dir)
{
	Node* current;

	if(dir == 0)
	{
		for (current = head->next; current != tail; current = current->next)
		{
			printf("챔피언 이름: %s\thp: %d\tmp: %d\tspeed: %d\trange: %d\tposition: %s\n", current->name, current->hp, current->mp, current->speed, current->range, current->posi);
		}
	}
	else
	{
		for (current = tail->prev; current != head; current = current->prev)
		{
			printf("챔피언 이름: %s\thp: %d\tmp: %d\tspeed: %d\trange: %d\tposition: %s\n", current->name, current->hp, current->mp, current->speed, current->range, current->posi);
		}
	}

}

void Insert_DL()
{
	char namev[NAME_MAX];
	char posiv[NAME_MAX];
	int hpv, mpv, speedv, rangev;

	while (1)
	{
		printf("챔피언 이름: ");
		gets_s(namev, NAME_MAX);

		if (strlen(namev) > 1)
		{
			break;
		}
		else
		{
			printf("입력 오류!\n");
		}
	}
	while (1)
	{
		printf("hp 입력: ");
		scanf_s("%d", &hpv);

		if (scanf_s("%d", &hpv) == 1)
		{
			while (getchar() != '\n');
			break;
		}
		else
		{
			while (getchar() != '\n');
			printf("입력 오류!\n");
		}
	}
	while (1)
	{
		printf("mp 입력: ");
		scanf_s("%d", &mpv);

		if (scanf_s("%d", &mpv) == 1)
		{
			while (getchar() != '\n');
			break;
		}
		else
		{
			while (getchar() != '\n');
			printf("입력 오류!\n");
		}
	}
	while (1)
	{
		printf("speed 입력: ");
		scanf_s("%d", &speedv);

		if (scanf_s("%d", &speedv) == 1)
		{
			while (getchar() != '\n');
			break;
		}
		else
		{
			while (getchar() != '\n');
			printf("입력 오류!\n");
		}
	}
	while (1)
	{
		printf("range 입력: ");
		scanf_s("%d", &rangev);

		if (scanf_s("%d", &rangev) == 1)
		{
			while (getchar() != '\n');
			break;
		}
		else
		{
			while (getchar() != '\n');
			printf("입력 오류!\n");
		}
	}
	while (1)
	{
		printf("position 입력: ");
		gets_s(posiv, NAME_MAX);

		if (strcmp(posiv, "top") == 0 && strcmp(posiv, "jungle") == 0 && strcmp(posiv, "mid") == 0 && strcmp(posiv, "bottom") == 0 && strcmp(posiv, "support") == 0)
		{
			break;
		}
		else
		{
			printf("입력 오류!\n");
		}
	}

	insert(namev, hpv, mpv, speedv, rangev, posiv);
}

void Search_DL(char* namev)
{
	Node* current = head->next;
	int found = 0;
	for (; current != tail; current = current->next)
	{
		if (strcmp(current->name, namev) == 0)
		{
			found = 1;
			printf("챔피언 이름: %s\thp: %d\tmp: %d\tspeed: %d\trange: %d\tposition: %s\n", current->name, current->hp, current->mp, current->speed, current->range, current->posi);
		}
	}
	if (found == 0)
	{
		printf("챔피언을 찾을 수 없습니다!\n");
	}
}

void Delete_DL(char* namev)
{
	Node* current = head->next;
	int found = 0;

	for (; current != tail; current = current->next)
	{
		if (strcmp(current->name, namev) == 0)
		{
			Node* temp = current->next;

			found = 1;

			current->prev->next = current->next;
			current->next->prev = current->prev;

			printf("%s 삭제 완료!\n", current->name);

			free(current);

			current = temp;
		}
	}

	if (found == 0)
	{
		printf("챔피언을 찾을 수 없습니다!\n");
	}

}

void DeleteAll_DL(char* posiv)
{
	Node* current = head->next;
	int found = 0;

	for (; current != tail; current = current->next)
	{
		if (strcmp(current->posi, posiv) == 0)
		{
			Node* temp = current->next;

			found = 1;

			current->prev->next = current->next;
			current->next->prev = current->prev;

			printf("%s 삭제 완료!\n", current->name);

			free(current);

			current = temp;
		}
	}

	if (found == 0)
	{
		printf("position이 %s인 챔피언을 찾을 수 없습니다!\n", posiv);
	}

}

void FindMaxHp_DL()
{
	Node* current = head->next;
	int maxhp = 0;

	for (; current != tail; current = current->next)
	{
		if (maxhp < current->hp)
		{
			maxhp = current->hp;
		}
	}
	current = head->next;

	for (; current != tail; current = current->next)
	{
		if (current->hp == maxhp)
		{
			printf("챔피언 이름: %s\thp: %d\tmp: %d\tspeed: %d\trange: %d\tposition: %s\n", current->name, current->hp, current->mp, current->speed, current->range, current->posi);
		}
	}
}

void SortByHp_DL()
{
	Node* current;
	int swapped = 0;
	do
	{
		swapped = 0;
		Node* current = head->next;

		while (current != tail)
		{
			Node* nextnode = current->next;
			Node* prevnode = current->prev;
			if (current->hp < current->next->hp)
			{
				swapped = 1;
				current->next = nextnode->next;
				prevnode->next = nextnode;
				nextnode->next->prev = current;
				nextnode->prev = prevnode;
				nextnode->next = current;
				current->prev = nextnode;
			}
			else
			{
				current = current->next;
			}
		}
	} while (swapped);

	printf("정렬 완료!\n");
}