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
		printf("��ɾ� �Է�: ");
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
			printf("�Է� ����!\n");
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
		printf("textdata.txt �Է� (�Ϸ� �� ���� �� 'q'�Է�) : \n");
		gets_s(input, 300);

		if (sscanf_s(input, "%[^\t]%d\t%d\t%d\t%d\t%s", name, NAME_MAX, &hp, &mp, &speed, &range, posi, NAME_MAX) >= 6)
		{
			Insert(head, name, hp, mp, speed, range, posi);
		}
		else if (strcmp(input, "q") == 0)
		{
			printf("�Է� �Ϸ�!\n");
			break;
		}
		else
		{
			printf("�Է� ����!\n");
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
			printf("è�Ǿ��̸�: %s\thp: %d\tmp: %d\tspeed: %d\trange: %d\tposition: %s\n", temp->name, temp->hp, temp->mp, temp->speed, temp->range, temp->posi);
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
		printf("è�Ǿ� �̸�: ");
		gets_s(namev, NAME_MAX);

		if (strlen(namev) <= 1)
		{
			printf("�Է� ����!\n");
		}
		else
		{
			break;
		}
	}
	while (1)
	{
		printf("hp �Է�: ");

		if (scanf_s("%d", &hpv) != 1)
		{
			while (getchar() != '\n');
			printf("�Է� ����!\n");
		}
		else
		{
			while (getchar() != '\n');
			break;
		}
	}
	while (1)
	{
		printf("mp �Է�: ");

		if (scanf_s("%d", &mpv) != 1)
		{
			while (getchar() != '\n');
			printf("�Է� ����!\n");
		}
		else
		{
			while (getchar() != '\n');
			break;
		}
	}
	while (1)
	{
		printf("speed �Է�: ");

		if (scanf_s("%d", &speedv) != 1)
		{
			while (getchar() != '\n');
			printf("�Է� ����!\n");
		}
		else
		{
			while (getchar() != '\n');
			break;
		}
	}
	while (1)
	{
		printf("range �Է�: ");

		if (scanf_s("%d", &rangev) != 1)
		{
			while (getchar() != '\n');
			printf("�Է� ����!\n");
		}
		else
		{
			while (getchar() != '\n');
			break;
		}
	}
	while (1)
	{
		printf("position �Է�: ");
		gets_s(posiv, NAME_MAX);

		if (strcmp(posiv, "top") == 0 || strcmp(posiv, "jungle") == 0 || strcmp(posiv, "mid") == 0 || strcmp(posiv, "bottom") == 0 || strcmp(posiv, "support") == 0)
		{
			break;
		}
		else
		{
			printf("�Է� ����!\n");
		}
	}
	
	Insert(head, namev, hpv, mpv, speedv, rangev, posiv);
	printf("�Է� �Ϸ�!\n");
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
		printf("è�Ǿ��̸�: %s\thp: %d\tmp: %d\tspeed: %d\trange: %d\tposition: %s\n", temp->name, temp->hp, temp->mp, temp->speed, temp->range, temp->posi);
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
			printf("%s ���� �Ϸ�!\n", namev);
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
		printf("%s�� ã�� �� �����ϴ�.\n");
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
			printf("%s ���� �Ϸ�!\n", temp->name);
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
		printf("%s�� ã�� �� �����ϴ�.\n");
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
			printf("è�Ǿ��̸�: %s\thp: %d\tmp: %d\tspeed: %d\trange: %d\tposition: %s\n", temp->name, temp->hp, temp->mp, temp->speed, temp->range, temp->posi);
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

	printf("�Է� �Ϸ�!\n");
}