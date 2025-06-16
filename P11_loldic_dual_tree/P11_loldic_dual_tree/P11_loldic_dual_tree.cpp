#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <Windows.h>

using namespace std;

struct Node 
{
    string position;
    string name;
    int hp, atk, def;
    Node* left;
    Node* right;

    Node(string pos, string n, int h, int a, int d)
        : position(pos), name(n), hp(h), atk(a), def(d), left(nullptr), right(nullptr) 
    {}
};

int scan_count;

class LoldicBST 
{
private:
    Node* root;

    Node* insert(Node* current, string pos, string name, int hp, int atk, int def) 
    {
        if (!current) 
        {
            scan_count++;
            if (scan_count % 10000 == 0)
            {
                cout << scan_count << "�� �Է¿Ϸ�!" << endl;
            }
            return new Node(pos, name, hp, atk, def);
        }
        if (name < current->name) 
        {
            current->left = insert(current->left, pos, name, hp, atk, def);
        }
        else if (name > current->name) 
        {
            current->right = insert(current->right, pos, name, hp, atk, def);
        }
        else
        {
            cout << "�̹� ���� �̸��� �ֽ��ϴ�!\n";
        }
        return current;
    }

    Node* searchByName(Node* current, const string& name) 
    {
        if (!current) return nullptr;
        if (name == current->name) return current;
        if (name < current->name) return searchByName(current->left, name);
        return searchByName(current->right, name);
    }

    Node* findMin(Node* current) 
    {
        while (current && current->left) 
        {
            current = current->left;
        }
        return current;
    }

    Node* deleteNode(Node* current, const string& name) 
    {
        if (!current) return nullptr;

        if (name < current->name) 
        {
            current->left = deleteNode(current->left, name);
        }
        else if (name > current->name)
        {
            current->right = deleteNode(current->right, name);
        }
        else 
        {
            // ������ ��带 ã��
            if (!current->left && !current->right) 
            {
                delete current;
                return nullptr;
            }
            else if (!current->left) 
            {
                Node* temp = current->right;
                delete current;
                return temp;
            }
            else if (!current->right)
            {
                Node* temp = current->left;
                delete current;
                return temp;
            }
            else 
            {
                Node* minNode = findMin(current->right);
                current->name = minNode->name;
                current->position = minNode->position;
                current->hp = minNode->hp;
                current->atk = minNode->atk;
                current->def = minNode->def;
                current->right = deleteNode(current->right, minNode->name);
            }
        }
        return current;
    }

    void inorder(Node* current) 
    {
        if (!current) return;
        inorder(current->left);
        cout << "[" << current->position << "] " << current->name
            << " | HP: " << current->hp
            << " | ATK: " << current->atk
            << " | DEF: " << current->def << endl;
        inorder(current->right);
    }

public:
    LoldicBST() : root(nullptr) {}

    void insert(string pos, string name, int hp, int atk, int def) 
    {
        root = insert(root, pos, name, hp, atk, def);
    }

    void searchByName(string name) 
    {
        Node* result = searchByName(root, name);
        if (result) 
        {
            cout << name << " �߰�! HP: " << result->hp << ", ATK: " << result->atk << ", DEF: " << result->def << endl;
        }
        else 
        {
            cout << name << " �� ã��.\n";
        }
    }

    void deleteByName(string name) 
    {
        root = deleteNode(root, name);
    }

    void printAll() 
    {
        cout << "=== ���� ���̺� ��� ===\n";
        inorder(root);
    }

    void scandata()
    {
        char cwd[MAX_PATH];
        GetCurrentDirectoryA(MAX_PATH, cwd);
        cout << "���� �۾� ���丮: " << cwd << endl;

        string name, pos;
        int hp, ad, df;

        ifstream fin("LOLDic.txt");  // ���� ����
        if (!fin.is_open()) 
        {
            std::cerr << "���� ���� ����" << endl;
            return;
        }

        while (fin >> pos >> name >> hp >> ad >> df)
        {
            insert(pos, name, hp, ad, df);
            // ���⼭ loldic�� insert �Լ� ȣ�� ����
        }

        cout << "�Է� �Ϸ�!" << endl;
        fin.close();
        return;
    }

    void Insert_BT()
    {
        string vname;
        string vpos;
        int vhp, vad, vdf;

        while (true)
        {
            cout << "è�Ǿ� �̸�: ";
            cin >> vname;
            if (vname.length() > 0)
            {
                break;
            }
            else
            {
                cout << "�Է� ����!" << endl; 
                continue;
            }
        }
        while (true)
        {
            cout << "������ �Է�: ";
            cin >> vpos;
            if (vpos == "TOP" || vpos == "JUNGLE" || vpos == "MID" || vpos == "ADCARRY" || vpos == "SUPPORTER")
            {
                continue;
            }
            else
            {
                cout << "�Է� ����!" << endl;
                break;
            }
        }
        while (true)
        {
            cout << "hp �Է�: ";
            
            if (cin >> vhp)
            {
                break;
            }
            else
            {
                cout << "�Է� ����!" << endl;
                continue;
            }
        }
        while (true)
        {
            cout << "ad �Է�: ";

            if (cin >> vad)
            {
                break;
            }
            else
            {
                cout << "�Է� ����!" << endl;
                continue;
            }
        }
        while (true)
        {
            cout << "df �Է�: ";

            if (cin >> vdf)
            {
                break;
            }
            else
            {
                cout << "�Է� ����!" << endl;
                continue;
            }
        }

        insert(vpos, vname, vhp, vad, vdf);

        cout << vname << "�߰� �Ϸ�!" << endl;
    }
};

int main()
{
    LoldicBST table;
    string input;
    string cmd;
    string vname;

    table.scandata();

    while (true)
    {
        cout << "��ɾ� �Է�: ";
        getline(cin, input);

        if (sscanf_s(input.c_str(), "%s %s", cmd, sizeof(cmd), vname, sizeof(vname)) >= 2)
        {
            if (cmd == "SearchByName_BT")
            {
                table.searchByName(vname);
            }
            else if (cmd == "SearchByName_BT")
            {
                table.searchByName(vname);
            }
        }
        if (input == "PrintAll_BT")
        {
            table.printAll();
        }
        else if (cmd == "Insert_BT")
        {
            table.Insert_BT();
        }
        else if (cmd == "SortByName_BT")
        {
        }
        else
        {
            cout << "��ɾ� ����!" << endl;
        }
    }

    return 0;
}
