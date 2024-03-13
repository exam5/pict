#include <iostream>
#include <string>
using namespace std;

class Entry {
public:
    long int number;
    string name;

    Entry(long int number_ = -1, string name_ = "----------") : number(number_), name(name_) {}
};

class HashTable {
private:
    int size;
    Entry *data;

    int hashFunction(long int key) {
        return key % size;
    }

public:
    HashTable(int size_ = 10) : size(size_) {
        data = new Entry[size];
    }

    void insertWithoutReplacement(const Entry& newEntry) {
        int hc = hashFunction(newEntry.number);
        int temp = hc;
        while (data[temp].number != -1 && temp != hc + 1) {
            temp = (temp + 1) % size;
        }
        if (temp != hc + 1) {
            data[temp] = newEntry;
        } else {
            cout << "HashTable is full." << endl;
        }
    }

    void insertWithReplacement(const Entry& newEntry) {
        int hc = hashFunction(newEntry.number);
        if (data[hc].number == -1 || hashFunction(data[hc].number) != hc) {
            data[hc] = newEntry;
        } else {
            Entry retrieve = data[hc];
            data[hc] = newEntry;
            insertWithReplacement(retrieve);
        }
    }

    int search(long int key) {
        int hc = hashFunction(key);
        int temp = hc;
        while (data[temp].number != key && data[temp].number != -1 && temp != hc + 1) {
            temp = (temp + 1) % size;
        }
        if (data[temp].number == key) {
            cout << "Element found at position: " << temp << endl;
            return temp;
        } else {
            cout << "Element not found." << endl;
            return -1;
        }
    }

    void update(long int key, long number_, const string& name_) {
        int loc = search(key);
        if (loc != -1) {
            data[loc].number = number_;
            data[loc].name = name_;
        }
    }

    void displayTable() {
        for (int i = 0; i < size; i++) {
            cout << i << " " << data[i].number << " " << data[i].name << endl;
        }
    }

    void deleteElem(long int key) {
        int loc = search(key);
        if (loc != -1) {
            data[loc].number = -1;
            data[loc].name = "----------";
        }
    }

    ~HashTable() {
        delete[] data;
    }
};

int main() {
    int size = 0;
    cout << "Enter the size of the hash table: ";
    cin >> size;
    HashTable H(size);

    int menu;
    while (true) {
        cout << "\n\nSelect an option:\n1) Insert with replacement\n2) Insert without replacement\n3) Search\n4) Update\n5) Delete\n6) Display\n0) Exit\n";
        cin >> menu;
        switch (menu) {
            case 1: {
                long int number_;
                string name_;
                cout << "\nEnter the number: ";
                cin >> number_;
                cout << "Enter the name: ";
                cin >> name_;
                H.insertWithReplacement(Entry(number_, name_));
                break;
            }
            case 2: {
                long int number_;
                string name_;
                cout << "\nEnter the number: ";
                cin >> number_;
                cout << "Enter the name: ";
                cin >> name_;
                H.insertWithoutReplacement(Entry(number_, name_));
                break;
            }
            case 3: {
                long int number_;
                cout << "\nEnter the key you want to search: ";
                cin >> number_;
                H.search(number_);
                break;
            }
            case 4: {
                long int keynumber_, number_;
                string name_;
                cout << "\nEnter the key you want to update: ";
                cin >> keynumber_;
                cout << "Enter the new number: ";
                cin >> number_;
                cout << "Enter the new name: ";
                cin >> name_;
                H.update(keynumber_, number_, name_);
                break;
            }
            case 5: {
                long int keynumber_;
                cout << "\nEnter the key you want to delete: ";
                cin >> keynumber_;
                H.deleteElem(keynumber_);
                break;
            }
            case 6:
                H.displayTable();
                break;
            case 0:
                return 0;
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
    }
}
