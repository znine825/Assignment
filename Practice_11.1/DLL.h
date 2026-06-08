

#ifndef DLL_H
#define DLL_H

#include <iostream>
#include <string>
#include <mutex>
#include <iomanip>
#include <typeinfo>
#include "DLLN.h"


#define ELEMENTS_PER_LINE 10

template<typename E>
class DLL {

    friend std::ostream& operator<<(std::ostream& fout, const DLL<E>& dll_E) {
        E data;
        if (dll_E.isEmpty()) {
            fout << dll_E.name << " is Empty now !!" << std::endl;
            return fout;
        }

        int count = 0;
        DLLN<E>* p = dll_E.head->getNext();

        while (p != dll_E.tail) {
            count++;
            data = *(p->getElem());
            fout << data << " ";
            p = p->getNext();

            if (count % ELEMENTS_PER_LINE == 0) {
                fout << std::endl;
            }
        }
        fout << std::endl;
        return fout;
    }

public:
    DLL(std::string n);
    ~DLL();

    std::string getName() { return this->name; }
    void setName(std::string n) { name = n; }

   
    bool isEmpty() const {
        return (this->num_entry == 0);
    }

    DLLN<E>* front() const;
    DLLN<E>* back() const;
    DLLN<E>* insertFront(E* pE);
    DLLN<E>* insertBack(E* pE);
    DLLN<E>* insertInOrder(E* pE);
    DLLN<E>* insertInOrderReverse(E* pE);
    DLLN<E>* find(E* pE_Key);
    DLLN<E>* searchInOrder(E* pE_Key);
    DLLN<E>* searchInOrderReverse(E* pE_Key);
    void removeFront();
    void removeBack();
    int getNumEntry() { return num_entry; }
    std::string getElementType() { return element_type; }
    void fprint(std::ostream& fout);

protected:

    DLLN<E>* _insert(DLLN<E>* v, E* pE);
    void _remove(DLLN<E>* v);

    std::string name;
    int num_entry; 
    std::string element_type;

    DLLN<E>* head;
    DLLN<E>* tail;

    std::mutex cs_dll;
};

template<typename E>
DLL<E>::DLL(std::string nm) {
    this->name = nm;
    this->head = new DLLN<E>;
    this->tail = new DLLN<E>;
    this->head->setNext(tail);
    this->tail->setPrev(head);
    this->num_entry = 0;
    this->element_type = typeid(E).name();
}

template<typename E>
DLL<E>::~DLL() {
    while (!isEmpty()) {
        removeFront();
    }
    delete head;
    delete tail;
}

template<typename E>
DLLN<E>* DLL<E>::front() const {
    return head->getNext();
}

template<typename E>
DLLN<E>* DLL<E>::back() const {
    return tail->getPrev();
}

template<typename E>
DLLN<E>* DLL<E>::searchInOrder(E* pE) {
    DLLN<E>* p = head->getNext();
    while (p != tail) {
        if (*(p->getElem()) > *pE)
            break;
        else
            p = p->getNext();
    }
    return p;
}

template<typename E>
DLLN<E>* DLL<E>::searchInOrderReverse(E* pE_Key) {
    DLLN<E>* p = tail;
    while (p != head) {
        if ((p->getPrev() == NULL) || (p->getPrev() == this->head))
            break;
        else if (*(p->getPrev()->getElem()) <= *pE_Key)
            break;
        else
            p = p->getPrev();
    }
    return p;
}

template<typename E>
DLLN<E>* DLL<E>::find(E* pE) {
    DLLN<E>* p = head->getNext();
    while (p != tail) {
        if (*(p->getElem()) == *pE)
            break;
        else
            p = p->getNext();
    }
    if (p == tail) return NULL;
    else return p;
}

template<typename E>
DLLN<E>* DLL<E>::_insert(DLLN<E>* p, E* pE) {
    cs_dll.lock(); 

    DLLN<E>* v = new DLLN<E>; 
    DLLN<E>* u = p->getPrev();

    v->setElem(pE);
    v->setNext(p);
    p->setPrev(v);
    v->setPrev(u);
    u->setNext(v);

    num_entry++;

    cs_dll.unlock(); 
    return v;
}

template<typename E>
DLLN<E>* DLL<E>::insertFront(E* pE) {
    return _insert(head->getNext(), pE);
}

template<typename E>
DLLN<E>* DLL<E>::insertBack(E* pE) {
    return _insert(tail, pE);
}

template<typename E>
DLLN<E>* DLL<E>::insertInOrder(E* pE) {
    DLLN<E>* p = searchInOrder(pE);
    DLLN<E>* v = _insert(p, pE);
    return v;
}

template<typename E>
DLLN<E>* DLL<E>::insertInOrderReverse(E* pE) {
    DLLN<E>* v;
    if (this->num_entry == 0) {
        v = _insert(this->tail, pE);
    }
    else {
        DLLN<E>* p = searchInOrderReverse(pE);
        v = _insert(p, pE);
    }
    return v;
}

template<typename E>
void DLL<E>::_remove(DLLN<E>* p) {
    cs_dll.lock();

    DLLN<E>* u = p->getPrev();
    DLLN<E>* w = p->getNext();


    u->setNext(w);
    w->setPrev(u);

    num_entry--;
    delete p;

    cs_dll.unlock();
}

template<typename E>
void DLL<E>::removeFront() {
    _remove(head->getNext());
}

template<typename E>
void DLL<E>::removeBack() {
    _remove(tail->getPrev());
}

template<typename E>
void DLL<E>::fprint(std::ostream& fout) {
    E data;
    if (isEmpty()) {
        fout << "DLL is Empty now !!" << std::endl;
        return;
    }
    int count = 0;
    DLLN<E>* p = head->getNext();
    while (p != tail) {
        count++;
        data = *(p->getElem());
        fout << data << " ";
        p = p->getNext();
        if (count % ELEMENTS_PER_LINE == 0) {
            fout << std::endl;
        }
    }
    fout << std::endl;
}

#endif