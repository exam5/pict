#include <iostream>
#include <vector>
using namespace std;

class Node
{
    string word;
    vector<string> meaning;
    Node *lchild;
    Node *rchild;

public:
    Node(const string &word) : word(word), lchild(nullptr), rchild(nullptr) {}

    friend class Tree;
};

class Tree
{
    Node *root;

    void addNode(Node *&root, const string &word, const string &meaning);
    void display(Node *root);
    void updateMeaning(Node *root, const string &keyword);
    Node *deleteNode(Node *root, const string &key);
    Node *findMin(Node *node);

public:
    Tree() : root(nullptr) {}

    void addKeyword();
    void display();
    void update();
    void deleteKeyword();
};

void Tree::addNode(Node *&root, const string &word, const string &meaning)
{
    if (!root)
    {
        root = new Node(word);
        root->meaning.push_back(meaning);
    }
    else if (word < root->word)
    {
        addNode(root->lchild, word, meaning);
    }
    else if (word > root->word)
    {
        addNode(root->rchild, word, meaning);
    }
    else
    {
        root->meaning.push_back(meaning);
    }
}

void Tree::addKeyword()
{
    string keyword, meaning;
    cout << "Enter keyword: ";
    cin >> keyword;
    cout << "Enter meaning: ";
    cin.ignore();
    getline(cin, meaning);
    addNode(root, keyword, meaning);
}

void Tree::display(Node *root)
{
    if (root)
    {
        display(root->lchild);
        cout << "-----------\n";
        cout << "Keyword: " << root->word << "\n";
        cout << "Meanings: \n";
        for (const auto &meaning : root->meaning)
        {
            cout << " " << meaning << endl;
        }
        cout << "-------------\n";
        display(root->rchild);
    }
}

void Tree::display()
{
    display(root);
}

void Tree::updateMeaning(Node *root, const string &keyword)
{
    if (!root)
    {
        cout << "Keyword not found!" << endl;
        return;
    }

    if (root->word == keyword)
    {
        string updatedMeaning;
        cout << "Enter updated meaning: ";
        cin.ignore();
        getline(cin, updatedMeaning);
        root->meaning.clear();
        root->meaning.push_back(updatedMeaning);
        cout << "Meaning updated successfully!" << endl;
        return;
    }

    if (keyword < root->word)
    {
        updateMeaning(root->lchild, keyword);
    }
    else
    {
        updateMeaning(root->rchild, keyword);
    }
}


void Tree::update()
{
    string keyword;
    cout << "Enter keyword to update: ";
    cin >> keyword;
    updateMeaning(root, keyword);
}

Node *Tree::deleteNode(Node *root, const string &key)
{
    if (!root)
    {
        return root;
    }

    if (key < root->word)
    {
        root->lchild = deleteNode(root->lchild, key);
    }
    else if (key > root->word)
    {
        root->rchild = deleteNode(root->rchild, key);
    }
    else
    {
        if (!root->lchild)
        {
            Node *temp = root->rchild;
            delete root;
            return temp;
        }
        else if (!root->rchild)
        {
            Node *temp = root->lchild;
            delete root;
            return temp;
        }
        Node *temp = findMin(root->rchild);
        root->word = temp->word;
        root->rchild = deleteNode(root->rchild, temp->word);
    }
    return root;
}

Node *Tree::findMin(Node *node)
{
    Node *current = node;
    while (current->lchild)
    {
        current = current->lchild;
    }
    return current;
}

void Tree::deleteKeyword()
{
    string keyword;
    cout << "Enter keyword to delete: ";
    cin >> keyword;
    root = deleteNode(root, keyword);
}

int main()
{
    Tree t;
    int choice;

    do
    {
        cout << "1. Add keyword\n"
             << "2. Display\n"
             << "3. Update keyword\n"
             << "4. Delete keyword\n"
             << "0. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            t.addKeyword();
            break;
        case 2:
            t.display();
            break;
        case 3:
            t.update();
            break;
        case 4:
            t.deleteKeyword();
            break;
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    return 0;
}
