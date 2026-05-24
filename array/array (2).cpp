#include "array.h"
#include <iostream>

int main()
{
    std::setlocale(LC_ALL, "Russian");
    IntVector demoVec(4);
    for (int i = 0; i < 4; ++i)
        demoVec.add(i + 1);
    std::cout << demoVec << std::endl;
    for (int i = 0; i < 8; i += 2)
        demoVec.addInPos(10 + i, i);
    std::cout << demoVec << std::endl;
    for (int i = 1; i < 8; i += 2)
        demoVec.at(i) = 20 + i;
    std::cout << demoVec << std::endl;
    for (int i = 6; i >= 0; i -= 3)
        demoVec.erase(i);
    std::cout << demoVec << std::endl;
    return 0;
}