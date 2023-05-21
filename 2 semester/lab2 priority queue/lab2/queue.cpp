#include "queue.h"
#include "Node.h"
#include <iostream>
using namespace std;

    Node* first;
    Node* last;

    queue::queue() : first(nullptr), last(nullptr) {}

    bool queue::is_empty() {
        return first == nullptr;
    }

    void queue::push(float val) {
        Node* p = new Node(val);

        if (is_empty()) {
            first = p;
            last = p;
        }
        else {
            if (p->data > first->data) {
                p->next = first;
                first = p;
            }
            else {
                Node* iter = first;
                while (iter->next) {
                    if (iter->next->data < p->data) {
                        p->next = iter->next;
                        iter->next = p;
                        break;
                    }
                    iter = iter->next;
                }
                if (p->next == nullptr) {
                    last = p;
                }
            }
        }
    }

    void queue::pop() {
        if (is_empty()) {
            return;
        }
        if (first == last) {
            delete first;
            first = nullptr;
            last = nullptr;
        }
        else{
            Node* p = first->next;
            delete first;
            first = p;
        }
    }

    float queue::top() {
        if (!is_empty())
            return first->data;

    }

    void queue::print() {
        if (is_empty()) {
            return;
        }

        queue c;
        do {
            c.push(top());
            cout << top() << " ";
            pop();
        } while (!is_empty());

        while (!c.is_empty()) {
            push(c.top());
            c.pop();
        }
        cout << endl;

    }

    void queue::make_empty() {
        while (!is_empty()) {
            pop();
        }
    }
