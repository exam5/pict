#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class treenode
{
    int data;
    treenode *lchild;
    treenode *rchild;

public:
    treenode()
    {
        data = 0;
        lchild = NULL;
        rchild = NULL;
    }
    friend class tree;
};

class tree
{
    treenode *root;
    treenode *maketree();
    void inorder(treenode *root);
    void inorder_iterative(treenode *root);
    void preorder(treenode *root);
    void preorder_iterative(treenode *root);
    void postorder(treenode *root);
    void postorder_iterative(treenode *root);
    int leafnode(treenode *root);
    int internalnode(treenode *root);
    int maxdepth(treenode *root);
    void erasetree(treenode *root);
    void mirrortree(treenode *root);
    void copyTree(const treenode *source, treenode *&destination);

public:
    tree()
    {
        root = NULL;
    }
    void create()
    {
        root = maketree();
    }
    void display()
    {
        cout << "inorder traversal : " << endl;
        inorder_iterative(root);
        cout << "preorder traversal : " << endl;
        preorder_iterative(root);
        cout << "postorder traversal : " << endl;
        postorder_iterative(root);
        cout << "the no.of leaf nodes are " << leafnode(root) << endl;
        cout << "max depth of the tree is" << endl;
        cout << maxdepth(root) << endl;
        cout << "the below nodes of the tree are deleted" << endl;
        erasetree(root);
        mirrortree(root);
        cout << "inorder traversal of mirror tree is : " << endl;
        inorder_iterative(root);
    }

    tree &operator=(const tree &other)
    {
        if (this != &other)
        {
            erasetree(root);
            copyTree(other.root, root);
        }
        return *this;
    }
};

treenode *tree::maketree()
{
    treenode *temp;
    temp = new treenode;
    cout << "Enter data: ";
    cin >> temp->data;
    cout << "DO you want to enter left child of " << temp->data << " (y/n):";
    char ch;
    cin >> ch;
    if (ch == 'y')
    {
        temp->lchild = this->maketree();
    };
    cout << "DO you want to enter right child of " << temp->data << " (y/n):";

    cin >> ch;
    if (ch == 'y')
    {
        temp->rchild = this->maketree();
    }

    return temp;
}
void tree ::inorder(treenode *root)
{
    if (root != NULL)
    {
        inorder(root->lchild);
        cout << root->data << endl;
        inorder(root->rchild);
    }
}
void tree ::inorder_iterative(treenode *root)
{
    stack<treenode *> s;
    treenode *curr = root;
    s.push(root);

    while (!s.empty())
    {
        while (curr != NULL)
        {
            s.push(curr);
            curr = curr->lchild;
        }

        curr = s.top();
        s.pop();
        cout << curr->data << endl;
        curr = curr->rchild;
    }
}

void tree ::preorder_iterative(treenode *root)
{
    stack<treenode *> s;
    s.push(root);

    while (s.empty() != true)
    {
        treenode *curr = s.top();
        cout << curr->data << endl;
        s.pop();

        if (curr->rchild)
        {
            s.push(curr->rchild);
        }
        if (curr->lchild)
        {
            s.push(curr->lchild);
        }
    }
}

void tree ::preorder(treenode *root)
{

    if (root != NULL)
    {
        cout << root->data << endl;
        preorder(root->lchild);
        preorder(root->rchild);
    }
}

void tree ::postorder(treenode *root)
{

    if (root != NULL)
    {
        postorder(root->lchild);
        postorder(root->rchild);
        cout << root->data << endl;
    }
}
void tree ::postorder_iterative(treenode *root)
{
    stack<treenode *> s;
    stack<treenode *> result;
    treenode *curr = root;
    s.push(root);

    while (!s.empty())
    {
        // go to the left node
        curr = s.top();
        result.push(curr);
        s.pop();

        if (curr->lchild)
        {
            s.push(curr->lchild);
        }
        if (curr->rchild)
        {
            s.push(curr->rchild);
        }
    }
    // go to the right child
    while (!result.empty())
    {
        curr = result.top();
        cout << curr->data << endl;
        result.pop();
    }
}

int tree ::leafnode(treenode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    if (root->lchild == NULL && root->rchild == NULL)
    {

        return 1;
    }
    else
    {
        int left = leafnode(root->lchild);
        int right = leafnode(root->rchild);
        return left + right;
    }
}
int tree ::internalnode(treenode *root)
{
    if (root == NULL)
    {
        return 0;
    }
    if (root->lchild != NULL && root->rchild != NULL)
    {

        return 1;
    }
    else
    {
        int left = internalnode(root->lchild);
        int right = internalnode(root->rchild);
        return left + right;
    }
}
int tree ::maxdepth(treenode *root)
{
    if (root == NULL)
    {
        return 0;
    }

    int Ldepth = maxdepth(root->lchild);
    int Rdepth = maxdepth(root->rchild);

    if (Ldepth > Rdepth)
    {
        return Ldepth + 1;
    }
    else
    {
        return Rdepth + 1;
    }
}
void tree ::erasetree(treenode *root)
{
    if (root == NULL)
    {
        return;
    }
    // deleting right tree;
    erasetree(root->rchild);
    // deleting left tree;
    erasetree(root->lchild);

    cout << "the deleted node is" << root->data << endl;
    delete root;
}
void tree ::mirrortree(treenode *root)
{
    if (root == NULL)
    {
        return;
    }
    treenode *temp;
    mirrortree(root->rchild);
    mirrortree(root->lchild);

    temp = root->lchild;
    root->lchild = root->rchild;
    root->rchild = temp;
}

void tree::copyTree(const treenode *source, treenode *&destination)
{
    if (source == nullptr)
    {
        destination = nullptr;
        return;
    }

    destination = new treenode();
    destination->data = source->data;
    copyTree(source->lchild, destination->lchild);
    copyTree(source->rchild, destination->rchild);
}

int main()
{
    tree obj;
    obj.create();
    obj.display();

    tree obj2;
    obj2 = obj;

    return 0;
}
