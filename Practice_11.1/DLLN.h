#ifndef DLLN_H
#define DLLN_H

#include <iostream>
template<typename E>
class DLLN {
public:
    DLLN() {
        this->pE = NULL;
        this->prev = this->next = NULL;
    }

    DLLN(E* pE) {
        this->pE = pE;
        this->prev = this->next = NULL;
    }

    ~DLLN() {}

    E* getElem() { return pE; }
    void setElem(E* pE) { this->pE = pE; }

    DLLN<E>* getPrev() { return this->prev; }
    DLLN<E>* getNext() { return this->next; }

    void setPrev(DLLN<E>* p) { this->prev = p; }
    void setNext(DLLN<E>* n) { this->next = n; }

private:
    E* pE;
    DLLN<E>* prev;
    DLLN<E>* next;
};

#endif