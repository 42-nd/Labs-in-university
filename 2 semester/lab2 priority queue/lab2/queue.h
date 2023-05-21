#pragma once
struct Node;
struct queue {
    Node* first;
    Node* last;

    queue();

    bool is_empty();
    void push(float val);
    void pop();
    float top();
    void print();
    void make_empty();
};
