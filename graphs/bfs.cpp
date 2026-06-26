#include <iostream>
#include <vector>
#include <queue> // 1. Added missing queue header

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

    // BFS Traversal starting from a specific node
    void bfs(int startVertex) {
        // 1. Create a visited vector and initialize all nodes to 'false'
        vector<bool> visitedNodes(V, false);

        // 2. Create the queue
        queue<int> bfsQueue;

        // 3. Mark the starting node as visited and push it to the queue
        visitedNodes[startVertex] = true;
        bfsQueue.push(startVertex);

        cout << "BFS Traversal: ";

        // 4. Loop runs as long as there are nodes to process in the queue
        while (!bfsQueue.empty()) {
            // Get the front element of the queue
            int curr = bfsQueue.front();
            bfsQueue.pop(); // Now it is safe to pop

            // Print/Process the node
            cout << curr << " ";

            // Check all neighbors of the current node
            for (int neigh : adjList[curr]) {
                // If the neighbor hasn't been visited, mark it visited and queue it
                if (!visitedNodes[neigh]) {
                    visitedNodes[neigh] = true;
                    bfsQueue.push(neigh);
                }
            }
        }
        cout << "\n";
    }
};

int main () {
    // 2. Changed graph size from 5 to 8 to fit vertices 0 to 7
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