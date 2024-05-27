#include <iostream>

using namespace std;

class myexception: public exception
{
  virtual const char* what() const throw()
  {
    return "could not memory allocation";
  }
} myex;

class myexception1: public exception
{
  virtual const char* what() const throw()
  {
    return "Singly linked list is empty.";
  }
} myex1;

struct Node {
    int key ;
    Node * pNext ;
};

struct List {
    Node * pHead ;
    Node * pTail ;
};

Node * createNode (int data ) {
    return new Node {data, nullptr};
}

List * createList ( Node * pNode ) {
    return new List {pNode, pNode};
}

bool isEmpty (List* L){
    return !L->pHead && !L->pTail;
}

bool addHead ( List *& L , int data ) {
    Node* newNode = createNode (data);

    if (!newNode){
        throw myex;
    }

    if (isEmpty(L)){
        L->pHead = newNode;
        L->pTail = newNode;
        return true;
    }

    newNode->pNext = L->pHead;
    L->pHead = newNode;

    return true;
}

bool addTail ( List *& L , int data ) {
    Node* newNode = createNode (data);

    if (!newNode){
        throw myex;
    }

    if (isEmpty(L)){
        L->pHead = newNode;
        L->pTail = newNode;
        return true;
    }

    L->pTail->pNext = newNode;
    L->pTail = newNode;

    return true;
}

bool addPos ( List *& L , int val , int pos ) {
    if (isEmpty(L)){
        return false;
    }

    if (pos <= 0) {
        return false;
    }

    if (pos == 1){
        addHead(L, val);
        return true;
    }

    int count = 1;
    Node* tmp = L->pHead;

    while (count != pos){
        tmp = tmp->pNext;
        ++count;

        if (tmp == nullptr) {
            return false;
        }
    }

    Node* newNode = new (nothrow) Node {tmp->key, tmp->pNext};

    if  (!newNode) {
        throw myex;
    }

    if (tmp->pNext == nullptr){
        tmp->key = val;
        tmp->pNext = newNode;
        L->pTail = newNode;
        return true;
    }

    tmp->key = val;
    tmp->pNext = newNode;

    return true;
}

bool addBefore ( List *& L , int data ,int val ) {
    Node* tmp = L->pHead;
    int count = 1;

    while ( tmp != nullptr){
        if (tmp->key == val){
            addPos(L, data, count);
            return true;
        }
        tmp = tmp->pNext;
        ++count;
    }

    return false;
}

bool addAfter ( List *& L , int data ,int val ) {
    Node* tmp = L->pHead;
    int count = 1;

    while (true){
        if (tmp == nullptr){
            break;
        }

        if (tmp->key == val){
            addPos(L, data, count + 1);
            return true;
        }

        tmp = tmp->pNext;

        ++count;
    }

    return false;
}

void removeHead ( List *& L ) {
    if (isEmpty(L)){
        throw myex1;
    }

    if (L->pHead == L->pTail){
        delete L->pHead;
        L->pHead = nullptr;
        L->pTail = nullptr;
        return;
    }

    Node* tmp = L->pHead->pNext;
    delete L->pHead;
    L->pHead = tmp;
}

void removeTail ( List *& L ) {
    if (isEmpty(L)){
        throw myex1;
    }

    if (L->pHead == L->pTail){
        delete L->pHead;
        L->pHead = nullptr;
        L->pTail = nullptr;
        return;
    }

    Node* tmp = L->pHead;

    while (tmp->pNext != L->pTail){
        tmp = tmp->pNext;
    }

    delete L->pTail;
    L->pTail = tmp;
    L->pTail->pNext = nullptr;
}

void removePos ( List *& L , int pos ) {
    if (pos <= 0) {
        throw "This location does not exist";
    }

    if (pos == 1){
        removeHead(L);
        return;
    }

    if (L->pHead == L->pTail && pos == 1){
        L->pHead = nullptr;
        L->pTail = nullptr;
    }

    int count = 1;
    Node* tmp = L->pHead;

    while (count != pos){
        tmp = tmp->pNext;

        if (tmp == nullptr){
            throw "This location does not exist";
        }

        count++;
    }

    if (tmp->pNext == nullptr){
        removeTail(L);
        return;
    }

    Node* tmpNext = tmp->pNext;
    tmp->key = tmpNext->key;
    tmp->pNext = tmpNext->pNext;

    if (tmpNext->pNext == nullptr){
        L->pTail = tmp;
    }

    delete tmpNext;
    tmpNext = nullptr;
}

void removeAll ( List *& L ) {
    if (isEmpty(L)){
        throw myex1;
    }

    Node* tmp = L->pHead;

    while (tmp != nullptr){
        L->pHead = tmp->pNext;
        delete tmp;
        tmp = L->pHead;
    }
    
    L->pTail = nullptr;
    delete L;
    L = nullptr;
}

void removeBefore ( List * L , int val ) {
    if (isEmpty(L)){
        throw myex1;
    }

    if (L->pHead == L->pTail){
        throw "Singly linked list has one element";
    }

    if (L->pHead->key == val){
        throw "cannot remove the element preceding the first element in singly linkde list" ;
    }

    Node* tmp = L->pHead;
    int count = 1;

    while ( tmp != nullptr){
        if (tmp->pNext != nullptr && tmp->pNext->key == val){
            removePos(L, count);
            return;
        }
        tmp = tmp->pNext;
        ++count;
    }
}

void removeAfter ( List * L , int val ) {
    if (isEmpty(L)){
        throw myex1;
    }

    if (L->pTail->key == val){
        throw "cannot remove the following element before the last element in singly linked list" ;
    }

    if (L->pHead == L->pTail){
        throw "Singly linked list has one element";
    }

    Node* tmp = L->pHead;
    int count = 1;

    while ( tmp != nullptr){
        if (tmp->key == val){
            removePos(L, count + 1);
            return;
        }
        tmp = tmp->pNext;
        ++count;
    }
}

void printList ( List * L ) {
    Node* tmp = L->pHead;

    while (tmp){
        cout << tmp->key << " ";
        tmp = tmp->pNext;
    }
}

int countElements ( List * L) {
    Node* tmp = L->pHead;
    int count = 0;

    while (tmp){
        ++count;
        tmp = tmp->pNext;
    }

    return count;
}

List * reverseList ( List * L ) {
    List* newL = new List {nullptr, nullptr};

    Node* tmp = L->pHead;

    while(tmp != nullptr){
        addHead(newL, tmp->key);
        tmp = tmp->pNext;
    }

    return newL;
}

void removeDuplicate ( List *& L ) {
    int sizeL = countElements(L);
    Node* tmp = L->pHead;
    Node* tmpPrev = nullptr;

    for (int i = 1; i <= sizeL; i++){
        tmpPrev = tmp->pNext;
        for (int j = i + 1; j <= sizeL; j++){
            if (tmpPrev->key == tmp->key){
                removePos(L, j);
                --sizeL;
                --j;
                continue;
            }
            tmpPrev = tmpPrev->pNext;
        }
        tmp = tmp->pNext;
    }
}

bool removeElement ( List *& L , int val){
    if (isEmpty(L)){
        throw myex1;
    }

    Node* tmp = L->pHead;
    int count = 1;
    bool check = false;

    while (tmp != nullptr){
        if (tmp->key == val){
            check = true;
            tmp = tmp->pNext;
            removePos(L, count);
            continue;
        }
        
        ++count;
        tmp = tmp->pNext;
    }

    return check;
}