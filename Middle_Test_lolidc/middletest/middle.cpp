#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

struct Node
{
	string name;
	string id;
	unsigned int age;
	unsigned int depart;
	unsigned int score;
	Node* left;
	Node* right;

	Node(string n, string i, unsigned int a, unsigned int d, unsigned int s) 
		: name(n), id(i), age(a), depart(d), score(s), left(nullptr), right(nullptr) 
	{}
};
struct Node_SL
{
	string name;
	string id;
	int age;
	int depart;
	int score;
	Node_SL* next_id;
	Node_SL* next_age;

	Node_SL(string n, string i, unsigned int a, unsigned int d, unsigned int s)
		: name(n), id(i), age(a), depart(d), score(s), next_id(nullptr), next_age(nullptr)
	{ }
};

class loldic
{
private:
	Node* root;

	Node* insert(Node* current, string name, int age, string id, int depart, int score)
	{
		if (!current)
		{
			return new Node(name, id, age, depart, score);
		}
		if (age < current->age)
		{
			current->left = insert(current->left, name, age, id, depart, score);
		}
		else if (age > current->age)
		{
			current->right = insert(current->right, name, age, id, depart, score);
		}
		else
		{
			// ���̰� ���� ��� ID �������� ����
			if (id < current->id)
			{
				current->left = insert(current->left, name, age, id, depart, score);
			}
			else if (id > current->id)
			{
				current->right = insert(current->right, name, age, id, depart, score);
			}
			else
			{
				cout << "���� ID�� ������ è�Ǿ��� �̹� �����մϴ�!" << endl;
			}
		}		
		return current;
	}

	void Inorder(Node* current)
	{
		if (!current) return;
		Inorder(current->left);
		cout << "�̸�: " << current->name
			<< " \t����: " << current->age
			<< " \tID: " << current->id
			<< " \t�Ҽ�: " << current->depart
			<< " \t����: " << current->score << endl;
		Inorder(current->right);
	}
	void reverseInorder(Node* current)
	{
		if (!current) return;
		reverseInorder(current->right);
		cout << "�̸�: " << current->name
			<< " \t����: " << current->age
			<< " \tID: " << current->id
			<< " \t�Ҽ�: " << current->depart
			<< " \t����: " << current->score << endl;
		reverseInorder(current->left);
	}

public:
	loldic() : root(nullptr) {}

	void insert(string name, int age, string id, int depart, int score)
	{
		root = insert(root, name, age, id, depart, score);
	}

	void PrintAllReversed()
	{
		reverseInorder(root);
	}
	void PrintAll()
	{
		Inorder(root);
	}

};

class loldic_SL
{
private:
	Node_SL* head_id;
	Node_SL* head_age;

public:
	loldic_SL() : head_id(nullptr), head_age(nullptr) {}

	void insert_ID(string name, int age, string id, int depart, int score)
	{
		Node_SL* current = new Node_SL(name, id, age, depart, score);

		if (!head_id)
		{
			head_id = current;
			head_id->next_id = head_id;  // �ڱ� �ڽ��� ����Ű�� ���� ����
			return;
		}

		Node_SL* temp = head_id;

		while (temp->next_id != head_id)
		{
			temp = temp->next_id;
		}
		temp->next_id = current;
		current->next_id = head_id;  // ���ο� ����� ������ head�� �̾���
	}
	void insert_Age(string name, int age, string id, int depart, int score)
	{
		Node_SL* current = new Node_SL(name, id, age, depart, score);

		if (!head_age)
		{
			head_age = current;
			head_age->next_age = head_age;  // �ڱ� �ڽ��� ����Ű�� ���� ����
			return;
		}

		Node_SL* temp = head_age;

		while (temp->next_age != head_age)
		{
			temp = temp->next_age;
		}
		temp->next_age = current;
		current->next_age = head_age;  // ���ο� ����� ������ head�� �̾���
	}


	void SortByID()
	{
		Node_SL* current;
		Node_SL* prev;
		int swapped;
		do
		{
			current = head_id;
			prev = NULL;
			swapped = 0;

			do
			{
				Node_SL* nextNode = current->next_id;
				if (current->id < nextNode->id)
				{
					swapped = 1;
					if (!prev)
					{
						head_id = nextNode;
						current->next_id = nextNode->next_id;
						nextNode->next_id = current;
						prev = head_id;
					}
					else
					{
						prev->next_id = nextNode;
						current->next_id = nextNode->next_id;
						nextNode->next_id = current;
						prev = nextNode;
					}
				}
				else
				{
					prev = current;
					current = current->next_id;
				}
			} while (current->next_id != head_id);
		} while (swapped);
	}
	void SortByAge()
	{
		Node_SL* current;
		Node_SL* prev;
		int swapped;
		do
		{
			current = head_age;
			prev = NULL;
			swapped = 0;

			do
			{
				Node_SL* nextNode = current->next_age;
				if (current->age < nextNode->age)
				{
					swapped = 1;
					if (!prev)
					{
						head_age = nextNode;
						current->next_age = nextNode->next_age;
						nextNode->next_age = current;
						prev = head_age;
					}
					else
					{
						prev->next_age = nextNode;
						current->next_age = nextNode->next_age;
						nextNode->next_age = current;
						prev = nextNode;
					}
				}
				else
				{
					prev = current;
					current = current->next_age;
				}
			} while (current->next_age != head_age);
		} while (swapped);
	}

	void PrintAll_SL_ID()
	{
		if (head_id == nullptr) return;

		Node_SL* temp = head_id;
		do {
			cout << "�̸�: " << temp->name
				<< " \t����: " << temp->age
				<< " \tID: " << temp->id
				<< " \t�Ҽ�: " << temp->depart
				<< " \t����: " << temp->score << endl;
			temp = temp->next_id;
		} while (temp != head_id);
	}
	void PrintAll_SL_Age()
	{
		if (head_age == nullptr) return;

		Node_SL* temp = head_age;
		do {
			cout << "�̸�: " << temp->name
				<< " \t����: " << temp->age
				<< " \tID: " << temp->id
				<< " \t�Ҽ�: " << temp->depart
				<< " \t����: " << temp->score << endl;
			temp = temp->next_age;
		} while (temp != head_age);
	}
};

void scandata(loldic& table, loldic_SL& table_SL)
{
	string name, id;
	int age, depart, score;

	ifstream fin("LOLDic.txt");

	while (fin >> name >> age >> id >> depart >> score)
	{
		table.insert(name, age, id, depart, score);
		table_SL.insert_ID(name, age, id, depart, score);
		table_SL.insert_Age(name, age, id, depart, score);
	}

	//table_SL.SortByID();
	//table_SL.SortByAge();

	cout << "�߰� �Ϸ�!" << endl;
	fin.close();
}

int main()
{
	loldic table;
	loldic_SL table_SL;
	string input;

	scandata(table, table_SL);

	while (true)
	{
		cout << "��ɾ� �Է�: ";
		cin >> input;

		if (input == "PrintAll_R")
		{
			table.PrintAllReversed();
		}
		else if (input == "PrintAll")
		{
			table.PrintAll();
		}
		else if (input == "PrintAll_SL_ID")
		{
			table_SL.PrintAll_SL_ID();
		}
		else if (input == "PrintAll_SL_Age")
		{
			table_SL.PrintAll_SL_Age();
		}
		else
		{
			cout << "��ɾ����!" << endl;
		}

	}
	return 0;
}