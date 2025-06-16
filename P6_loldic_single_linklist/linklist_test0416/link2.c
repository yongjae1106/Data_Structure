#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_MAX 30

typedef struct Node
{
	char name[NAME_MAX], posi[NAME_MAX];
	int hp, mp, speed, range;
	struct Node* next;
}
Node;

void scanch(Node** head);
void Search_SL(Node** head, char* namev);
void Insert_SL(Node** head);
void Insert(Node** head, char* namev, int hpv, int mpv, int speedv, int rangev, char* posiv);
void PrintAll_SL(Node** head);
void Delete_SL(Node** head, char* namev);
void DeleteAll_SL(Node** head, char* posiv);
void FindMaxHp_SL(Node** head);
void SortByHp_SL(Node** head);


int main()
{
	char input[300];
	char com[30];
	char namev[NAME_MAX];

	Node* head = NULL;

	scanch(&head);

	while (1)
	{
		printf("명령어 입력: ");
		gets_s(input, 300);

		if (sscanf_s(input, "%s %[^\n]", com, 30, namev, NAME_MAX) >= 2)
		{
			if (strcmp(com, "Search_SL") == 0)
			{
				Search_SL(&head, namev);
			}
			else if (strcmp(com, "Delete_SL") == 0)
			{
				Delete_SL(&head, namev);
			}
			else if (strcmp(com, "DeleteAll_SL") == 0)
			{
				DeleteAll_SL(&head, namev);
			}
		}
		else if (strcmp(com, "Insert_SL") == 0)
		{
			Insert_SL(&head);
		}
		else if (strcmp(com, "PrintAll_SL") == 0)
		{
			PrintAll_SL(&head);
		}
		else if (strcmp(com, "FindMaxHp_SL") == 0)
		{
			FindMaxHp_SL(&head);
		}
		else if (strcmp(com, "SortByHp_SL") == 0)
		{
			SortByHp_SL(&head);
		}
		else
		{
			printf("입력 오류!\n");
		}
	}
}

void scanch(Node** head)
{
	char input[300];
	char name[NAME_MAX];
	char posi[NAME_MAX];
	int hp = 0, mp = 0, speed = 0, range = 0;

	while (1)
	{
		printf("textdata.txt 입력 (완료 시 엔터 후 'q'입력) : \n");
		gets_s(input, 300);

		if (sscanf_s(input, "%[^\t]%d\t%d\t%d\t%d\t%s", name, NAME_MAX, &hp, &mp, &speed, &range, posi, NAME_MAX) >= 6)
		{
			Insert(head, name, hp, mp, speed, range, posi);
		}
		else if (strcmp(input, "q") == 0)
		{
			printf("입력 완료!\n");
			break;
		}
		else
		{
			printf("입력 오류!\n");
		}
	}
}

void Search_SL(Node** head, char* namev)
{
	Node* temp = *head;

	while (temp != NULL)
	{
		if (strcmp(temp->name, namev) == 0)
		{
			printf("챔피언이름: %s\thp: %d\tmp: %d\tspeed: %d\trange: %d\tposition: %s\n", temp->name, temp->hp, temp->mp, temp->speed, temp->range, temp->posi);
		}
		temp = temp->next;
	}
}

void Insert_SL(Node** head)
{
	char namev[NAME_MAX], posiv[NAME_MAX];
	int hpv = 0, mpv = 0, speedv = 0, rangev = 0;

	while (1)
	{
		printf("챔피언 이름: ");
		gets_s(namev, NAME_MAX);

		if (strlen(namev) <= 1)
		{
			printf("입력 오류!\n");
		}
		else
		{
			break;
		}
	}
	while (1)
	{
		printf("hp 입력: ");

		if (scanf_s("%d", &hpv) != 1)
		{
			while (getchar() != '\n');
			printf("입력 오류!\n");
		}
		else
		{
			while (getchar() != '\n');
			break;
		}
	}
	while (1)
	{
		printf("mp 입력: ");

		if (scanf_s("%d", &mpv) != 1)
		{
			while (getchar() != '\n');
			printf("입력 오류!\n");
		}
		else
		{
			while (getchar() != '\n');
			break;
		}
	}
	while (1)
	{
		printf("speed 입력: ");

		if (scanf_s("%d", &speedv) != 1)
		{
			while (getchar() != '\n');
			printf("입력 오류!\n");
		}
		else
		{
			while (getchar() != '\n');
			break;
		}
	}
	while (1)
	{
		printf("range 입력: ");

		if (scanf_s("%d", &rangev) != 1)
		{
			while (getchar() != '\n');
			printf("입력 오류!\n");
		}
		else
		{
			while (getchar() != '\n');
			break;
		}
	}
	while (1)
	{
		printf("position 입력: ");
		gets_s(posiv, NAME_MAX);

		if (strcmp(posiv, "top") == 0 || strcmp(posiv, "jungle") == 0 || strcmp(posiv, "mid") == 0 || strcmp(posiv, "bottom") == 0 || strcmp(posiv, "support") == 0)
		{
			break;
		}
		else
		{
			printf("입력 오류!\n");
		}
	}
	
	Insert(head, namev, hpv, mpv, speedv, rangev, posiv);
	printf("입력 완료!\n");
}

void Insert(Node** head, char* namev, int hpv, int mpv, int speedv, int rangev, char* posiv)
{
	Node* newnode = malloc(sizeof(Node));
	strcpy_s(newnode->name, NAME_MAX, namev);
	strcpy_s(newnode->posi, NAME_MAX, posiv);
	newnode->hp = hpv;
	newnode->mp = mpv;
	newnode->speed = speedv;
	newnode->range = rangev;
	newnode->next = NULL;

	if (*head == NULL)
	{
		*head = newnode;
		return;
	}

	Node* temp = *head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = newnode;
	
}

void PrintAll_SL(Node** head)
{
	Node* temp = *head;

	while (temp != NULL)
	{
		printf("챔피언이름: %s\thp: %d\tmp: %d\tspeed: %d\trange: %d\tposition: %s\n", temp->name, temp->hp, temp->mp, temp->speed, temp->range, temp->posi);
		temp = temp->next;
	}
}

void Delete_SL(Node** head, char* namev)
{
	Node* temp = *head;
	Node* prev = NULL;
	int found = 0;
	while (temp != NULL)
	{
		if (strcmp(temp->name, namev) == 0)
		{
			found = 1;
			if (prev == NULL)
			{
				*head = temp->next;
			}
			else if (temp->next == NULL)
			{
				prev->next = NULL;
			}
			else
			{
				prev->next = temp->next;
			}
			printf("%s 삭제 완료!\n", namev);
			free(temp);
			temp = prev ? prev->next : *head;
		}
		else
		{
			prev = temp;
			temp = temp->next;
		}
	}
	if (found == 0)
	{
		printf("%s를 찾을 수 없습니다.\n");
	}
}

void DeleteAll_SL(Node** head, char* posiv)
{
	Node* temp = *head;
	Node* prev = NULL;
	int found = 0;
	while (temp != NULL)
	{
		if (strcmp(temp->posi, posiv) == 0)
		{
			found = 1;
			if (prev == NULL)
			{
				*head = temp->next;
			}
			else if (temp->next == NULL)
			{
				prev->next = NULL;
			}
			else
			{
				prev->next = temp->next;
			}
			printf("%s 삭제 완료!\n", temp->name);
			free(temp);
			temp = prev ? prev->next : *head;
		}
		else
		{
			prev = temp;
			temp = temp->next;
		}
	}
	if (found == 0)
	{
		printf("%s를 찾을 수 없습니다.\n");
	}
}

void FindMaxHp_SL(Node** head)
{
	Node* temp = *head;
	int maxhp = 0;
	while (temp != NULL)
	{
		if (maxhp < temp->hp)
		{
			maxhp = temp->hp;
		}
		temp = temp->next;
	}
	temp = *head;

	while (temp != NULL)
	{
		if (temp->hp == maxhp)
		{
			printf("챔피언이름: %s\thp: %d\tmp: %d\tspeed: %d\trange: %d\tposition: %s\n", temp->name, temp->hp, temp->mp, temp->speed, temp->range, temp->posi);
		}
		temp = temp->next;
	}
}

void SortByHp_SL(Node** head)
{
	Node* temp = *head;
	int swapped = 0;

	do
	{
		swapped = 0;
		temp = *head;
		Node* prev = NULL;

		while (temp->next != NULL)
		{
			Node* nextnode = temp->next;
			if (temp->hp < nextnode->hp)
			{
				swapped = 1;
				
				if (prev == NULL)
				{
					*head = nextnode;
					temp->next = nextnode->next;
					nextnode->next = temp;
					prev = *head;
				}
				else
				{
					prev->next = nextnode;
					temp->next = nextnode->next;
					nextnode->next = temp;
					prev = nextnode;
				}
			}
			else
			{
				prev = temp;
				temp = temp->next;
			}
		}
	} while (swapped);

	printf("입력 완료!\n");
}