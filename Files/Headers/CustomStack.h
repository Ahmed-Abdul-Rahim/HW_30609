#ifndef CUSTOMSTACK_H
#define CUSTOMSTACK_H

#include <iostream>
#include <memory>
using namespace std;

template <typename T>
class StackNode {
public:
    T data;
    shared_ptr<StackNode<T>> next;

    StackNode(T val) : data(val), next(nullptr) {}
};

template <typename T>
class CustomStack {
private:
    shared_ptr<StackNode<T>> top;

public:
    CustomStack() : top(nullptr) {}

    void push(T val) {
        auto newNode = make_shared<StackNode<T>>(val);
        newNode->next = top;
        top = newNode;
    }

    T pop() {
        if (!top) {
            cout << "Stack is empty! Can't backtrack." << endl;
            return nullptr;
        }

        T poppedValue = top->data;
        top = top->next;
        return poppedValue;
    }

    T peek() {
        if (top) return top->data;
        throw runtime_error("Stack is empty!");
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

#endif
