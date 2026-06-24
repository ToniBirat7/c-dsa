#include <iostream>
#include <vector>

using namespace std;

class Graph {
private: 
    int numVertices;
    vector<vector<int>> adjMatrix; // 2D grid of size V x V

public:
    // Constructor
    Graph(int vertices) {
        numVertices = vertices;
        // Resize the outer vector to V, and fill each with an inner vector of size V initialized to 0
        adjMatrix.resize(vertices, vector<int>(vertices, 0));
    }

    // Add a directed edge: u -> v
    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        // For an undirected graph, you would also add:
        // adjMatrix[v][u] = 1;
    }

    // Check if an edge exists: O(1) Time Complexity
    bool hasEdge(int u, int v) {
        return adjMatrix[u][v] == 1;
    }

    // Print the physical matrix representation
    void printMatrix() {
        cout << "--- Adjacency Matrix Representation ---\n";
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << "\n";
        }
    }

    // Print the graph neighbors (Scanning a row takes O(V) time)
    void printGraph() {
        cout << "--- Graph Neighbors ---\n";
        for (int i = 0; i < numVertices; i++) {
            cout << "Vertex " << i << " is connected to: ";
            for (int j = 0; j < numVertices; j++) {
                if (adjMatrix[i][j] == 1) {
                    cout << j << " ";
                }
            }
            cout << "\n";
        }
    }
};

int main() {
    // Create a graph with 4 vertices
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);

    // 1. Print the raw 2D matrix
    g.printMatrix();
    cout << "\n";

    // 2. Print connections (formatted just like your adjacency list output)
    g.printGraph();
    cout << "\n";

    // 3. Fast O(1) Edge queries
    cout << "--- Edge Queries ---" << endl;
    cout << "Does edge 0 -> 2 exist? " << (g.hasEdge(0, 2) ? "Yes" : "No") << endl;
    cout << "Does edge 2 -> 1 exist? " << (g.hasEdge(2, 1) ? "Yes" : "No") << endl;

    return 0;
}