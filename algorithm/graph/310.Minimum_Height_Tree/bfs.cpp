#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> findMinHeightTrees(int n, vector <vector<int>> &edges) {
    if (n == 1) {
        // If there is only one node, return it as the root
        return {0};
    }

    vector <vector<int>> adjList(n);
    vector<int> inDegree(n, 0);

    // Build the adjacency list and compute in-degrees
    for (const auto &edge: edges) {
        adjList[edge[0]].push_back(edge[1]);
        adjList[edge[1]].push_back(edge[0]);
        inDegree[edge[0]]++;
        inDegree[edge[1]]++;
    }

    // Initialize a queue for topological sorting
    queue<int> q;

    // Add leaves (nodes with in-degree 1) to the queue
    for (int i = 0; i < n; ++i) {
        if (inDegree[i] == 1) {
            q.push(i);
        }
    }

    // Print the adjacency list
    cout << "Adjacency List:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << i << " -> ";
        for (int neighbor: adjList[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }

    // Perform topological sorting
    while (n > 2) {
        int sz = q.size();
        n -= sz;

        for (int i = 0; i < sz; ++i) {
            int node = q.front();
            q.pop();

            for (int neighbor: adjList[node]) {
                if (--inDegree[neighbor] == 1) {
                    q.push(neighbor);
                }
            }
        }
    }

    // The remaining nodes in the queue are the roots of MHTs
    vector<int> result;
    while (!q.empty()) {
        result.push_back(q.front());
        q.pop();
    }

    return result;
}

int main() {
    // Example usage
    int n = 6;
    vector <vector<int>> edges = {{0, 3},
                                  {1, 3},
                                  {2, 3},
                                  {4, 3},
                                  {5, 4}};

    vector<int> result = findMinHeightTrees(n, edges);

    // Print the result
    cout << "Minimum Height Trees' root labels: ";
    for (int root: result) {
        cout << root << " ";
    }
    cout << endl;

    return 0;
}

