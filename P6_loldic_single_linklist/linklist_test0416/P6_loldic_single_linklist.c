#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_MAX 30

typedef struct Node
{
	char name[NAME_MAX];
	char posi[NAME_MAX];
	int hp, mp, speed, range;
	struct Node* next;
}Node;

void scandata(Node** head);
void Insert(Node** head, char* namev, int hpv, int mpv, int speedv, int rangev, char* posiv);
void Search_SL(Node** head, char* namev);
void PrintAll_SL(Node** head);
void Insert_SL(Node** head);
void Delete_SL(Node** head, char* namev);
void DeleteAll_SL(Node** head, char* posiv);
void FindMaxHp_SL(Node** head);
void SortByHp_SL(Node** head);

int main()
{
	char input[300];
	char namev[NAME_MAX];
	char com[30];
	Node* head = NULL;

	scandata(&head);

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
		else if (strcmp(input, "Insert_SL") == 0)
		{
			Insert_SL(&head);
		}
		else if (strcmp(input, "PrintAll_SL") == 0)
		{
			PrintAll_SL(&head);
		}
		else if (strcmp(input, "FindMaxHp_SL") == 0)
		{
			FindMaxHp_SL(&head);
		}
		else if (strcmp(input, "SortByHp_SL") == 0)
		{
			SortByHp_SL(&head);
		}
		else
		{
			printf("�Է� ����!\n");
		}

	}
}

void scandata(Node** head)
{
	char input[300];
	char namev[NAME_MAX];
	char posiv[NAME_MAX];
	int hpv = 0, mpv = 0, speedv = 0, rangev = 0;

	while (1)
	{
		printf("textdata.txt �Է� (�Ϸ� �� ���� �� 'q' �Է�): \n");
		gets_s(input, 300);

		if (sscanf_s(input, "%[^\t]%d\t%d\t%d\t%d\t%s", namev, NAME_MAX, &hpv, &mpv, &speedv, &rangev, posiv, NAME_MAX) >= 6)
		{
			Insert(head, namev, hpv, mpv, speedv, rangev, posiv);
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

void Search_SL(Node** head, char* namev)
{
	Node* temp = *head;
	int found = 0;

	while (temp != NULL)
	{
		if (strcmp(temp->name, namev) == 0)
		{
			printf("è�Ǿ� �̸�: %s\thp: %d\tmp: %d\tspeed: %d\trange: %d\tposition: %s\n", temp->name, temp->hp, temp->mp, temp->speed, temp->range, temp->posi);
			found = 1;
		}
		temp = temp->next;
	}
	if (found == 0)
	{
		printf("è�Ǿ��� ã�� �� �����ϴ�!\n");
	}
}

void PrintAll_SL(Node** head)
{
	Node* temp = *head;

	while (temp != NULL)
	{
		printf("è�Ǿ� �̸�: %s\thp: %d\tmp: %d\tspeed: %d\trange: %d\tposition: %s\n", temp->name, temp->hp, temp->mp, temp->speed, temp->range, temp->posi);
		temp = temp->next;
	}
}

void Insert_SL(Node** head)
{
	char namev[NAME_MAX];
	char posiv[NAME_MAX];
	int hpv = 0, mpv = 0, speedv = 0, rangev = 0;

	while (1)
	{
		printf("è�Ǿ� �̸�: ");
		gets_s(namev, NAME_MAX);

		if (strlen(namev) > 1)
		{
			break;
		}
		else
		{
			printf("�Է� ����!\n");
		}
	}
	while (1)
	{
		printf("hp �Է�: ");
		if (scanf_s("%d", &hpv) == 1)
		{
			while (getchar() != '\n');
			break;
		}
		else
		{
			while (getchar() != '\n');
			printf("�Է� ����!\n");
		}
	}
	while (1)
	{
		printf("mp �Է�: ");
		if (scanf_s("%d", &mpv) == 1)
		{
			while (getchar() != '\n');
			break;
		}
		else
		{
			while (getchar() != '\n');
			printf("�Է� ����!\n");
		}
	}
	while (1)
	{
		printf("speed �Է�: ");
		if (scanf_s("%d", &speedv) == 1)
		{
			while (getchar() != '\n');
			break;
		}
		else
		{
			while (getchar() != '\n');
			printf("�Է� ����!\n");
		}
	}
	while (1)
	{
		printf("range �Է�: ");
		if (scanf_s("%d", &rangev) == 1)
		{
			while (getchar() != '\n');
			break;
		}
		else
		{
			while (getchar() != '\n');
			printf("�Է� ����!5\n");
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
	printf("%s �߰� �Ϸ�!\n", namev);
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
			printf("�����Ϸ�!\n");
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
		printf("ã�����߽��ϴ�!\n");
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
			printf("%s ���� �Ϸ�\n", temp->name);
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
		printf("position�� %s�� è�Ǿ��� ã�� ���߽��ϴ�!\n", posiv);
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
			printf("è�Ǿ� �̸�: %s\thp: %d\tmp: %d\tspeed: %d\trange: %d\tposition: %s\n", temp->name, temp->hp, temp->mp, temp->speed, temp->range, temp->posi);
		}
		temp = temp->next;
	}
}

void SortByHp_SL(Node** head)
{
	Node* temp = *head;
	Node* prev = NULL;
	int swapped = 0;

	do
	{
		temp = *head;
		prev = NULL;
		swapped = 0;

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
}

