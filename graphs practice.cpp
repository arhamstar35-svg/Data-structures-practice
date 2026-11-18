
#include <iostream>
using namespace std;

class Graph {
    int vertices;
    int adj[10][10];

public:

    // Constructor initializes the adjacency matrix with 0
    Graph(int v) {
        vertices = v;

        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                adj[i][j] = 0;
            }
        }
    }

    // Adds an undirected edge between two vertices
    void addEdge(int u, int v) {
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    // Displays the adjacency matrix
    void display() {
        cout << "Adjacency Matrix:\n";

        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                cout << adj[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Depth First Search
    void DFS(int start, bool visited[]) {

        // Mark current vertex as visited
        visited[start] = true;

        cout << start << " ";

        // Visit all unvisited adjacent vertices
        for (int i = 0; i < vertices; i++) {

            if (adj[start][i] == 1 && visited[i] == false) {
                DFS(i, visited);
            }
        }
    }

    // Starts DFS traversal
    void startDFS(int start) {
        bool visited[10] = {false};

        cout << "DFS: ";
        DFS(start, visited);

        cout << endl;
    }

    // Breadth First Search
    void BFS(int start) {
        bool visited[10] = {false};

        int queue[10];
        int front = 0;
        int rear = -1;

        // Insert starting vertex into queue
        queue[++rear] = start;
        visited[start] = true;

        cout << "BFS: ";

        while (front <= rear) {

            // Remove vertex from front
            int current = queue[front++];

            cout << current << " ";

            // Visit all adjacent unvisited vertices
            for (int i = 0; i < vertices; i++) {

                if (adj[current][i] == 1 && visited[i] == false) {

                    queue[++rear] = i;
                    visited[i] = true;
                }
            }
        }

        cout << endl;
    }
};

int main() {

    Graph g(5);

    // Add edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);

    // Display graph
    g.display();

    // Perform traversals
    g.startDFS(0);
    g.BFS(0);

    return 0;
}

