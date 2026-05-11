#pragma once
#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
using namespace std;

class ArrayException
{
};

class Array
{
private:
    int* ptr;     // указатель на динамический массив
    int size;     // текущий размер
    int capacity; // вместимость

public:
    explicit Array(int startCapacity = 10);
    Array(const Array& arr);
    ~Array();

    Array& operator=(const Array& arr);

    // оператор индексации
    int& operator[](int index);

    void insert(int elem, int index);
    void insert(int elem);
    void remove(int index);
    int getSize() const;

    // увеличение вместимости
    void increaseCapacity(int newCapacity);
};

#endif