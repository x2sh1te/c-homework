#include "linelist.h"


template<typename U>
Node<U>::Node(const U& v, Node* n) : value(v), link(n) {}

template<typename U>
const U& Node<U>::read() const { return value; }

template<typename U>
Node<U>* Node<U>::next() { return link; }


template<typename U>
LinkedCircle<U>::LinkedCircle() : head(nullptr) {}

template<typename U>
LinkedCircle<U>::~LinkedCircle() {
    while (head)
        popFront();
}

template<typename U>
void LinkedCircle<U>::popFront() {
    if (head) {
        Node<U>* t = head->link;
        delete head;
        head = t;
    }
}

template<typename U>
void LinkedCircle<U>::popAfter(Node<U>* ref) {
    if (ref && ref->link) {
        Node<U>* rm = ref->link;
        ref->link = rm->link;
        delete rm;
    }
}

template<typename U>
void LinkedCircle<U>::pushFront(const U& val) {
    head = new Node<U>(val, head);
}

template<typename U>
void LinkedCircle<U>::pushAfter(Node<U>* after, const U& val) {
    if (after) {
        after->link = new Node<U>(val, after->link);
    }
}

template<typename U>
Node<U>* LinkedCircle<U>::getHead() {
    return head;
}

template<typename U>
std::ostream& operator<<(std::ostream& os, LinkedCircle<U>& c) {
    Node<U>* p = c.head;
    if (!p)
        os << "пустл";
    while (p) {
        os << p->read() << " ";
        p = p->next();
    }
    return os;
}

template class LinkedCircle<int>;
template class Node<int>;
template std::ostream& operator<<(std::ostream&, LinkedCircle<int>&);