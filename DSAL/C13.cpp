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
        if (landmarks.find(u) == landmarks.end() || landmarks.find(v) == landmarks.end()) {
            cout << "Invalid landmarks! Ensure both exist before adding an edge.\n";
            return;
        }
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
        if (landmarks.find(start) == landmarks.end()) {
            cout << "Invalid starting landmark!\n";
            return;
        }
        vector<bool> visited(nodes, false);
        cout << "DFS: ";
        DFS(landmarks[start], visited);
        cout << endl;
    }

    void performBFS(string start) {
        if (landmarks.find(start) == landmarks.end()) {
            cout << "Invalid starting landmark!\n";
            return;
        }
        cout << "BFS: ";
        BFS(landmarks[start]);
        cout << endl;
    }
};

int main() {
    int n, edges;
    cout << "Enter number of landmarks: ";
    cin >> n;
    cin.ignore();

    Graph g(n);

    cout << "Enter landmark names:\n";
    for (int i = 0; i < n; i++) {
        string name;
        cout << "Landmark " << i + 1 << ": ";
        getline(cin, name);
        g.addLandmark(i, name);
    }

    cout << "Enter number of connections (edges): ";
    cin >> edges;
    cin.ignore();

    cout << "Enter landmark connections (Format: Landmark1 Landmark2):\n";
    for (int i = 0; i < edges; i++) {
        string u, v;
        cout << "Edge " << i + 1 << ": ";
        cin >> u >> v;
        g.addEdge(u, v);
    }

    string start;
    cout << "Enter starting landmark for DFS and BFS: ";
    cin >> start;

    g.performDFS(start);
    g.performBFS(start);

    return 0;
}

