#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <stack>
#include <map>
using namespace std;

class Node {
public:
    string data;
    Node* next;
    Node(const string& data_) : data(data_), next(nullptr) {}
};

class Graph {
private:
    map<string, Node*> vertices;

    Node* createNode(const string& data) {
        return new Node(data);
    }

public:
    ~Graph() {
        for (auto& pair : vertices) {
            Node* current = pair.second;
            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }
    }

    void addEdge(const string& src, const string& dest) {
        if (vertices.find(src) == vertices.end()) {
            vertices[src] = createNode(src);
        }
        if (vertices.find(dest) == vertices.end()) {
            vertices[dest] = createNode(dest);
        }
        Node* newNode = createNode(dest);
        newNode->next = vertices[src]->next;
        vertices[src]->next = newNode;
    }

    void display() {
        for (const auto& pair : vertices) {
            Node* current = pair.second;
            cout << current->data;
            current = current->next;
            while (current != nullptr) {
                cout << " -> " << current->data;
                current = current->next;
            }
            cout << endl;
        }
    }

    void DFS(const string& start) {
        set<string> visited;
        stack<string> stk;
        stk.push(start);
        while (!stk.empty()) {
            string current = stk.top();
            stk.pop();
            if (visited.find(current) == visited.end()) {
                cout << current << " ";
                visited.insert(current);
                Node* temp = vertices[current]->next;
                while (temp != nullptr) {
                    stk.push(temp->data);
                    temp = temp->next;
                }
            }
        }
        cout << endl;
    }

    void BFS(const string& start) {
        set<string> visited;
        queue<string> que;
        que.push(start);
        while (!que.empty()) {
            string current = que.front();
            que.pop();
            if (visited.find(current) == visited.end()) {
                cout << current << " ";
                visited.insert(current);
                Node* temp = vertices[current]->next;
                while (temp != nullptr) {
                    que.push(temp->data);
                    temp = temp->next;
                }
            }
        }
        cout << endl;
    }
};

int main() {
    Graph g;
    int edges;
    cout << "Enter number of edges: ";
    cin >> edges;
    cout << "Enter connections in format 'source destination':" << endl;
    for (int i = 0; i < edges; ++i) {
        string src, dest;
        cin >> src >> dest;
        g.addEdge(src, dest);
    }

    cout << "Adjacency list of the graph:" << endl;
    g.display();

    string startVertex;
    cout << "Enter starting vertex for DFS and BFS: ";
    cin >> startVertex;

    cout << "DFS traversal: ";
    g.DFS(startVertex);

    cout << "BFS traversal: ";
    g.BFS(startVertex);

    return 0;
}
