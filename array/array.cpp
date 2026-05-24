#include "array.h"

IntVector::IntVector(int initSize) {
    maxLength_ = (initSize > 0) ? initSize : INIT_CAP;
    data_ = new int[maxLength_];
    length_ = 0;
}

IntVector::IntVector(const IntVector& other)
    : length_(other.length_), maxLength_(other.maxLength_)
{
    data_ = new int[maxLength_];
    for (int i = 0; i < length_; ++i)
        data_[i] = other.data_[i];
}

IntVector::~IntVector() { delete[] data_; }

IntVector& IntVector::operator=(const IntVector& other) {
    if (this == &other)
        return *this;
    if (maxLength_ != other.maxLength_) {
        delete[] data_;
        data_ = new int[other.maxLength_];
        maxLength_ = other.maxLength_;
    }
    length_ = other.length_;
    for (int i = 0; i < length_; ++i)
        data_[i] = other.data_[i];
    return *this;
}

int& IntVector::at(int pos) {
    if (pos < 0 || pos >= length_)
        throw VectorError();
    return data_[pos];
}

void IntVector::add(int value) {
    addInPos(value, length_);
}

void IntVector::addInPos(int value, int pos) {
    if (pos < 0 || pos > length_)
        throw VectorError();
    if (length_ == maxLength_)
        expand(maxLength_ + 1);
    for (int j = length_; j > pos; --j)
        data_[j] = data_[j - 1];
    data_[pos] = value;
    ++length_;
}

void IntVector::erase(int pos) {
    if (pos < 0 || pos >= length_)
        throw VectorError();
    for (int i = pos; i < length_ - 1; ++i)
        data_[i] = data_[i + 1];
    --length_;
}

int IntVector::size() const { return length_; }

void IntVector::expand(int minRequired) {
    int newCap = (maxLength_ * 2 > minRequired) ? maxLength_ * 2 : minRequired;
    int* buf = new int[newCap];
    for (int i = 0; i < length_; ++i)
        buf[i] = data_[i];
    delete[] data_;
    data_ = buf;
    maxLength_ = newCap;
}

std::ostream& operator<<(std::ostream& os, const IntVector& v) {
    os << "Length: " << v.length_ << std::endl;
    for (int i = 0; i < v.length_; ++i)
        os << v.data_[i] << std::endl;
    return os;
}