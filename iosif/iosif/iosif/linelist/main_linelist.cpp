#include "linelist.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <windows.h>

int main() {
    SetConsoleOutputCP(65001); // чтобы была поддержка русского
    SetConsoleCP(65001);
    int participant_count, step;
    std::cout << "Введидте количество элементов ";
    std::cin >> participant_count;
    std::cout << "Введите шаг: ";
    std::cin >> step;

    clock_t start_time = clock();

    LinkedCircle<int> circle;
    for (int id = participant_count; id > 0; --id) {
        circle.pushFront(id);
    }

    int left = participant_count;
    Node<int>* where = circle.getHead();

    while (left > 1) {
        for (int jump = 1; jump < step - 1; ++jump) {
            where = where->next();
            if (!where->next())
                where = circle.getHead();
        }
        if (step == 1) {
            circle.popFront();
            where = circle.getHead();
        }
        else {
            if (!where->next()) {
                circle.popFront();
                where = circle.getHead();
            }
            else {
                circle.popAfter(where);
                if (!where->next())
                    where = circle.getHead();
                else
                    where = where->next();
            }
        }
        --left;
    }

    int survivor = circle.getHead()->read();
    clock_t end_time = clock();
    double duration = 1.0 * (end_time - start_time) / CLOCKS_PER_SEC;

    std::cout << "Ответ: " << survivor << std::endl;
    std::cout << "Время: " << duration << " сек." << std::endl;

    std::ofstream csv("result.csv", std::ios::app);
    std::ifstream check("result.csv");
    check.seekg(0, std::ios::end);
    if (check.tellg() <= 0) {
        csv << "N;Output;Time" << std::endl;
    }
    csv << participant_count << ";" << survivor << ";" << duration << std::endl;
    return 0;
}