#pragma once
#include <iostream>

constexpr int INIT_CAP = 10;

class VectorError {};

class IntVector {
    int* data_;
    int length_, maxLength_;

    void expand(int minRequired);

public:
    explicit IntVector(int initSize = INIT_CAP);
    IntVector(const IntVector& other);
    ~IntVector();

    IntVector& operator=(const IntVector& other);

    int& at(int pos);                 
    int size() const;

    void add(int value);              
    void addInPos(int value, int pos); 
    void erase(int pos);              

    friend std::ostream& operator<<(std::ostream&, const IntVector&);
};