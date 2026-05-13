#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

const int MAX = 100000;
vector<int> graph[MAX];
bool visited[MAX];

void parallelDFS(int node) {
    bool alreadyVisited;

    #pragma omp critical
    {
        alreadyVisited = visited[node];
        if (!alreadyVisited) {
            visited[node] = true;
            cout << node << " ";
        }
    }

    if (alreadyVisited) return;

    for (int i = 0; i < graph[node].size(); i++) {
        int adj = graph[node][i];

        #pragma omp task
        parallelDFS(adj);
    }
}

int main() {
    int n, m, start;

    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> m;

    cout << "Enter starting node: ";
    cin >> start;

    cout << "\nEnter edges (u v format):\n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cout << "Edge " << i + 1 << ": ";
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u); // undirected graph
    }

    for (int i = 0; i < n; i++)
        visited[i] = false;

    cout << "\nParallel DFS Traversal:\n";

    #pragma omp parallel
    {
        #pragma omp single
        {
            parallelDFS(start);
        }
    }

    cout << endl;
    return 0;
}