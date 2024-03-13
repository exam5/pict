#include <iostream>
#include <stack>
using namespace std;

class Node {
    int data;
    Node* left;
    Node* right;
    bool rthread;
    bool lthread;

public:
    Node() {
        data = 0;
        left = nullptr;
        right = nullptr;
        rthread = false;
        lthread = false;
    }

    friend class TBST;
};

class TBST {
    Node* root;

    void inorder();
    void preorder();
    void deleteNode(Node* par, Node* curr);

public:
    TBST() {
        root = nullptr;
    }

    void make();
    void traversal(int c);
    void removeNode();
};

void TBST::make() {
    cout << "Enter data: ";
    int d;
    cin >> d;
    Node* newnode = new Node;
    newnode->data = d;

    if (!root) {
        root = newnode;
        root->lthread = true;
        root->rthread = true;
    } else {
        Node* temp = root;
        while (1) {
            if (temp->data > newnode->data) {
                if (temp->lthread) {
                    newnode->right = temp;
                    newnode->left = temp->left;
                    temp->left = newnode;
                    newnode->rthread = true;
                    newnode->lthread = temp->lthread;
                    temp->lthread = false;
                    break;
                } else {
                    temp = temp->left;
                }
            } else {
                if (temp->rthread) {
                    newnode->right = temp->right;
                    newnode->left = temp;
                    temp->right = newnode;
                    newnode->rthread = temp->rthread;
                    newnode->lthread = true;
                    temp->rthread = false;
                    break;
                } else {
                    temp = temp->right;
                }
            }
        }
    }
}

void TBST::inorder() {
    if (!root) {
        cout << "TBST is empty" << endl;
        return;
    }

    Node* temp = root;
    while (!temp->lthread) {
        temp = temp->left;
    }

    while (temp) {
        cout << temp->data << " ";

        if (temp->rthread) {
            temp = temp->right;
        } else {
            temp = temp->right;
            while (!temp->lthread) {
                temp = temp->left;
            }
        }
    }
    cout << endl;
}


void TBST::preorder() {
    if (root == nullptr) {
        cout << "TBST is empty" << endl;
        return;
    }

    Node* ptr = root;
    while (ptr != nullptr) {
        cout << ptr->data << endl;

        if (ptr->lthread == false) {
            ptr = ptr->left;
        } else if (ptr->rthread == false) {
            ptr = ptr->right;
        } else {
            while (ptr != nullptr && ptr->rthread == true) {
                ptr = ptr->right;
            }
            if (ptr != nullptr) {
                ptr = ptr->right;
            }
        }
    }
}

void TBST::traversal(int c) {
    if (!root) {
        cout << "Tree is empty!" << endl;
        return;
    }

    if (c == 2) {
        this->inorder();
    } else if (c == 3) {
        this->preorder();
    }
}

void TBST::removeNode() {
    int c;
    cout << "Enter node to be deleted: ";
    cin >> c;
    Node* par = nullptr;
    Node* curr = root;
    bool flag = false;

    do {
        if (curr->data > c) {
            if (curr->lthread) {
                break;
            } else {
                par = curr;
                curr = curr->left;
            }
        } else if (curr->data < c) {
            if (curr->rthread) {
                break;
            } else {
                par = curr;
                curr = curr->right;
            }
        }
        if (curr->data == c) {
            flag = true;
            break;
        }
    } while (!curr->lthread || !curr->rthread);

    if (flag) {
        deleteNode(par, curr);
    }
}

void TBST::deleteNode(Node* par, Node* curr) {
    if (curr->lthread && curr->rthread) {
        if (curr == root) {
            root = nullptr;
        } else if (par->left == curr) {
            par->lthread = true;
            par->left = curr->left;
        } else {
            par->rthread = true;
            par->right = curr->right;
        }
        delete curr;
    } else if (!curr->lthread) {
        Node* child;
        if (par->left == curr) {
            par->left = curr->left;
            par = par->left;
        } else {
            par->right = curr->left;
            par = par->right;
        }
        while (!par->rthread) {
            par = par->right;
        }
        par->right = curr->right;
        delete curr;
    } else {
        if (par->left == curr) {
            par->left = curr->right;
            par = par->left;
        } else {
            par->right = curr->right;
            par = par->right;
        }
        while (!par->lthread) {
            par = par->left;
        }
        par->left = curr->left;
        delete curr;
    }
}

int main() {
    TBST t;
    int choice;
    bool f = true;

    while (f) {
        cout << "Enter 1 to enter value\n";
        cout << "Enter 2 to get inorder traversal\n";
        cout << "Enter 3 to get preorder traversal\n";
        cout << "Enter 4 to delete tree\n";
        cout << "Enter 0 to exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 0:
                f = false;
                break;
            case 1:
                t.make();
                break;
            case 2:
            case 3:
                t.traversal(choice);
                break;
            case 4:
                t.removeNode();
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
