#include <iostream>
#include <fstream>
#include "queue.h"

using namespace std;
//3á 4à
int main() {
    queue q;
    queue ab;
    ifstream fin;
    float num;
    fin.open("test lab 2.txt");
    cout << q.is_empty() << endl;
    while (fin >> num) {
        q.push(num);
    }

    cout << q.is_empty() << endl;
    cout << q.top() << endl;
    q.pop();
    cout << q.top() << endl;

    cout << "--------------" << endl;
    q.print();
    cout << q.is_empty() << endl;
    q.make_empty();
    cout << q.is_empty() << endl;
    return 0;
}