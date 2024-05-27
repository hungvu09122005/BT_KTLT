#include <iostream>

using namespace std;

class myexception: public exception
{
  virtual const char* what() const throw()
  {
    return "could not memory allocation";
  }
} myex;

struct Node {
    int key;
    Node* pNext;
};

struct Queue {
    Node* pHead;
    Node* pTail;
};

Queue* initialize(int val) {
    Node* newNode = new (nothrow) Node {val, nullptr};

    if (!newNode){
        throw myex;
    }

    Queue* queue = new (nothrow) Queue {newNode, newNode};

    if (!queue) {
        throw myex;
    }

    return queue;
}

bool isEmpty(const Queue* queue) {
    if (queue->pHead == nullptr && queue->pTail == nullptr) {
        return true;
    }

    return false;
}

void Enqueue (Queue* queue, int val) {
    Node* newNode = new Node{ val, queue->pHead };

    if (!newNode) {
        throw "cought not memory alloccation";
    }

    queue->pHead = newNode;
}

int Dequeue (Queue* queue) {
    if (isEmpty(queue)) {
        throw "queue is empty (cought not pop)";
    }

    Node* tmp = queue->pHead;
    int tmpKey = queue->pTail->key;
    
    while (tmp->pNext != queue->pTail){
        tmp = tmp->pNext;
    }

    tmp->pNext = nullptr;
    delete queue->pTail;
    queue->pTail = tmp;

    return tmpKey;
}

int countingElementQueue (Queue* queue) {
    int count = 0;
    Node* tmp = queue->pHead;

    while (tmp){
        ++count;
        tmp = tmp->pNext;
    }

    return count;
}