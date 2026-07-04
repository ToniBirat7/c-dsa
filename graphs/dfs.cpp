#include <iostream>
#include <vector>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjList;

public:
    Graph(int size) {
        V = size;
        adjList.resize(size);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v); // Directed
    }
};

int main() {
    return 0;
}