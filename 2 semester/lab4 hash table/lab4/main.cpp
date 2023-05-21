#include <iostream>
#include <fstream>
#include <string>

using namespace std;


struct TableElement {
    string productName;
    int quantity;
};


struct HashNode {
    string key;
    TableElement value;
    HashNode* next;
};

class HashTable {
private:
    HashNode** table;
    int size;
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
        table = new HashNode * [n];
        for (int i = 0; i < n; i++) {
            table[i] = nullptr;
        }
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
        HashNode* newNode = new HashNode();
        newNode->key = key;
        newNode->value = value;
        newNode->next = table[index];
        table[index] = newNode;
    }
    int search(string key) {
        int index = hashFunc(key);
        HashNode* node = table[index];
        while (node != nullptr) {
            if (node->key == key) {
                return node->value.quantity;
            }
            node = node->next;
        }
        return -1;
    }
    void print() {
        for (int i = 0; i < size; i++) {
            HashNode* node = table[i];
            while (node != nullptr) {
                cout << "Key: " << node->key << ", Value: " << node->value.productName << ", " << node->value.quantity << endl;
                node = node->next;
            }
        }
    }
    void buy(string key, int quantityToBuy) {
        int index = hashFunc(key);
        HashNode* node = table[index];
        while (node != nullptr) {
            if (node->key == key) {
                if (node->value.quantity < quantityToBuy) {
                    cout << "Error: Not enough " << node->value.productName << " in stock." << endl;
                    return;
                }
                else {
                    node->value.quantity -= quantityToBuy;
                    if (node->value.quantity == 0) {
                        table[index] = node->next;
                        delete node;
                    }
                    return;
                }
            }
            node = node->next;
        }
        cout << "Error: " << key << " not found." << endl;
    }

};
int main() {
    HashTable table(100);

    ifstream inputwork("WORK.txt");

    string productCode;
    string productName;
    int quantity; //кол-во
    while (inputwork >> productCode >> productName >> quantity) {
        TableElement element = { productName, quantity };
        table.insert(productCode, element);
    }

    table.print();
    cout << "--------------------------" << endl;
    ifstream inputbuy("buy.txt");
    while (inputbuy >> productCode >> quantity) {
        table.buy(productCode, quantity);
    }
    table.print();
    return 0;
}
