#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct HashNode {
    string key;
    float value;
};

class HashTable {
private:
    HashNode* table;
    int size;
    int num;
    int hashFunc(string key) {
        int hash = 0;
        for (char c : key) {
            hash += (int)c;
        }
        return hash % size;
    }
public:
    HashTable(int n) {
        size = n;
        table = new HashNode[n];
        for (int i = 0; i < n; i++) {
            table[i].key = "";
            table[i].value= 0;
        }
    }

    void insert(string key, float value) {
        //int index = hashFunc(key);
        //int startIndex = index;
        int i = 0;
        while (table[i].key != "") {
            //i = (i + 1) % size;
            i++;
            if (i == size-1) {
                cout << "Error: table is full" << endl;
                return;
            }
        }
        table[i].key = key;
        table[i].value = value;
        num++;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            if (table[i].key != "") {
                cout << "Key: " << table[i].key << ", Value: " << table[i].value << endl;
            }
        }
    }
    void sort_direct_insert() {
        int comparisons = 0;
        int moves = 0;
        for (int i = 1; i < num; i++) {
            HashNode current = table[i];
            moves++;
            int j = i - 1;
            while (j >= 0 && table[j].value > current.value) {
                comparisons++;
                table[j + 1] = table[j];
                moves++;
                j--;
            }
            comparisons++;
            table[j + 1] = current;
            moves++;
        }
        comparisons++;
        cout << "Comparisons: " << comparisons << endl;
        cout << "Moves: " << moves << endl;
    }
};
int main() {
    HashTable table(10);

    ifstream inputwork("input.txt");

    string productCode;
    float value;
    while (inputwork >> productCode >> value) {
        table.insert(productCode, value);
    }

    table.print();

    cout << "----------------------------" << endl;
    table.sort_direct_insert();
    cout << "----------------------------" << endl;
    table.print();
    return 0;
}