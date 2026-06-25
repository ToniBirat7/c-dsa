#include <iostream>
#include <vector>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjList;
   
public:
    Graph(int vertices) {
        V = vertices;
        adjList.resize(V);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

        // Print the representation
    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << "Vertex " << i << " is connected to: ";
            for (int neighbour : adjList[i]) {
                cout << neighbour << " ";
            }
            cout << "\n";
        }
    }
};

int main () {
    return 0;
}