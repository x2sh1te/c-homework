#include <iostream>
#include "DateTime.h"

using namespace std;

int main()
{
    cout << "Демонстрация модульного класса DateTime " << endl;

    DateTime dt1(2021, 12, 21, 7, 54, 34);
    DateTime dt2(2021, 1, 1, 0, 0, 0);

    cout << "\n1. Вывод даты в разных форматах:" << endl;
    cout << "Объект 1 (ISO): ";
    dt1.printISO();
    cout << "Объект 1 (Числовой): ";
    dt1.printFormatNumeric();
    cout << "Объект 1 (Текстовый): ";
    dt1.printFormatText();
    cout << "Объект 1 (Короткий): ";
    dt1.printFormatShort();

    cout << "\n2. Введите дату в формате yyyy-MM-ddThh:mm:ss: " << endl;
    DateTime dt3;
    cin >> dt3;

    cout << "Вы ввели: ";
    cout << dt3;

    // 3. День недели
    cout << "\n3. Информация о введенной дате:" << endl;
    cout << "День недели: " << dt3.getDayOfWeekString() << endl;

    cout << "\n4. Разница между датами:" << endl;
    double diff = dt1.diffDays(dt2);
    cout << "Разница между dt1 и dt2: " << diff << " дней." << endl;

    return 0;
}