#include <iostream>
#include <ctime>
#define MAX_NAME 30
#define MAX_CHAMPION

using namespace std;

struct NodeDL
{
	int hp, ad, df;
	char name[MAX_NAME];
	char posi[MAX_NAME];
	NodeDL* next;
	NodeDL* prev;
};
struct NodeSL
{
	int hp, ad, df;
	char name[MAX_NAME];
	char posi[MAX_NAME];
	NodeSL* next;
};

NodeDL* tail_DL;
NodeDL* head_DL;

NodeSL* head_SL = NULL;

void initlist();
void scandata();
void PrintAll_DL(int dir);
void PrintAll_SL();
void FindMaxHp_DL();
void SortByHp_DL();
void FindMaxHp_SL();
void SortByHp_SL();
void insert_DL(char* namev, int hpv, int adv, int dfv, char* posiv);
void insert_SL(char* namev, int hpv, int adv, int dfv, char* posiv);

int main()
{
	clock_t start = 0;
	clock_t end = 0;

	char input[300];

	initlist();

	scandata();

	while (1)
	{
		printf("명령어 입력: ");
		cin >> input;

		if (strcmp(input, "PrintAll_DL_L") == 0)
		{
			start = clock();
			PrintAll_DL(1);
			end = clock();
			cout << "수행시간: " << end - start << "ticks" << endl;
		}
		else if (strcmp(input, "PrintAll_DL_R") == 0)
		{
			start = clock();
			PrintAll_DL(0);
			end = clock();
			cout << "수행시간: " << end - start << "ticks" << endl;
		}
		if (strcmp(input, "PrintAll_SL") == 0)
		{
			start = clock();
			PrintAll_SL();
			end = clock();
			cout << "수행시간: " << end - start << "ticks" << endl;
		}
		else if (strcmp(input, "FindMaxHp_DL") == 0)
		{
			start = clock();
			FindMaxHp_DL();
			end = clock();
			cout << "수행시간: " << end - start << "ticks" << endl;
		}
		else if (strcmp(input, "SortByHp_DL") == 0)
		{
			start = clock();
			SortByHp_DL();
			end = clock();
			cout << "수행시간: " << end - start << "ticks" << endl;
		}
		else if (strcmp(input, "FindMaxHp_SL") == 0)
		{
			start = clock();
			FindMaxHp_SL();
			end = clock();
			cout << "수행시간: " << end - start << "ticks" << endl;
		}
		else if (strcmp(input, "SortByHp_SL") == 0)
		{
			start = clock();
			SortByHp_SL();
			end = clock();
			cout << "수행시간: " << end - start << "ticks" << endl;
		}
	}

}


void scandata()
{
	char input[300];
	char namev[MAX_NAME];
	char posiv[MAX_NAME];
	int hpv, adv, dfv;

	while (1)
	{
		printf("textdata.txt 입력 (완료 시 엔터 후 'q'입력): \n");
		gets_s(input, 300);

		if (sscanf_s(input, "%s %s %d %d %d", posiv, MAX_NAME, namev, MAX_NAME, &hpv, &adv, &dfv) >= 5)
		{
			insert_DL(namev, hpv, adv, dfv, posiv);
			insert_SL(namev, hpv, adv, dfv, posiv);
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

void initlist()
{
	head_DL = new NodeDL;
	tail_DL = new NodeDL;

	head_DL->prev = nullptr;
	head_DL->next = tail_DL;

	tail_DL->prev = head_DL;
	tail_DL->next = nullptr;
}

void insert_DL(char* namev, int hpv, int adv, int dfv, char* posiv)
{
	NodeDL* current = new NodeDL;
	strcpy_s(current->name, MAX_NAME, namev);
	strcpy_s(current->posi, MAX_NAME, posiv);
	current->hp = hpv;
	current->ad = adv;
	current->df = dfv;

	current->prev = tail_DL->prev;
	tail_DL->prev = current;
	current->prev->next = current;
	current->next = tail_DL;
}
void insert_SL(char* namev, int hpv, int adv, int dfv, char* posiv) {
	NodeSL* current = new NodeSL;
	strcpy_s(current->name, MAX_NAME, namev);
	strcpy_s(current->posi, MAX_NAME, posiv);
	current->hp = hpv;
	current->ad = adv;
	current->df = dfv;
	current->next = NULL;

	if (head_SL == NULL)
	{
		head_SL = current;
		return;
	}

	// 맨 뒤에 생성해주기 위해
	NodeSL* temp = head_SL;
	while (temp->next != NULL)
		temp = temp->next;

	temp->next = current;
}

void PrintAll_DL(int dir)
{
	NodeDL* current;

	if (dir == 0)
	{
		for (current = head_DL->next; current != tail_DL; current = current->next)
		{
			printf("챔피언 이름: %s\thp: %d\tposition: %s\tad: %d\tdf: %d\n", current->name, current->hp, current->posi, current->ad, current->df);
		}
	}
	else
	{
		for (current = tail_DL->prev; current != head_DL; current = current->prev)
		{
			printf("챔피언 이름: %s\thp: %d\tposition: %s\tad: %d\tdf: %d\n", current->name, current->hp, current->posi, current->ad, current->df);
		}
	}

}
void PrintAll_SL()
{
	NodeSL* current = head_SL;

	while (current != NULL)
	{
		printf("챔피언 이름: %s\thp: %d\tposition: %s\tad: %d\tdf: %d\n", current->name, current->hp, current->posi, current->ad, current->df);
		current = current->next;
	}
}


// 정렬 및 최대체력출력
void FindMaxHp_DL()
{
	NodeDL* current = head_DL->next;
	int maxhp = 0;

	for (; current != tail_DL; current = current->next)
	{
		if (maxhp < current->hp)
		{
			maxhp = current->hp;
		}
	}
	current = head_DL->next;

	for (; current != tail_DL; current = current->next)
	{
		if (current->hp == maxhp)
		{
			printf("챔피언 이름: %s\thp: %d\tposition: %s\tad: %d\tdf: %d\n", current->name, current->hp, current->posi, current->ad, current->df);
		}
	}
}
void SortByHp_DL()
{
	NodeDL* current;
	int swapped = 0;
	do
	{
		swapped = 0;
		NodeDL* current = head_DL->next;

		while (current != tail_DL)
		{
			NodeDL* nextnode = current->next;
			NodeDL* prevnode = current->prev;
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

void FindMaxHp_SL()
{
	NodeSL* current = head_SL;
	int maxhp = 0;

	while (current != NULL)
	{
		if (maxhp < current->hp)
		{
			maxhp = current->hp;
		}
		current = current->next;
	}
	current = head_SL;

	while (current != NULL)
	{
		if (current->hp == maxhp)
		{
			printf("챔피언 이름: %s\thp: %d\tposition: %s\tad: %d\tdf: %d\n", current->name, current->hp, current->posi, current->ad, current->df);
		}
		current = current->next;
	}
}
void SortByHp_SL()
{
	NodeSL* temp;
	NodeSL* prev;
	int swapped = 0;

	do
	{
		temp = head_SL;
		prev = NULL;
		swapped = 0;

		while (temp->next != NULL)
		{
			NodeSL* nextnode = temp->next;
			if (temp->hp < nextnode->hp)
			{
				swapped = 1;
				if (prev == NULL)
				{
					head_SL = nextnode;
					temp->next = nextnode->next;
					nextnode->next = temp;
					prev = head_SL;
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
	printf("정렬 완료!\n");
}
