#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

struct Node
{
	string name;
	string id;
	int age;
	int depart;
	int score;
	Node* left;
	Node* right;

	Node(string n, int a, string i, int d, int s) : name(n), id(i), age(a), depart(d), score(s), left(nullptr), right(nullptr) {}
};
struct Node_SL
{
	string name;
	string id;
	int age, depart, score;

	Node_SL* next_id;
	Node_SL* next_age;

	Node_SL(string _name, int _age, string _id, int _depart, int _score) : name(_name), age(_age), id(_id), depart(_depart), score(_score), next_id(nullptr), next_age(nullptr)
	{ }
};


class dic
{
private:
	Node* root;

	Node* insert(Node* current, string name, int age, string id, int depart, int score)
	{
		if (!current)
		{
			return new Node(name, age, id, depart, score);
		}
		else if (current->id > id)
		{
			current->left = insert(current->left, name, age, id, depart, score);
		}
		else if (current->id < id)
		{
			current->right = insert(current->right, name, age, id, depart, score);
		}
		else
		{
			cout << "ID가 같습니다!" << endl;
		}

		return current;
	}

	void inorder(Node* current)
	{
		if (!current) return;
		inorder(current->left);
		cout << " 이름: " << current->name
			<< " 나이: " << current->age
			<< " ID: " << current->id
			<< " 소속: " << current->depart
			<< " 점수: " << current->score
			<< endl;
		print_count++;
		inorder(current->right);
	}
	void reverse_inorder(Node* current)
	{
		if (!current) return;

		reverse_inorder(current->right);
		cout << " 이름: " << current->name
			<< " 나이: " << current->age
			<< " ID: " << current->id
			<< " 소속: " << current->depart
			<< " 점수: " << current->score
			<< endl;
		print_R_count++;
		reverse_inorder(current->left);
	}

public:
	dic() : root(nullptr) {}

	int print_count;
	int print_R_count;

	void insert(string name, int age, string id, int depart, int score)
	{
		root = insert(root, name, age, id, depart, score);
	}

	void PrintAll_R()
	{
		print_R_count = 0;
		reverse_inorder(root);
		cout << print_R_count << "개 출력" << endl;
	}
	void PrintAll()
	{
		print_count = 0;
		inorder(root);
		cout << print_count << "개 출력" << endl;
	}
};
class dic_SL
{
private:
	Node_SL* head_id;
	Node_SL* head_age;
public:
	dic_SL() : head_id(nullptr), head_age(nullptr), count_id(0), count_age(0) {}
	int count_id;
	int count_age;

	void insert_id(string name, int age, string id, int depart, int score)
	{
		Node_SL* newNode = new Node_SL(name, age, id, depart, score);

		if (!head_id)
		{
			head_id = newNode;
			head_id->next_id = head_id;
			return;
		}

		Node_SL* temp = head_id;
		while (temp->next_id != head_id)
		{
			temp = temp->next_id;
		} 
		temp->next_id = newNode;
		newNode->next_id = head_id;
	}
	void insert_age(string name, int age, string id, int depart, int score)
	{
		Node_SL* newNode = new Node_SL(name, age, id, depart, score);

		if (!head_age)
		{
			head_age = newNode;
			head_age->next_age = head_age;
			return;
		}

		Node_SL* temp = head_age;
		while (temp->next_age != head_age)
		{
			temp = temp->next_age;
		}
		temp->next_age = newNode;
		newNode->next_age = head_age;
	}

	void sortbyID()
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
	void sortbyAge()
	{
		Node_SL* current;
		Node_SL* prev;
		int swapped;

		do
		{
			current = head_age;
			swapped = 0;
			prev = NULL;

			do
			{
				Node_SL* nextNode = current->next_age;
				if (current->id < nextNode->id)
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
		if (!head_id) return;

		Node_SL* current = head_id;
		count_id = 0;
		do
		{
			cout << "이름: " << current->name
				<< "나이: " << current->age
				<< "ID: " << current->id
				<< "소속: " << current->depart
				<< "점수: " << current->score
				<< endl;
			count_id++;
			current = current->next_id;
		} while (current != head_id);

		cout << count_id << "개 출력" << endl;
	}
	void PrintAll_SL_Age()
	{
		if (!head_age) return;

		Node_SL* current = head_age;
		count_age = 0;
		do
		{
			cout << "이름: " << current->name
				<< "나이: " << current->age
				<< "ID: " << current->id
				<< "소속: " << current->depart
				<< "점수: " << current->score
				<< endl;
			count_age++;
			current = current->next_age;
		} while (current != head_age);

		cout << count_age << "개 출력" << endl;
	}
};

void scandata(dic& table, dic_SL& table_SL)
{
	string name, id;
	int age, depart, score;

	ifstream fin("LOLDic.txt");

	while (fin >> name >> age >> id >> depart >> score)
	{
		table.insert(name, age, id, depart, score);
		table_SL.insert_id(name, age, id, depart, score);
		table_SL.insert_age(name, age, id, depart, score);
	}

	table_SL.sortbyAge();
	table_SL.sortbyID();

	fin.close();

	cout << "추가 완료!\n";
}

int main()
{
	dic table;
	dic_SL table_SL;
	string input;

	scandata(table, table_SL);

	while (true)
	{
		cout << "명령어 입력: ";
		cin >> input;

		if (input == "PrintAll")
		{
			table.PrintAll();
		}
		else if (input == "PrintAll_R")
		{
			table.PrintAll_R();
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
			cout << "명령어오류!" << endl;
		}
	}
}