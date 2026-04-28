#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>
#include <string>
#include <iomanip>

// Объявление класса
class DateTime
{
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    bool isLeap(int y) const;
    int getDaysInMonth(int y, int m) const;
    bool validate() const;
    long long toAbsoluteDays() const;

public:
    DateTime();
    DateTime(int y, int m, int d, int h = 0, int min = 0, int s = 0);

    // Методы вывода
    void printFormatNumeric() const;
    void printFormatText() const;
    void printFormatShort() const;
    void printISO() const;

    int getDayOfWeek() const;
    std::string getDayOfWeekString() const;
    double diffDays(const DateTime &other) const;

    static DateTime getEaster(int y);

    friend std::istream &operator>>(std::istream &in, DateTime &dt);
    friend std::ostream &operator<<(std::ostream &out, const DateTime &dt);
};

#endif