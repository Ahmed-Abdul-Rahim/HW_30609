#ifndef CUSTOMQUEUE_H
#define CUSTOMQUEUE_H

#include <iostream>
#include <memory>
using namespace std;

template <typename T>
class QueueNode {
public:
    T data;
    shared_ptr<QueueNode<T>> next;

    QueueNode(T val) : data(val), next(nullptr) {}
};

template <typename T>
class CustomQueue {
private:
    shared_ptr<QueueNode<T>> front;
    shared_ptr<QueueNode<T>> rear;

public:
    CustomQueue() : front(nullptr), rear(nullptr) {}

    void enqueue(T val) {
        auto newNode = make_shared<QueueNode<T>>(val);
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (front) {
            front = front->next;
            if (!front) rear = nullptr;
        }
    }

    T peek() {
        if (front) return front->data;
        throw runtime_error("Queue is empty");
    }

    bool isEmpty() {
        return front == nullptr;
    }
};

#endif
