#include "4vryad.h"
#include <iostream>
using namespace std;

int main(void)
{
    setlocale(LC_ALL, "Russian");
    Field field(true);

    while (!field.isOver())
    {
        field.print();
        cout << "Ходит " <<
            (field.isRedTurnNow() ? "Красный" : "Желтый") <<
            " Выберите от 1-7" << endl;

        int column;
        cin >> column;

        if (!field.makeTurn(column))
            cout << "Выбранно неверное число, попробуйте еще раз (1-7)" << endl;
    }

    field.print();
    field.printResult();
    return 0;
}