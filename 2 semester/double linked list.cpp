#include <iostream>
#include <fstream>
using namespace std;
// 1ж 2 двунаправ
struct Node{
    float data;
    Node* next;
    Node* prev;

    Node(float val) : data(val), next(nullptr), prev(nullptr) {} 
};
struct linked_list{
    Node* first;
    Node* last;

    linked_list() : first(nullptr), last(nullptr) {}

    bool is_empty(){
        return first == nullptr;
    }

    void push_back(float val){
        Node* p = new Node(val);
        if (is_empty()){
            first = p;
            last = p;
        }
        else{
            p->prev = last;
            last->next = p;
            last = p;
        }
    }
    
    void push_forward(float val){
        Node* p = new Node(val);
        if (is_empty()){
            first = p;
            last = p;
        }
        else{
            first->prev = p;
            p->next = first;
            first = p;
        }
    }
    
    void print_l(){
        if (is_empty()){
            return;
        }
        
        Node* p = first;
        while(p){
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
        
    }

    void print_r(){
        if (is_empty()){
            return;
        }
        
        Node* p = last;
        while(p){
            cout << p->data << " ";
            p = p->prev;
        }
        cout << endl;
        
    }
};
int main(){
    linked_list l;
    ifstream fin;
    fin.open("test.txt");
    float num,previous_num;
    bool flag = true;
    fin >> num;
    previous_num = num;
    do {
        if (previous_num >= num){
            flag = false;
        }
        l.push_back(num);
        previous_num = num;
    }while (fin >> num);
    
    cout <<"---------------------" << endl;
    l.print_l();
    l.print_r();
    return 0;
}