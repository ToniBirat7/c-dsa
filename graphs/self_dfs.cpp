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

    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << "Neighbour of Node " << i << ": ";

            for (int neighbour : adjList[i]) {
                cout << neighbour << " ";
            }

            cout << "\n";
        }
    }

    void dfs(int u,vector<bool> &visitedNode) {
        visitedNode[u] = true;

        cout << u << " ";

        for (int v : adjList[u]) {
            if (!visitedNode[v]) {
                dfs(v, visitedNode);
            }
        }
    }
};

int main() {
    Graph g(8);

    vector<bool> visitedNodes(8, false);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 6);
    g.addEdge(4, 6);
    g.addEdge(4, 7);
    g.addEdge(6, 7);

    g.printGraph();

    cout << "Dfs : ";

    g.dfs(0, visitedNodes);

    return 0;
}