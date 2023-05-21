#include <iostream> 
#include <fstream>
#include <vector> 
#include <stack> 
#include <unordered_map>
using namespace std;

class Graph {

public:
    int n; //���������� ������ � �����

    unordered_map<int, vector<int>> adj_dict; //�������, �������� ������ ��������� ������

    Graph(int k) { //����������� ������, ����������� ���������� ������ � �����
        n = k;
        for (int i = 0; i < k; i++) {// ������������� ������� ��������� ��� ���� ������
            adj_dict[i] = vector<int>();
        }
    }

    void add_edge(int u, int v) { //����� ���������� ����� ����� ��������� u � v
        adj_dict[u].push_back(v); 
    }

    void print() { //����� ������ ������ ��������� ����� �� �����
        for (auto it = adj_dict.begin(); it != adj_dict.end(); it++) { //���������� ��� ������� �����
            int u = it->first; 
            vector<int> neighbors = it->second; //������ ��������� ��� ������� u
            cout << u << ": ";
            for (auto v : neighbors) { //���������� ��� ������� ������� ��� ������� u
                cout << v << " ";
            }
            cout << endl;
        }
    }

    vector<int> find_cycle() {
        for (auto it = adj_dict.begin(); it != adj_dict.end(); it++) {
            vector<int> cycle; // ������ ��� �������� ���������� ������
            vector<bool> visited(n, false); // ������, ������������� ���������� �������
            int start = it->first; // �������� ����� � ������� u
            stack<int> s;
            s.push(start);
            visited[start] = true;
            while (!s.empty()) {
                int u = s.top();
                s.pop();
                cycle.push_back(u); // ��������� ������� u � ����
                for (auto v : adj_dict[u]) { // ���������� ��� ������� ������� ��� u
                    
                    if (!visited[v] && adj_dict[v].size() != 0) { // ���� v ��� �� ��������, ��������� �� � ���� � �������� ��� ����������
                        s.push(v);
                        visited[v] = true;
                    }
                    else if (find(cycle.begin(), cycle.end(), v) != cycle.end()) { // ���� v ��� �������� � ��������� � ������� �����, �� �� ����� ����
                        auto start = find(cycle.begin(), cycle.end(), v); // ������� ������ �����
                        vector<int> result(start, cycle.end()); // ������� ������, ���������� ������� �����
                        return result;
                    }
                }
            }
            
        }

        return vector<int>(); // ���� ���� �� ������, ���������� ������ ������
    }
};

void check_graph(Graph g) { 
    vector<int> cycle = g.find_cycle();
    for (auto k : cycle) {// ���������� ������� �����
        Graph g_copy(g.n); 
        g_copy.adj_dict = g.adj_dict;
        g_copy.adj_dict.erase(k); 

        for (auto& adj_list : g_copy.adj_dict) {// ������� ������� �� ������� ��������� ������ ������ ����� �����
            auto& neighbors = adj_list.second;
            neighbors.erase(remove(neighbors.begin(), neighbors.end(), k), neighbors.end());
        }
        if (g_copy.find_cycle().size()==0) { // ���� ����� �������� ������� ���� �� �������� ������, ������� ��������� � ����� ������� ���������
            cout << "We can delete vertex: " << k << endl; 
            cout << "How adj_dict should look:" << endl; 
            g_copy.print(); 

            return;
        }
    }
    cout << "We can't delete any vertex" << endl; // ���� �� ���� ������� ������, ������� ����� �������, ������� ��������� �� ����
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
