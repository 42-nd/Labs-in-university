#include <iostream> 
#include <fstream>
#include <vector> 
#include <stack> 
#include <unordered_map>
using namespace std;

class Graph {

public:
    int n; //количество вершин в графе

    unordered_map<int, vector<int>> adj_dict; //словарь, хранящая списки смежности вершин

    Graph(int k) { //конструктор класса, принимающий количество вершин в графе
        n = k;
        for (int i = 0; i < k; i++) {// Инициализация списков смежности для всех вершин
            adj_dict[i] = vector<int>();
        }
    }

    void add_edge(int u, int v) { //метод добавления ребра между вершинами u и v
        adj_dict[u].push_back(v); 
    }

    void print() { //метод вывода списка смежности графа на экран
        for (auto it = adj_dict.begin(); it != adj_dict.end(); it++) { //перебираем все вершины графа
            int u = it->first; 
            vector<int> neighbors = it->second; //список смежности для вершины u
            cout << u << ": ";
            for (auto v : neighbors) { //перебираем все вершины смежные для вершины u
                cout << v << " ";
            }
            cout << endl;
        }
    }

    vector<int> find_cycle() {
        for (auto it = adj_dict.begin(); it != adj_dict.end(); it++) {
            vector<int> cycle; // вектор для хранения пройденных вершин
            vector<bool> visited(n, false); // массив, отслеживающий пройденные вершины
            int start = it->first; // начинаем поиск с вершины u
            stack<int> s;
            s.push(start);
            visited[start] = true;
            while (!s.empty()) {
                int u = s.top();
                s.pop();
                cycle.push_back(u); // добавляем вершину u в цикл
                for (auto v : adj_dict[u]) { // перебираем все смежные вершины для u
                    
                    if (!visited[v] && adj_dict[v].size() != 0) { // если v еще не посещена, добавляем ее в стек и отмечаем как посещенную
                        s.push(v);
                        visited[v] = true;
                    }
                    else if (find(cycle.begin(), cycle.end(), v) != cycle.end()) { // если v уже посещена и находится в текущем цикле, то мы нашли цикл
                        auto start = find(cycle.begin(), cycle.end(), v); // находим начало цикла
                        vector<int> result(start, cycle.end()); // создаем вектор, содержащий вершины цикла
                        return result;
                    }
                }
            }
            
        }

        return vector<int>(); // если цикл не найден, возвращаем пустой вектор
    }
};

void check_graph(Graph g) { 
    vector<int> cycle = g.find_cycle();
    for (auto k : cycle) {// Перебираем вершины цикла
        Graph g_copy(g.n); 
        g_copy.adj_dict = g.adj_dict;
        g_copy.adj_dict.erase(k); 

        for (auto& adj_list : g_copy.adj_dict) {// Удаляем вершину из списков смежности других вершин копии графа
            auto& neighbors = adj_list.second;
            neighbors.erase(remove(neighbors.begin(), neighbors.end(), k), neighbors.end());
        }
        if (g_copy.find_cycle().size()==0) { // Если после удаления вершины граф не содержит циклов, выводим сообщение и новый словарь смежности
            cout << "We can delete vertex: " << k << endl; 
            cout << "How adj_dict should look:" << endl; 
            g_copy.print(); 

            return;
        }
    }
    cout << "We can't delete any vertex" << endl; // Если не было найдено вершин, которые можно удалить, выводим сообщение об этом
}
int main() {
    int n, u, v;
    ifstream input("input.txt"); 
    input >> n; 
    Graph g(n); 
    while (input >> u >> v) { 
        g.add_edge(u, v); 
    }
    input.close(); 
    g.print(); 
    cout << "---------------" << endl;
    vector<int> cycle = g.find_cycle();
    cout << "---------------" << endl;
    for (auto i : cycle) {
        cout << i << " ";
    }
    cout << endl;
    check_graph(g); 
    return 0; 
}
