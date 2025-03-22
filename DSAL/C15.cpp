//You have a business with several offices; you want to lease phone lines to connect them up with each other; and the phone company charges different amounts of money to connect different pairs of cities. You want a set of lines that connects all your offices with a minimum total cost. Solve the problem by suggesting appropriate data structures.


#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
    int offices;
    vector<vector<pair<int, int>>> adjList;

public:
    Graph(int n) {
        offices = n;
        adjList.resize(n);
    }

    void addEdge(int u, int v, int cost) {
        adjList[u].push_back({cost, v});
        adjList[v].push_back({cost, u});
    }

    void primMST(int start) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<bool> visited(offices, false);
        int totalCost = 0;

        pq.push({0, start});

        cout << "Minimum Spanning Tree Edges:\n";
        while (!pq.empty()) {
            auto [cost, node] = pq.top();
            pq.pop();

            if (visited[node]) continue;
            visited[node] = true;
            totalCost += cost;

            if (cost != 0) cout << "Connected: " << node << " with cost " << cost << endl;

            for (auto &[edgeCost, neighbor] : adjList[node]) {
                if (!visited[neighbor]) pq.push({edgeCost, neighbor});
            }
        }

        cout << "Total Cost: " << totalCost << endl;
    }
};

int main() {
    Graph g(5); 

    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 20);
    g.addEdge(1, 3, 30);
    g.addEdge(2, 3, 25);
    g.addEdge(3, 4, 15);
    g.addEdge(1, 4, 35);

    g.primMST(0); 

    return 0;
}
