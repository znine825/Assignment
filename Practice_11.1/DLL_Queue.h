#ifndef DLL_QUEUE_H
#define DLL_QUEUE_H
#include <iostream>
#include <string>
#include "DLL.h"

template<typename E>
class DLL_Queue : public DLL<E> {
    friend std::ostream& operator<<(std::ostream& fout, DLL_Queue<E>& dllQ) {
        if (dllQ.isEmpty()) {
            fout << dllQ.name << " is Empty now !!" << std::endl;
            return fout;
        }
        return fout << static_cast<DLL<E>&>(dllQ);
    }

public:
    DLL_Queue(std::string nm);
    ~DLL_Queue();
    E* deQueue();
    DLLN<E>* enQueue(E* pE);
};

template<typename E>
DLL_Queue<E>::DLL_Queue(std::string nm) : DLL<E>(nm) {
}

template<typename E>
DLL_Queue<E>::~DLL_Queue() {
}

template<typename E>
DLLN<E>* DLL_Queue<E>::enQueue(E* pE) {
    return this->insertBack(pE);
}

template<typename E>
E* DLL_Queue<E>::deQueue() {
    if (this->isEmpty()) {
        return NULL;
    }

    E* pE = this->front()->getElem();

    this->removeFront();

    return pE;
}

#endif