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

struct Stack {
    Node* pTop;
};

Stack* initialize(int val) {
    Node* newNode = new (nothrow) Node {val, nullptr};

    if (!newNode){
        throw myex;
    }

    Stack* stack = new (nothrow) Stack {newNode};

    if (!stack) {
        throw myex;
    }

    return stack;
}

bool isEmpty(const Stack* stack) {
    if (stack->pTop == nullptr) {
        return true;
    }

    return false;
}

void Push(Stack* stack, int val) {
    Node* newNode = new Node{ val, stack->pTop };

    if (!newNode) {
        throw "cought not memory alloccation";
    }

    stack->pTop = newNode;
}

int Pop (Stack* stack) {
    if (isEmpty(stack)) {
        throw "stack is empty (cought not pop)";
    }

    Node* tmp = stack->pTop;
    int tmpKey = tmp->key;
    stack->pTop = stack->pTop->pNext;
    delete tmp;
    tmp = nullptr;

    return tmpKey;
}

int countingElementStack (Stack* stack) {
    int count = 0;
    Node* tmp = stack->pTop;

    while (tmp){
        ++count;
        tmp = tmp->pNext;
    }

    return count;
}