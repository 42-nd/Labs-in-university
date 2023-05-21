#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set> //неотсортированное множество, используется при вводе городов которые мы избегаем, хотя можно и без этого
#include <fstream>
#include <string>
using namespace std;


class Graph {
public:
    int V; // кол-во вершин(городов)
    vector<vector<int>> adj; // список связности

    Graph(int n) {
        V = n;
        adj.resize(n);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
};

// Поиск в ширину, чтобы найти кратчайший путь из A в B, используется, потому что он гарантирует, что кратчайший путь будет найден, если граф не содержит ребер отрицательного веса.
vector<int> BFS(Graph graph, int A, int B, unordered_set<int> avoid) {
    vector<int> path; // Хранит путь из А в В
    queue<int> q; // Очередь, необходимая чтобы хранить вершины, которые нужно обойти, а также чтобы сохранять порядок обхода.
    vector<bool> visited(graph.V, false); // вектор, который хранит, какие вершины мы посетили
    vector<int> parent(graph.V, -1); // нужен, чтобы потом вернуться и вывести путь

    // помечаем вершину А пройденной
    q.push(A);
    visited[A] = true;

    // сам алгоритм
    while (!q.empty()) {
        int node = q.front();
        q.pop();

        // проверка, не попали ли мы в В
        if (node == B) {
            // проходим в обратном порядке от В в А и выводим маршрут
            int curr = B;
            while (curr != A) {
                path.push_back(curr);
                curr = parent[curr];
            }
            path.push_back(A);
            reverse(path.begin(), path.end());
            return path;
        }

        // проходим всех соседей конкретного города
        for (int neighbor : graph.adj[node]) {
            // проеверяем не явлется ли сосед тем, кого надо избегать и не посетили ли мы его
            if (!avoid.count(neighbor) && !visited[neighbor]) {
                // добавляем в очередь, отмечаем пройденным, добавляем в parent, чтобы запомнить как шли
                q.push(neighbor);
                visited[neighbor] = true;
                parent[neighbor] = node;
            }
        }
    }

    // Если В недостижим из А
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

    string A, B; // из какого в какой город надо найти путь
    int leng;
    input >> A >> B >> leng;

    int k; // сколько городов надо избегать
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
        fout << "Не нейден путь из " << city_names[A_index] << " в " << city_names[B_index] << endl;
    }
    else {
        fout << "Кратчайший путь из " << city_names[A_index] << " в " << city_names[B_index] << ": ";
        for (int node : path) {
            fout << city_names[node] << " ";
        }
    }
    return 0;
}