#include "array.h"

// конструктор
Array::Array(int startCapacity)
{
    if (startCapacity <= 0)
        capacity = 10;
    else
        capacity = startCapacity;
    ptr = new int[capacity];
    size = 0;
}

// конструктор копирования
Array::Array(const Array& arr)
{
    ptr = new int[arr.capacity];
    size = arr.size;
    capacity = arr.capacity;
    for (int i = 0; i < size; i++)
        ptr[i] = arr.ptr[i];
}

// деструктор
Array::~Array()
{
    delete[] ptr;
}

// оператор присваивания
Array& Array::operator=(const Array& arr)
{
    if (this == &arr)
        return *this;

    if (capacity != arr.capacity)
    {
        delete[] ptr;
        ptr = new int[arr.capacity];
        capacity = arr.capacity;
    }
    size = arr.size;
    for (int i = 0; i < size; i++)
        ptr[i] = arr.ptr[i];
    return *this;
}

// проверка границ
int& Array::operator[](int index)
{
    if (index >= size || index < 0)
        throw ArrayException();
    return ptr[index];
}

// вставка элемента по индексу
void Array::insert(int elem, int index)
{
    if (index < 0 || index > size)
        throw ArrayException();

    if (size == capacity)
        increaseCapacity(size + 1);

    // сдвигаем элементы вправо
    for (int j = size - 1; j >= index; j--)
        ptr[j + 1] = ptr[j];

    ptr[index] = elem;
    size++;
}

// вставка в конец
void Array::insert(int elem)
{
    insert(elem, size);
}

// удаление элемента по индексу
void Array::remove(int index)
{
    if (index < 0 || index >= size)
        throw ArrayException();

    for (int j = index; j < size - 1; j++)
        ptr[j] = ptr[j + 1];

    size--;
}

// увеличение вместимости
void Array::increaseCapacity(int newCapacity)
{
    capacity = (newCapacity < capacity * 2) ? capacity * 2 : newCapacity;
    int* newPtr = new int[capacity];

    for (int i = 0; i < size; i++)
        newPtr[i] = ptr[i];

    delete[] ptr;
    ptr = newPtr;
}

// получение размера
int Array::getSize() const
{
    return size;
}