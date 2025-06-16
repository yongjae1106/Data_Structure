#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

struct Node
{
	string name;
	string id;
	int age, depart, score;
	Node* left;
	Node* right;

	Node(string n, int a, string i, int d, int s) : name(n), age(a), id(i), depart(d), score(s), left(nullptr), right(nullptr) {}
};
struct Node_SL
{
	string name;
	string id;
	int age, depart, score;
	Node_SL* next_id;
	Node_SL* next_age;

	Node_SL(string n, int a, string i, int d, int s) : name(n), age(a), id(i), depart(d), score(s), next_id(nullptr), next_age(nullptr) {}
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
		else if (current->id < id)
		{
			current->right = insert(current->right, name, age, id, depart, score);
		}
		else if (current->id > id)
		{
			current->left = insert(current->left, name, age, id, depart, score);
		}
		else
		{
			cout << "같은 Id인 데이터가 존재합니다!\n";
		}
		return current;
	}

	void inorder(Node* current)
	{
		if (!current) return;
		inorder(current->left);
		cout << "이름: " << current->name
			<< " 나이: " << current->age
			<< " ID: " << current->id
			<< " 소속: " << current->depart
			<< " 점수: " << current->score
			<< endl;
		count++;
		inorder(current->right);
	}
	void inorder_R(Node* current)
	{
		if (!current) return;
		inorder_R(current->right);
		cout << "이름: " << current->name
			<< " 나이: " << current->age
			<< " ID: " << current->id
			<< " 소속: " << current->depart
			<< " 점수: " << current->score
			<< endl;
		count_r++;
		inorder_R(current->left);
	}
public:
	dic() : root(nullptr), count(0), count_r(0) {}

	int count;
	int count_r;

	void insert(string name, int age, string id, int depart, int score)
	{
		root = insert(root, name, age, id, depart, score);
	}

	void PrintAll()
	{
		count = 0;
		inorder(root);
		cout << count << "개 출력" << endl;
	}
	void PrintAll_R()
	{
		count_r = 0;
		inorder_R(root);
		cout << count_r << "개 출력" << endl;
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

	void SortByID()
	{
		if (!head_id || head_id->next_id == head_id) return; // 0 or 1 노드

		// Step 1: 원형 링크 끊기
		Node_SL* last = head_id;
		while (last->next_id != head_id)
		{
			last = last->next_id;
		}
		last->next_id = nullptr; // 끊기

		// Step 2: 일반 버블 정렬
		bool swapped;
		do 
		{
			swapped = false;
			Node_SL* prev = nullptr;
			Node_SL* curr = head_id;
			Node_SL* next = nullptr;

			while (curr && curr->next_id) 
			{
				next = curr->next_id;
				if (curr->id > next->id) 
				{
					// Swap
					swapped = true;

					if (prev) 
					{
						prev->next_id = next;
					}
					else 
					{
						head_id = next;
					}
					curr->next_id = next->next_id;
					next->next_id = curr;

					prev = next;
				}
				else 
				{
					prev = curr;
					curr = curr->next_id;
				}
			}
		} while (swapped);

		// Step 3: 원형 링크 복원
		Node_SL* temp = head_id;
		while (temp->next_id)
		{
			temp = temp->next_id;
		}
		temp->next_id = head_id; // 다시 원형으로
	}
	void SortByAge()
	{
		if (!head_age || head_age->next_age == head_age) return;

		Node_SL* last = head_age;
		while (last->next_age != head_age)
		{
			last = last->next_age;
		}
		last->next_age = nullptr;

		bool swapped = false;

		do
		{
			Node_SL* prev = nullptr;
			Node_SL* curr = head_age;
			Node_SL* next = nullptr;
			swapped = false;

			while (curr && curr->next_age)
			{
				next = curr->next_age;
				if(curr->age > next->age)
				{
					swapped = true;
					if (prev)
					{
						prev->next_age = next;
					}
					else
					{
						head_age = next;
					}
					curr->next_age = next->next_age;
					next->next_age = curr;

					prev = next;
				}
				else
				{
					prev = curr;
					curr = curr->next_age;
				}
			}
		} while (swapped);

		Node_SL* temp = head_age;
		while (temp->next_age)
		{
			temp = temp->next_age;
		}
		temp->next_age = head_age;
	}

	void PrintAll_SL_ID()
	{
		Node_SL* current = head_id;
		do
		{
			cout << "이름: " << current->name
				<< " 나이: " << current->age
				<< " ID: " << current->id
				<< " 소속: " << current->depart
				<< " 점수: " << current->score
				<< endl;
			count_id++;
			current = current->next_id;
		} while (current->next_id != head_id);
	}
	void PrintAll_SL_Age()
	{
		Node_SL* current = head_age;
		do
		{
			cout << "이름: " << current->name
				<< " 나이: " << current->age
				<< " ID: " << current->id
				<< " 소속: " << current->depart
				<< " 점수: " << current->score
				<< endl;
			count_age++;
			current = current->next_age;
		} while (current->next_age != head_age);
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

	fin.close();

	table_SL.SortByAge();
	table_SL.SortByID();
	cout << "추가 완료!" << endl;
}

int main()
{
	dic table;
	dic_SL table_SL;
	string input;

	scandata(table, table_SL);

	while (true)
	{
		cout << "명령어입력: ";
		cin >> input;
		if (input == "PrintAll_R")
		{
			table.PrintAll_R();
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
			cout << "명령어오류!" << endl;
		}
	}
}