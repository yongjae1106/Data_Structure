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
}
Node;

void insert_SL(Node** head);
void insertR(Node** head, char* namev, int hpv, int mpv, int speedv, int rangev, char* posiv);
void del(Node** head, char* namev);
void delall(Node** head, char* posiv);
void search_SL(Node** head, char* namev);
void print(Node** head);
void scandata(Node** head);
void findmaxhp_SL(Node** head);
void sortbyhp_SL(Node** head);



int main()
{
	char input[300];
	char com[30];
	char namev[NAME_MAX];
	Node* head = NULL;

	scandata(&head);

	while(1)
	{
		printf("��ɾ� �Է�: ");
		gets_s(input, 300);


		if (sscanf_s(input, "%s %[^\n]", com, sizeof(com), namev, NAME_MAX) == 2)
		{
			if (strcmp(com, "Search_SL") == 0)
			{
				search_SL(&head, namev);
			}
			else if (strcmp(com, "Delete_SL") == 0)
			{
				del(&head, namev);
			}
			else if (strcmp(com, "DeleteAll_SL") == 0)
			{
				delall(&head, namev);
			}
		}
		else if (strcmp(input, "Insert_SL") == 0)
		{
			insert_SL(&head);
		}
		else if (strcmp(input, "PrintAll_SL") == 0)
		{
			print(&head);
		}
		else if (strcmp(input, "FindMaxHp_SL") == 0)
		{
			findmaxhp_SL(&head);
		}
		else if (strcmp(input, "SortByHp_SL") == 0)
		{
			sortbyhp_SL(&head);
		}
		else
		{
			printf("��ɾ� ����!\n");
		}
	}

}

void insert_SL(Node** head)
{
	char name[NAME_MAX];
	char posi[NAME_MAX];
	int hp = 0, mp = 0, speed = 0, range = 0;

	while (1)
	{
		printf("è�Ǿ� �̸�: ");
		gets_s(name, NAME_MAX);

		if (strlen(name) > 1)
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
		printf("%s�� hp �Է�: ", name);
		if (scanf_s("%d", &hp) == 1)
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
		printf("%s�� mp �Է�: ", name);
		if (scanf_s("%d", &mp) == 1)
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
		printf("%s�� speed �Է�: ", name);
		if (scanf_s("%d", &speed) == 1)
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
		printf("%s�� range �Է�: ", name);
		if (scanf_s("%d", &range) == 1)
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
		printf("%s�� position �Է�: ", name);
		scanf_s("%s", posi, NAME_MAX);

		while (getchar() != '\n');

		if (strcmp(posi, "top") == 0 || strcmp(posi, "jungle") == 0 || strcmp(posi, "mid") == 0 || strcmp(posi, "bottom") == 0 || strcmp(posi, "support") == 0)
		{
			break;
		}
		else
		{
			printf("�Է� ����!\n");
		}
	}

	insertR(head, name, hp, mp, speed, range, posi);
	printf("%s �߰� �Ϸ�!\n", name);
}

void insertR(Node** head, char* namev, int hpv, int mpv, int speedv, int rangev, char* posiv)
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

void del(Node** head, char* namev)
{
	Node* temp = *head;
	Node* prev = NULL;

	while (temp != NULL && strcmp(temp->name, namev) != 0)
	{
		prev = temp;
		temp = temp->next;
	}

	if (temp == NULL) // è�Ǿ��� ã�� ���� ���
	{
		printf("è�Ǿ��� ã�� ���߽��ϴ�!\n");
		return;
	}
	else if (temp == *head) // ù��° ��� �� ���
	{
		*head = temp->next;
	}
	else if (temp->next == NULL) // ������ ����� ���
	{
		prev->next = NULL;
	}
	else
	{
		prev->next = temp->next;
	}
	free(temp);
	printf("%s ���� �Ϸ�!\n", namev);
}

void delall(Node** head, char* posiv)
{
	Node* temp = *head;
	Node* prev = NULL;
	int found = 0;
	while (temp != NULL)
	{
		if (strcmp(temp->posi, posiv) == 0)
		{
			found = 1;
			if (temp == *head)
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
			printf("%s �����Ϸ�.\n", temp->name);
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
		printf("%s�� è�Ǿ��� ã�� �� �����ϴ�!\n", posiv);
	}

}

void print(Node** head)
{
	Node* temp = *head;

	while (temp != NULL)
	{
		printf("�̸�: %s\t\thp: %d\tmp: %d\tspeed: %d\trange: %d\tposition: %s\n", temp->name, temp->hp, temp->mp, temp->speed, temp->range, temp->posi);
		temp = temp->next;
	}
}

void scandata(Node** head)
{
	char data[300];
	char name[NAME_MAX];
	char posi[NAME_MAX];
	int hp = 0, mp = 0, speed = 0, range = 0;

	while (1)
	{
		printf("datatext.txt �Է� (�Է� �Ϸ� �� ���� �� 'q' �Է�): ");
		gets_s(data, 300);

		if (sscanf_s(data, "%[^\t]%d\t%d\t%d\t%d\t%s", name, NAME_MAX, &hp, &mp, &speed, &range, posi, NAME_MAX) == 6)
		{
			insertR(head, name, hp, mp, speed, range, posi);
		}
		else if (strcmp(data, "q") == 0)
		{
			printf("�Է¿Ϸ�!\n");
			break;
		}
		else
		{
			printf("�Է¿���!\n");
		}
	}
}

void search_SL(Node** head, char* namev)
{
	Node* temp = *head;
	
	while (temp != NULL && strcmp(temp->name, namev) != 0)
	{
		temp = temp->next;
	}

	if (temp == NULL)
	{
		printf("è�Ǿ��� ã�� �� �����ϴ�!\n");
	}
	else
	{
		printf("�̸�: %s\t\thp: %d\tmp: %d\tspeed: %d\trange: %d\tposition: %s\n", temp->name, temp->hp, temp->mp, temp->speed, temp->range, temp->posi);
	}
}

void findmaxhp_SL(Node** head)
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
			printf("�̸�: %s\t\thp: %d\tmp: %d\tspeed: %d\trange: %d\tposition: %s\n", temp->name, temp->hp, temp->mp, temp->speed, temp->range, temp->posi);
		}
		temp = temp->next;
	}
}

void sortbyhp_SL(Node** head)
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
				if (prev == NULL)
				{
					temp->next = nextnode->next;
					nextnode->next = temp;
					*head = nextnode;
					prev = *head;
				}
				else
				{
					prev->next = nextnode;
					temp->next = nextnode->next;
					nextnode->next = temp;
					prev = nextnode;
				}
				swapped = 1;
			}
			else
			{
				prev = temp;
				temp = temp->next;
			}
		}
	} while (swapped);

	printf("���� �Ϸ�!\n");
}