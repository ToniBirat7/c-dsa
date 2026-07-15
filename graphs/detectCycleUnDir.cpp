// Cycle Detection in Graph (Undirected)

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

    bool cycleExists(int u, int parent, vector<bool> &visitedNodes) {

        cout << u << " ";
        parent = u;

        visitedNodes[u] = true;

        for (int v : adjList[u]) {
            if (!visitedNodes[v]) {
                if (cycleExists(v, parent, visitedNodes)) return true;
            }
            else {
                if (v != parent) {
                return true;
                }
            }
        }

        return false;
    }
};

int main() {

    Graph g(8);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 2);
    g.addEdge(3, 4);


    g.printGraph();

    cout << "Dfs: ";

    vector<bool> visitedNodes(8, false);

    bool existsOrNot = g.cycleExists(0, -1, visitedNodes);

    cout << "\nCycle: " << existsOrNot;

    return 0;
}
