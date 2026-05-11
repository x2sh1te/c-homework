#include "Rational.h"
#include <cmath>
#include <cstring>

using namespace std;

int gcd_int(int a, int b) {
    a = abs(a);
    b = abs(b);

    if (a == 0) return b;
    if (b == 0) return a;

    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

Rational::Rational() : num(0), den(1) {}

Rational::Rational(int n) : num(n), den(1) {}

Rational::Rational(int n, int d) {
    if (d == 0) {
        num = 0;
        den = 1;
    }
    else {
        num = n;
        den = d;
        simplify();
    }
}

Rational& Rational::simplify() {
    if (den == 0) {
        num = 0;
        den = 1;
        return *this;
    }

    if (den < 0) {
        num = -num;
        den = -den;
    }

    long long g = gcd_int(num, den);

    if (g != 0) {
        num /= g;
        den /= g;
    }

    return *this;
}

Rational& Rational::operator+=(const Rational& r) {
    num = num * r.den + den * r.num;
    den = den * r.den;
    return simplify();
}

Rational Rational::operator+(const Rational& r) const {
    Rational t(*this);
    return t += r;
}

Rational& Rational::operator-=(const Rational& r) {
    num = num * r.den - den * r.num;
    den = den * r.den;
    return simplify();
}

Rational Rational::operator-(const Rational& r) const {
    Rational t(*this);
    return t -= r;
}

Rational& Rational::operator*=(const Rational& r) {
    num *= r.num;
    den *= r.den;
    return simplify();
}

Rational Rational::operator*(const Rational& r) const {
    return Rational(num * r.num, den * r.den);
}

Rational& Rational::operator/=(const Rational& r) {
    if (r.num == 0) {
        cout << "Ошибка: деление на ноль!" << endl;
        num = 0;
        den = 1;
        return *this;
    }

    num *= r.den;
    den *= r.num;

    return simplify();
}

Rational Rational::operator/(const Rational& r) const {
    if (r.num == 0) {
        cout << "Ошибка: деление на ноль!" << endl;
        return Rational(0, 1);
    }
    return Rational(num * r.den, den * r.num);
}


bool Rational::operator==(const Rational& r) const {
    return (long long)num * r.den == (long long)r.num * den;
}

bool Rational::operator!=(const Rational& r) const {
    return !(*this == r);
}

bool Rational::operator<(const Rational& r) const {
    return (long long)num * r.den < (long long)r.num * den;
}

bool Rational::operator<=(const Rational& r) const {
    return *this < r || *this == r;
}

bool Rational::operator>(const Rational& r) const {
    return (long long)num * r.den > (long long)r.num * den;
}

bool Rational::operator>=(const Rational& r) const {
    return *this > r || *this == r;
}
double Rational::toDouble() const {
    return static_cast<double>(num) / den;
}
long long gcd_ll(long long a, long long b) {
    a = llabs(a);
    b = llabs(b);
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a == 0 ? 1 : a;
}

Rational Rational::fromDouble(double d) {
    if (fabs(d) < 1e-12)
        return Rational(0, 1);

    bool negative = d < 0;
    d = fabs(d);

    uint64_t bits;
    memcpy(&bits, &d, sizeof(double));

    int exp = (bits >> 52) & 0x7FF;
    uint64_t mant = bits & ((1ULL << 52) - 1);

    if (exp == 0x7FF) return Rational(0, 1);

    long long num = mant;
    long long den = 1;

    if (exp == 0) {
        den = 1LL << 52;
    }
    else {
        num |= (1ULL << 52);
        int shift = exp - 1023 - 52;

        if (shift >= 0)
            num <<= shift;
        else
            den <<= -shift;
    }

    long long g = gcd_ll(num, den);
    if (g > 0) {
        num /= g;
        den /= g;
    }

    while ((num > INT32_MAX || den > INT32_MAX) && den > 1) {
        num /= 2;
        den /= 2;
    }

    long long best_num = num;
    long long best_den = den;
    double best_error = 1e9;

    for (long long test_den = 1; test_den <= 1000000; ++test_den) {
        long long test_num = (long long)round(d * test_den);
        double err = fabs(d - static_cast<double>(test_num) / test_den);

        if (err < best_error) {
            best_error = err;
            best_num = test_num;
            best_den = test_den;
        }

        if (best_error < 1e-10) break;
    }

    if (negative) best_num = -best_num;

    if (best_error < 1e-9 || best_den < den / 2) {
        return Rational((int)best_num, (int)best_den);
    }

    if (num > INT32_MAX || den > INT32_MAX || den <= 0)
        return Rational(0, 1);

    return Rational((int)num, (int)den);
}

void KvUrav(const Rational& a, const Rational& b, const Rational& c) {
    double A = a.toDouble();
    double B = b.toDouble();
    double C = c.toDouble();

    cout << "Уравнение: " << a << "x^2 + " << b << "x + " << c << " = 0\n";
    double D = B * B - 4.0 * A * C;
    cout << "Дискриминант равен = " << D << endl;
    if (D < 0) {
        cout << "Нет действительных корней\n";
        return;
    }
    double sqrtD = sqrt(D);
    if (fabs(D) < 1e-12) {
        cout << "x=" << Rational::fromDouble(-B / (2.0 * A)) << endl;
    }
    else {
        cout << "x1=" << Rational::fromDouble((-B + sqrtD) / (2.0 * A)) << endl;
        cout << "x2=" << Rational::fromDouble((-B - sqrtD) / (2.0 * A)) << endl;
    }
}

ostream& operator<<(ostream& os, const Rational& r) {
    if (r.den == 1) os << r.num;
    else if (r.num == 0) os << 0;
    else os << r.num << "/" << r.den;
    return os;
}