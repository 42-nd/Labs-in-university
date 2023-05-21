#include <iostream>
#include <fstream>
#include <string>

using namespace std;


struct TableElement {
    string productName;
    int quantity;
    int price;
};


struct HashNode {
    string key;
    TableElement value;
    HashNode* next;
};

class HashTable {
public:

    int size;
    int num_of_elems;
    HashNode** table;

    HashTable(int n) {
        size = n;
        num_of_elems = 0;
        table = new HashNode * [n];
        for (int i = 0; i < n; i++) {
            table[i] = nullptr;
        }
    }

    int hashFunc(string key) {
        int hash = 0;
        for (char c : key) {
            hash += (int)c;
        }
        return hash % size;
    }
    void insert(string key, TableElement value) {

        int index = hashFunc(key);
        HashNode* node = table[index];
        while (node != nullptr) {
            if (node->key == key) {
                node->value.quantity += value.quantity;
                return;
            }
            node = node->next;
        }
        num_of_elems++;
        HashNode* newNode = new HashNode();
        newNode->key = key;
        newNode->value = value;
        newNode->next = table[index];
        table[index] = newNode;
    }
    TableElement search(string key) {
        int index = hashFunc(key);
        HashNode* node = table[index];
        while (node != nullptr) {
            if (node->key == key) {
                return node->value;
            }
            node = node->next;
        }
    }
    void print() {
        for (int i = 0; i < size; i++) {
            HashNode* node = table[i];
            while (node != nullptr) {
                cout << "Key: " << node->key << ", Value: " << node->value.productName << ", " << node->value.quantity << ", " << node->value.price << endl;
                node = node->next;
            }
        }
    }

};

void shellSort(HashTable& hashTable) {
    int n = hashTable.num_of_elems;
    int* quantities = new int[n];
    string* keys = new string[n];
    int i = 0;
    
    for (int j = 0; j < hashTable.size; j++) {
        HashNode* node = hashTable.table[j];
        while (node != nullptr) {
            quantities[i] = node->value.quantity;
            keys[i] = node->key;
            i++;
            node = node->next;
        }
    }
    
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = quantities[i];
            string temp_key = keys[i];
            int j = i;
            while (j >= gap && quantities[j - gap] > temp) {
                quantities[j] = quantities[j - gap];
                keys[j] = keys[j - gap];
                j -= gap;
            }
            quantities[j] = temp;
            keys[j] = temp_key;
        }
    }

    for (int i = 0; i < n; i++) {
        TableElement elem = hashTable.search(keys[i]);
        cout << keys[i] << " " << elem.productName << " " << elem.quantity << " " << elem.price << endl;
    }

    delete[] quantities;
    delete[] keys;
}

int main() {
    HashTable table(100);

    ifstream inputwork("WORK.txt");
    ifstream inputprice("prices.txt");

    string productCode;
    string productName;
    int quantity; 
    while (inputwork >> productCode >> productName >> quantity) {
        TableElement element = { productName, quantity, -1 };
        table.insert(productCode, element);
    }

    table.print();
    cout << "------------------1" << endl;
    int price;
    while (inputprice >> productCode >> price) {
        int index = table.hashFunc(productCode);
        HashNode* node = table.table[index];
        while (node != nullptr) {
            if (node->key == productCode) {
                node->value.price = price;
            }
            node = node->next;
        }
    }
    table.print();
    cout << "------------------2" << endl;
    shellSort(table);
    return 0;
}
