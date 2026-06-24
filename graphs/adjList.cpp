#include <iostream>
#include <vector>

using namespace std;

class Graph {
private: 
    int numVertices;
    vector<vector<int>> adjList;

public:
    Graph(int vertices) {
        numVertices = vertices;
        adjList.resize(vertices);
    }

    // Add an edge for an undirected graph
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    // Print the representation
    void printGraph() {
        for (int i = 0; i < numVertices; i++) {
            cout << "Vertex " << i << " is connected to: ";
            for (int neighbour : adjList[i]) {
                cout << neighbour << " ";
            }
            cout << "\n";
        }
    }

    // Print edge directions reversed
    Graph getTranspose() {
        Graph transpose(numVertices);

        for (int u = 0; u < numVertices; u++) {
            for (int v : adjList[u]) {
                transpose.addEdge(v,u);
            }
        }

        return transpose;
    }
};

int main() {

    Graph g(4);
    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(1,2);
    g.addEdge(2,3);

    cout << "--- Original Graph ---" << endl;
    g.printGraph();

    cout << "\n--- Transposed Graph ---" << endl;
    Graph g_transpose = g.getTranspose();
    g_transpose.printGraph();
    
    return 0;
}