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
    return "Doubly linked list is empty.";
  }
} myex1;

struct DNode {
    int key ;
    DNode * pNext ;
    DNode * pPrev ;
};

struct DList {
    DNode * pHead ;
    DNode * pTail ;
};

DNode * createNode (int data ) {
    return new DNode {data, nullptr, nullptr};
}

DList * createList ( DNode * pNode ) {
    return new DList {pNode, pNode};
}

bool isEmpty (DList* L){
    return !L->pHead && !L->pTail;
}

bool addHead ( DList *& L , int data ) {
    DNode* newNode = createNode (data);

    if (!newNode){
        throw myex;
    }

    if (isEmpty(L)){
        L->pHead = newNode;
        L->pTail = newNode;
        return true;
    }

    newNode->pNext = L->pHead;
    L->pHead->pPrev = newNode;
    L->pHead = newNode;

    return true;
}

bool addTail ( DList *& L , int data ) {
    DNode* newNode = createNode (data);

    if (!newNode){
        throw myex;
    }

    if (isEmpty(L)){
        L->pHead = newNode;
        L->pTail = newNode;
        return true;
    }

    L->pTail->pNext = newNode;
    newNode->pPrev = L->pTail;
    L->pTail = newNode;

    return true;
}

bool addPos ( DList *& L , int val , int pos ) {
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
    DNode* tmp = L->pHead;

    while (count != pos){
        tmp = tmp->pNext;
        ++count;

        if (tmp == nullptr) {
            return false;
        }
    }

    DNode* newNode = new (nothrow) DNode {val, tmp, tmp->pPrev};

    if  (!newNode) {
        throw myex;
    }

    tmp->pPrev = newNode;
    newNode->pPrev->pNext = newNode;

    return true;
}

bool addBefore ( DList *& L , int data ,int val ) {
    if (isEmpty(L)){
        return false;
    }

    DNode* tmp = L->pHead;
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

bool addAfter ( DList *& L , int data ,int val ) {
    DNode* tmp = L->pHead;
    int count = 1;

    while (true){
        if (tmp == nullptr){
            break;
        }

        if (tmp->pNext == nullptr && tmp->key == val){
            addTail(L, data);
            return true;
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

void removeHead ( DList *& L ) {
    if (isEmpty(L)){
        throw myex1;
    }

    if (L->pHead == L->pTail){
        delete L->pHead;
        L->pHead = nullptr;
        L->pTail = nullptr;
        return;
    }

    DNode* tmp = L->pHead->pNext;
    delete L->pHead;
    L->pHead = tmp;
    L->pHead->pPrev = nullptr;
}

void removeTail ( DList *& L ) {
    if (isEmpty(L)){
        throw myex1;
    }

    if (L->pHead == L->pTail){
        delete L->pHead;
        L->pHead = nullptr;
        L->pTail = nullptr;
        return;
    }

    DNode* tmp = L->pHead;

    while (tmp->pNext != L->pTail){
        tmp = tmp->pNext;
    }

    delete L->pTail;
    L->pTail = tmp;
    L->pTail->pNext = nullptr;
}

void removePos ( DList *& L , int pos ) {
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
    DNode* tmp = L->pHead;

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

    DNode* tmpPrev = tmp->pPrev;
    tmpPrev->pNext = tmp->pNext;
    tmp->pNext->pPrev = tmpPrev;

    delete tmp;
    tmp = nullptr;
}

void removeAll ( DList *& L ) {
    if (isEmpty(L)){
        throw myex1;
    }

    DNode* tmp = L->pHead;

    while (tmp != nullptr){
        L->pHead = tmp->pNext;
        delete tmp;
        tmp = L->pHead;
    }
    
    L->pTail = nullptr;
    delete L;
    L = nullptr;
}

void removeBefore ( DList * L , int val ) {
    if (isEmpty(L)){
        throw myex1;
    }

    if (L->pHead == L->pTail){
        throw "Singly linked list has one element";
    }

    if (L->pHead->key == val){
        throw "cannot remove the element preceding the first element in singly linkde list" ;
    }

    DNode* tmp = L->pHead;
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

void removeAfter ( DList * L , int val ) {
    if (isEmpty(L)){
        throw myex1;
    }

    if (L->pTail->key == val){
        throw "cannot remove the following element before the last element in singly linked list" ;
    }

    if (L->pHead == L->pTail){
        throw "Singly linked list has one element";
    }

    DNode* tmp = L->pHead;
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

void printList ( DList * L ) {
    DNode* tmp = L->pHead;

    while (tmp != nullptr){
        cout << tmp->key << " ";
        tmp = tmp->pNext;
    }
}

int countElements ( DList * L) {
    DNode* tmp = L->pHead;
    int count = 0;

    while (tmp){
        ++count;
        tmp = tmp->pNext;
    }

    return count;
}

DList * reverseList ( DList * L ) {
    DList* newL = new DList {nullptr, nullptr};

    DNode* tmp = L->pHead;

    while(tmp != nullptr){
        addHead(newL, tmp->key);
        tmp = tmp->pNext;
    }

    return newL;
}

void removeDuplicate ( DList *& L ) {
    int sizeL = countElements(L);
    DNode* tmp = L->pHead;
    DNode* tmpPrev = nullptr;

    for (int i = 1; i <= sizeL; i++){
        tmpPrev = tmp->pNext;
        for (int j = i + 1; j <= sizeL; j++){
            if (tmpPrev->key == tmp->key){
                tmpPrev = tmpPrev->pNext;
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

bool removeElement ( DList *& L , int val){
    if (isEmpty(L)){
        throw myex1;
    }

    DNode* tmp = L->pHead;
    int count = 1;
    bool check = false;

    while (tmp != nullptr){
        if (tmp->key == val){
            tmp = tmp->pNext;
            removePos(L, count);
            check = true;
            continue;
        }
        
        ++count;
        tmp = tmp->pNext;
    }

    return check;
}