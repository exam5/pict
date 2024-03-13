#include <iostream>
using namespace std;

class Node {
public:
    int key;
    string value;
    Node* next;

    Node(int key_ = 0, string value_ = "") : key(key_), value(value_), next(nullptr) {}
};

class Dict {
public:
    Node* arr[10] = { nullptr };

    void insertValue(int key, const string& value) {
        int index = key % 10;
        if (arr[index] == nullptr) {
            arr[index] = new Node(key, value);
        } else {
            Node* temp = arr[index];
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = new Node(key, value);
        }
    }

    void display() {
        for (int i = 0; i < 10; i++) {
            Node* temp = arr[i];
            while (temp != nullptr) {
                cout << "(" << temp->key << "," << temp->value << ")";
                if (temp->next != nullptr) {
                    cout << " -> ";
                }
                temp = temp->next;
            }
            cout << endl;
        }
    }

    void search(int key) {
        int index = key % 10;
        Node* temp = arr[index];
        int comparisons = 1;
        while (temp != nullptr) {
            if (temp->key == key) {
                cout << "(" << temp->key << "," << temp->value << ") found with " << comparisons << " comparisons." << endl;
                return;
            }
            temp = temp->next;
            comparisons++;
        }
        cout << "Key not found." << endl;
    }

    void deleteKey(int key) {
        int index = key % 10;
        Node* temp = arr[index];
        if (temp == nullptr) {
            cout << "Key not found." << endl;
            return;
        }
        if (temp->key == key) {
            arr[index] = temp->next;
            delete temp;
            cout << "Key deleted successfully." << endl;
            return;
        }
        while (temp->next != nullptr && temp->next->key != key) {
            temp = temp->next;
        }
        if (temp->next == nullptr) {
            cout << "Key not found." << endl;
            return;
        }
        Node* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        cout << "Key deleted successfully." << endl;
    }

    ~Dict() {
        for (int i = 0; i < 10; i++) {
            Node* temp = arr[i];
            while (temp != nullptr) {
                Node* toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }
        }
    }
};

int main() {
    Dict dictionary;

    cout << "Enter number of key-value pairs: ";
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int key;
        string value;
        cout << "Enter key " << i + 1 << ": ";
        cin >> key;
        cout << "Enter value " << i + 1 << ": ";
        cin >> value;
        dictionary.insertValue(key, value);
    }

    cout << "\nDictionary Contents:" << endl;
    dictionary.display();
    
    int searchKey;
    cout << "\nEnter key to search: ";
    cin >> searchKey;
    dictionary.search(searchKey);

    int deleteKey;
    cout << "\nEnter key to delete: ";
    cin >> deleteKey;
    dictionary.deleteKey(deleteKey);

    cout << "\nDictionary after deletion:" << endl;
    dictionary.display();

    return 0;
}
