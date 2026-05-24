#pragma once
#include <iostream>


template<typename U>
class Node {
    U value;
    Node* link;
public:
    Node(const U& v, Node* n);
    const U& read() const;
    Node* next();

    template<typename V> friend class LinkedCircle;
};

template<typename U>
class LinkedCircle {
    Node<U>* head;

    LinkedCircle(const LinkedCircle& src); 
    LinkedCircle& operator=(const LinkedCircle&) = delete;
public:
    LinkedCircle();
    ~LinkedCircle();

    Node<U>* getHead();

    void popFront();
    void popAfter(Node<U>* ref);
    void pushFront(const U& val);
    void pushAfter(Node<U>* after, const U& val);

    template<typename V>
    friend std::ostream& operator<<(std::ostream&, LinkedCircle<V>&);
};