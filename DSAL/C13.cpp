//Represent a given graph using adjacency matrix/ list to perform DFS and using list to perform BFS. Use the map of the area around the college as the graph. Identify the prominent land marks as nodes and perform DFS and BFS on that

#include <iostream>
#include <map>
#include <vector>
#include <queue>
using namespace std;

class Graph {
    map<string, int> landmarks; 
    vector<string> names;
    vector<vector<int>> adjList;
    int nodes;

public:
    Graph(int n) {
        nodes = n;
        adjList.resize(n);
    }

    void addLandmark(int index, string name) {
        landmarks[name] = index;
        names.push_back(name);
    }

    void addEdge(string u, string v) {
        int i = landmarks[u], j = landmarks[v];
        adjList[i].push_back(j);
        adjList[j].push_back(i);
    }

    void DFS(int start, vector<bool> &visited) {
        cout << names[start] << " ";
        visited[start] = true;
        for (int neighbor : adjList[start]) {
            if (!visited[neighbor])
                DFS(neighbor, visited);
        }
    }

    void BFS(int start) {
        vector<bool> visited(nodes, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << names[node] << " ";

            for (int neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    void performDFS(string start) {
        vector<bool> visited(nodes, false);
        cout << "DFS: ";
        DFS(landmarks[start], visited);
        cout << endl;
    }

    void performBFS(string start) {
        cout << "BFS: ";
        BFS(landmarks[start]);
        cout << endl;
    }
};

int main() {
    Graph g(5);

    g.addLandmark(0, "College");
    g.addLandmark(1, "Library");
    g.addLandmark(2, "Canteen");
    g.addLandmark(3, "Hostel");
    g.addLandmark(4, "Playground");

    g.addEdge("College", "Library");
    g.addEdge("College", "Canteen");
    g.addEdge("Library", "Hostel");
    g.addEdge("Canteen", "Playground");
    g.addEdge("Hostel", "Playground");

    g.performDFS("College");
    g.performBFS("College");

    return 0;
}
