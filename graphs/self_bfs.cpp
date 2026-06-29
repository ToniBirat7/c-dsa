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

            cout << curr << " ";

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
    Graph g(8);

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

    // Print adjacency list
    g.printGraph();
    cout << "\n";

    // Run BFS starting from node 0
    g.bfs(0);
    
    return 0;
}