#include "DateTime.h"
#include <cmath>

bool DateTime::isLeap(int y) const
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int DateTime::getDaysInMonth(int y, int m) const
{
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2 && isLeap(y))
        return 29;
    return days[m];
}

bool DateTime::validate() const
{
    if (year < 1 || month < 1 || month > 12)
        return false;
    if (day < 1 || day > getDaysInMonth(year, month))
        return false;
    if (hour < 0 || hour > 23)
        return false;
    if (minute < 0 || minute > 59)
        return false;
    if (second < 0 || second > 59)
        return false;
    return true;
}

long long DateTime::toAbsoluteDays() const
{
    int y = year, m = month;
    if (m <= 2)
    {
        y--;
        m += 12;
    }
    return 365LL * y + y / 4 - y / 100 + y / 400 + (153 * m - 457) / 5 + day - 1;
}

DateTime::DateTime()
{
    year = 2000;
    month = 1;
    day = 1;
    hour = 0;
    minute = 0;
    second = 0;
}

DateTime::DateTime(int y, int m, int d, int h, int min, int s)
{
    year = y;
    month = m;
    day = d;
    hour = h;
    minute = min;
    second = s;
    if (!validate())
    {
        year = 2000;
        month = 1;
        day = 1;
        hour = 0;
        minute = 0;
        second = 0;
        std::cout << "Warning: Invalid date provided. Reset to default." << std::endl;
    }
}

void DateTime::printFormatNumeric() const
{
    std::cout << day << "." << std::setw(2) << std::setfill('0') << month << "." << year << std::endl;
}

void DateTime::printFormatText() const
{
    const std::string months[] = {"", "января", "февраля", "марта", "апреля", "мая", "июня",
                                  "июля", "августа", "сентября", "октября", "ноября", "декабря"};
    std::cout << day << " " << months[month] << " " << year << std::endl;
}

void DateTime::printFormatShort() const
{
    std::cout << std::setw(2) << std::setfill('0') << day << "."
              << std::setw(2) << std::setfill('0') << month << "."
              << (year % 100) << std::endl;
}

void DateTime::printISO() const
{
    std::cout << year << "-"
              << std::setw(2) << std::setfill('0') << month << "-"
              << std::setw(2) << std::setfill('0') << day << "T"
              << std::setw(2) << std::setfill('0') << hour << ":"
              << std::setw(2) << std::setfill('0') << minute << ":"
              << std::setw(2) << std::setfill('0') << second << std::endl;
}

int DateTime::getDayOfWeek() const
{
    int y = year, m = month, d = day;
    if (m < 3)
    {
        m += 12;
        y--;
    }
    int k = y % 100;
    int j = y / 100;
    int h = (d + 13 * (m + 1) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
    return (h + 6) % 7;
}

std::string DateTime::getDayOfWeekString() const
{
    const std::string days[] = {"Понедельник", "Вторник", "Среда",
                                "Четверг", "Пятница", "Суббота", "Воскресенье", };
    return days[getDayOfWeek()];
}

double DateTime::diffDays(const DateTime &other) const
{
    long long days1 = toAbsoluteDays();
    long long days2 = other.toAbsoluteDays();
    double time1 = (hour * 3600 + minute * 60 + second) / 86400.0;
    double time2 = (other.hour * 3600 + other.minute * 60 + other.second) / 86400.0;
    return (days1 - days2) + (time1 - time2);
}

DateTime DateTime::getEaster(int y)
{
    int a = y % 19;
    int b = y / 100;
    int c = y % 100;
    int d = b / 4;
    int e = b % 4;
    int f = (b + 8) / 25;
    int g = (b - f + 1) / 3;
    int h = (19 * a + b - d - g + 15) % 30;
    int i = c / 4;
    int k = c % 4;
    int l = (32 + 2 * e + 2 * i - h - k) % 7;
    int m = (a + 11 * h + 22 * l) / 451;
    int month = (h + l - 7 * m + 114) / 31;
    int day = ((h + l - 7 * m + 114) % 31) + 1;
    return DateTime(y, month, day, 0, 0, 0);
}

std::istream &operator>>(std::istream &in, DateTime &dt)
{
    char sep1, sep2, sep3, sep4, sep5;
    in >> dt.year >> sep1 >> dt.month >> sep2 >> dt.day >> sep3 >> dt.hour >> sep4 >> dt.minute >> sep5 >> dt.second;
    if (!dt.validate())
    {
        dt = DateTime();
        std::cout << "Дата введена неверно" << std::endl;
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, const DateTime &dt)
{
    dt.printISO();
    return out;
}