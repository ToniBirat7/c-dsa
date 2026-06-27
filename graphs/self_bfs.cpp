#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjList;

public:
    Graph(int graphSize) {
        V = graphSize;
        adjList.resize(V);
    }

    void addEdge(int u, int v) {
        // Directed Graph
        adjList[u].push_back(v);
    }

    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << "Neighbour of Node " << i << ": ";

            for (int neighbour : adjList[i]) {
                cout << neighbour;
            }

            cout << "\n";
        }
    }

    void bfs(int startVertex) {
        // Visited list
        vector<bool> visitedNodes(V, false);

        // Queue to store the neighbours
        queue<int> bfsQueue;

        visitedNodes[startVertex] = true;
        bfsQueue.push(startVertex);

        cout << "BFS Traversal: ";

        while (!bfsQueue.empty()) {
        
            int curr = bfsQueue.front();
            bfsQueue.pop();
            
            for (int neighbour : adjList[curr]) {
                if (!visitedNodes[neighbour]) {
                    visitedNodes[neighbour] = true;
                    bfsQueue.push(neighbour);
                }
            }
        }
    }
};

int main() {
    return 0;
}