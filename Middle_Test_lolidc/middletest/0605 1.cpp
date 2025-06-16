#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

struct Node
{
	string name;
	string id;
	unsigned int age, depart, score;
	Node* left;
	Node* right;

	Node(string n, int a, string i, int d, int s) : name(n), age(a), id(i), depart(d), score(s), left(nullptr), right(nullptr)
	{}

};

struct Node_SL
{
	string name;
	string id;
	unsigned int age, depart, score;
	Node_SL* next_id;
	Node_SL* next_age;

	Node_SL(string n, int a, string i, int d, int s) : name(n), age(a), id(i), depart(d), score(s), next_id(nullptr), next_age(nullptr)
	{
	}
};

class dic
{
private:
	Node* root;

	Node* insert(Node* curr, string name, int age, string id, int depart, int score)
	{
		if (!curr)
		{
			return new Node(name, age, id, depart, score);
		}
		else if (curr->id > id)
		{
			curr->left = insert(curr->left, name, age, id, depart, score);
		}
		else if (curr->id < id)
		{
			curr->right = insert(curr->right, name, age, id, depart, score);
		}
		else
		{
			cout << "같은 ID의 데이터가 있습니다!\n";
		}
		return curr;
	}

	void inorder(Node* curr)
	{
		if (!curr) return;
		inorder(curr->left);
		cout << "이름: " << curr->name
			<< " 나이: " << curr->age
			<< " ID: " << curr->id
			<< " 소속: " << curr->depart
			<< " 점수: " << curr->score
			<< endl;
		count++;
		inorder(curr->right);
	}
	void inorder_R(Node* curr)
	{
		if (!curr) return;
		inorder_R(curr->right);
		cout << "이름: " << curr->name
			<< " 나이: " << curr->age
			<< " ID: " << curr->id
			<< " 소속: " << curr->depart
			<< " 점수: " << curr->score
			<< endl;
		count_R++;
		inorder_R(curr->left);
	}

public:
	dic() : root(nullptr), count(0), count_R(0) {}

	int count;
	int count_R;

	void insert(string name, int age, string id, int depart, int score)
	{
		root = insert(root, name, age, id, depart, score);
	}

	void PrintAll_R()
	{
		count_R = 0;
		inorder_R(root);
		cout << count_R << "개 출력\n";
	}
	void PrintAll()
	{
		count = 0;
		inorder(root);
		cout << count << "개 출력\n";
	}
};
class dic_SL
{
private:
	Node_SL* head_id;
	Node_SL* head_age;
public:
	dic_SL() : head_id(nullptr), head_age(nullptr), count_ID(0), count_Age(0) {}
	int count_ID;
	int count_Age;

	void insert_ID(string name, int age, string id, int depart, int score)
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
	void insert_Age(string name, int age, string id, int depart, int score)
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
		if (!head_id || head_id->next_id == head_id) return;
		
		Node_SL* last = head_id;
		while (last->next_id != head_id)
		{
			last = last->next_id;
		}
		last->next_id = nullptr;

		bool swapped;
		do
		{
			Node_SL* prev = nullptr;
			Node_SL* curr = head_id;
			Node_SL* next = nullptr;
			swapped = false;
			
			while(curr && curr->next_id)
			{
				next = curr->next_id;
				if (curr->id > next->id)
				{
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

		Node_SL* temp = head_id;
		while (temp->next_id)
		{
			temp = temp->next_id;
		}
		temp->next_id = head_id;
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

		bool swapped;
		do
		{
			Node_SL* prev = nullptr;
			Node_SL* curr = head_age;
			Node_SL* next = nullptr;
			swapped = false;

			while (curr && curr->next_age)
			{
				next = curr->next_age;

				if (curr->age > next->age)
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
		Node_SL* curr = head_id;

		do
		{
			cout << "이름: " << curr->name
				<< " 나이: " << curr->age
				<< " ID: " << curr->id
				<< " 소속: " << curr->depart
				<< " 점수: " << curr->score
				<< endl;
			count_ID++;
			curr = curr->next_id;
		} while (curr != head_id);

		cout << count_ID << "개 출력\n";
	}
	void PrintAll_SL_Age()
	{
		Node_SL* curr = head_age;

		do
		{
			cout << "이름: " << curr->name
				<< " 나이: " << curr->age
				<< " ID: " << curr->id
				<< " 소속: " << curr->depart
				<< " 점수: " << curr->score
				<< endl;
			count_Age++;
			curr = curr->next_age;
		} while (curr != head_age);

		cout << count_Age << "개 출력\n";
	}
};

void scandata(dic& table, dic_SL& table_SL)
{
	string name, id;
	unsigned int age, depart, score;

	ifstream fin("LOLDic.txt");

	while (fin >> name >> age >> id >> depart >> score)
	{
		table.insert(name, age, id, depart, score);
		table_SL.insert_ID(name, age, id, depart, score);
		table_SL.insert_Age(name, age, id, depart, score);
	}
	table_SL.SortByAge();
	table_SL.SortByID();

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
		cout << "명령어입력: ";
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
			cout << "명령어오류!\n";
		}
	}

}