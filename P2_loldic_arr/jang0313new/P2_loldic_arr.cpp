#include <iostream>
#define MAX_CHAMPIONS 200

using namespace std;

struct Champions
{
	char name[30];
	char position[10];
	int hp;
	int mp;
	int speed;
	int range;
};

struct Champions ch[MAX_CHAMPIONS];
size_t champion_count = 3;

void champion_default()
{
	strcpy_s(ch[0].name, 30, "Jayce");
	strcpy_s(ch[0].position, 10, "mid");
	ch[0].hp = 3466;
	ch[0].mp = 8307;
	ch[0].speed = 452;
	ch[0].range = 73;

	strcpy_s(ch[1].name, 30, "Vayne");
	strcpy_s(ch[1].position, 10, "support");
	ch[1].hp = 3318;
	ch[1].mp = 2790;
	ch[1].speed = 390;
	ch[1].range = 60;

	strcpy_s(ch[2].name, 30, "LeeSin");
	strcpy_s(ch[2].position, 10, "support");
	ch[2].hp = 9864;
	ch[2].mp = 6257;
	ch[2].speed = 747;
	ch[2].range = 19;
}

void Search_Ch()
{
	char name[30];
	int found = 0;

	while (true)
	{
		cout << "è�Ǿ��̸�: ";
		cin >> name;

		for (int i = 0; i < champion_count; i++)
		{
			if (strcmp(ch[i].name, name) == 0)
			{
				cout << "è�Ǿ��̸�: " << ch[i].name << "\thp: " << ch[i].hp << "\tmp: " << ch[i].mp << "\tspeed: " << ch[i].speed << "\trange: " << ch[i].range << "\tposition: \n" << ch[i].position;
				found = 1;
				return;
			}
		}

		if (found == 0)
		{
			cout << name << "�� ã�� �� �����ϴ�\n";
		}
	}
}

void Insert_Ch()
{
	char name[30] = { 0 }, position[10] = { 0 };
	int hp = 0, mp = 0, speed = 0, range = 0;
	cout << "è�Ǿ� �̸� �Է�: ";
	cin >> name;
	strcpy_s(ch[champion_count].name, 30, name);

	cout << name << "�� hp �Է�:";
	cin >> hp;
	ch[champion_count].hp = hp;

	cout << name << "�� mp �Է�:";
	cin >> mp;
	ch[champion_count].mp = mp;

	cout << name << "�� speed �Է�:";
	cin >> speed;
	ch[champion_count].speed = speed;

	cout << name << "�� range �Է�:";
	cin >> range;
	ch[champion_count].range = range;

	while (true)
	{
		cout << name << "�� position �Է�: ";;
		cin >> position;
		if (strcmp(position, "top") == 0 || strcmp(position, "jungle") == 0 || strcmp(position, "mid") == 0 || strcmp(position, "bottom") == 0 || strcmp(position, "support") == 0)
		{
			strcpy_s(ch[champion_count].position, 30, position);
			break;
		}
		else
		{
			cout << "�Է� ����!\n";
		}
	}


	cout << name << " �߰� �Ϸ�!\n";


	champion_count++;
}

void Printall()
{
	for (int i = 0; i < champion_count; i++)
	{
		cout << "è�Ǿ��̸�: " << ch[i].name << "\thp: " << ch[i].hp << "\tmp: " << ch[i].mp << "\tspeed: " << ch[i].speed << "\trange: " << ch[i].range << "\tposition: " << ch[i].position << "\n";
	}
}

void delete_ch()
{
	char name[30];
	int found = -1;
	while (true)
	{
		cout << "è�Ǿ� �̸�: ";
		cin >> name;

		for (int i = 0; i < champion_count; i++)
		{
			if (strcmp(ch[i].name, name) == 0)
			{
				found = i;
				champion_count--;
				cout << name << "�� �����Ǿ����ϴ�.\n";

				break;
			}
		}

		if (found == -1)
		{
			cout << "�Է� ����!\n";
			continue;
		}
		else
		{
			break;
		}

		for (int j = found; j < champion_count; j++)
		{
			if (j + 1 <= champion_count)
			{
				strcpy_s(ch[j].name, 30, ch[j + 1].name);
				strcpy_s(ch[j].position, 10, ch[j + 1].position);
				ch[j].hp = ch[j + 1].hp;
				ch[j].mp = ch[j + 1].mp;
				ch[j].speed = ch[j + 1].speed;
				ch[j].range = ch[j + 1].range;
			}
		}

	}
}

int main()
{
	champion_default();
	while (1)
	{
		char command[10] = { 0 };
		cout << "��ɾ� �Է�: ";
		cin >> command;

		while (getchar() != '\n');

		if (strcmp(command, "Search") == 0)
		{
			Search_Ch();
		}
		else if (strcmp(command, "Insert") == 0)
		{
			Insert_Ch();
		}
		else if (strcmp(command, "PrintAll") == 0)
		{
			Printall();
		}
		else if (strcmp(command, "Delete") == 0)
		{
			delete_ch();
		}
		else if (strcmp(command, "DeleteAll") == 0)
		{

		}
		else if (strcmp(command, "q") == 0)
		{
			break;
		}
		else
		{
			cout << "��ɾ �߸��Ǿ����ϴ�.\n";
		}
	}
}

