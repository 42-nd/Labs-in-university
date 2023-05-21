#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set> //����������������� ���������, ������������ ��� ����� ������� ������� �� ��������, ���� ����� � ��� �����
#include <fstream>
#include <string>
using namespace std;


class Graph {
public:
    int V; // ���-�� ������(�������)
    vector<vector<int>> adj; // ������ ���������

    Graph(int n) {
        V = n;
        adj.resize(n);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
};

// ����� � ������, ����� ����� ���������� ���� �� A � B, ������������, ������ ��� �� �����������, ��� ���������� ���� ����� ������, ���� ���� �� �������� ����� �������������� ����.
vector<int> BFS(Graph graph, int A, int B, unordered_set<int> avoid) {
    vector<int> path; // ������ ���� �� � � �
    queue<int> q; // �������, ����������� ����� ������� �������, ������� ����� ������, � ����� ����� ��������� ������� ������.
    vector<bool> visited(graph.V, false); // ������, ������� ������, ����� ������� �� ��������
    vector<int> parent(graph.V, -1); // �����, ����� ����� ��������� � ������� ����

    // �������� ������� � ����������
    q.push(A);
    visited[A] = true;

    // ��� ��������
    while (!q.empty()) {
        int node = q.front();
        q.pop();

        // ��������, �� ������ �� �� � �
        if (node == B) {
            // �������� � �������� ������� �� � � � � ������� �������
            int curr = B;
            while (curr != A) {
                path.push_back(curr);
                curr = parent[curr];
            }
            path.push_back(A);
            reverse(path.begin(), path.end());
            return path;
        }

        // �������� ���� ������� ����������� ������
        for (int neighbor : graph.adj[node]) {
            // ���������� �� ������� �� ����� ���, ���� ���� �������� � �� �������� �� �� ���
            if (!avoid.count(neighbor) && !visited[neighbor]) {
                // ��������� � �������, �������� ����������, ��������� � parent, ����� ��������� ��� ���
                q.push(neighbor);
                visited[neighbor] = true;
                parent[neighbor] = node;
            }
        }
    }

    // ���� � ���������� �� �
    return path;
}

int main() {
    ifstream input("test.txt");
    ofstream fout ("file.txt");

    int n; 
    input >> n;
    vector <string> city_names;

    for (int i = 0; i < n; i++) {
        string city;
        input >> city;
        city_names.push_back(city);
    }

    Graph graph(n);
    int m;
    input >> m;

    for (int i = 0; i < m; i++) {
        string u, v;
        int leng;
        input >> u >> v >> leng;
        int u_index = find(city_names.begin(), city_names.end(), u) - city_names.begin();
        int v_index = find(city_names.begin(), city_names.end(), v) - city_names.begin();
        graph.addEdge(u_index, v_index);
    }

    string A, B; // �� ������ � ����� ����� ���� ����� ����
    int leng;
    input >> A >> B >> leng;

    int k; // ������� ������� ���� ��������
    input >> k;


    unordered_set<int> avoid;
    for (int i = 0; i < k; i++) {
        string city;
        input >> city;
        int city_index = find(city_names.begin(), city_names.end(), city) - city_names.begin();
        avoid.insert(city_index);
    }

    int A_index = find(city_names.begin(), city_names.end(), A) - city_names.begin();
    int B_index = find(city_names.begin(), city_names.end(), B) - city_names.begin();

    vector<int> path = BFS(graph, A_index, B_index, avoid);
    if (path.size() == 0) {
        fout << "�� ������ ���� �� " << city_names[A_index] << " � " << city_names[B_index] << endl;
    }
    else {
        fout << "���������� ���� �� " << city_names[A_index] << " � " << city_names[B_index] << ": ";
        for (int node : path) {
            fout << city_names[node] << " ";
        }
    }
    return 0;
}