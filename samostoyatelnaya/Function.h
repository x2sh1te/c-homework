#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <stdexcept>

// Абстрактный базовый класс
class Function {
public:
    virtual ~Function() = default;
    virtual double evaluate(double x) const = 0;
    virtual void display(double x) const;
    virtual double differentiate(double x, double h = 1e-5) const;
    virtual double integrate(double a, double b, int steps = 10000) const;
    virtual double findMin(double a, double b, int steps = 10000) const;
    virtual double findMax(double a, double b, int steps = 10000) const;
};

// Гипербола: f(x) = k/x + b
class Hyperbola : public Function {
private:
    double k, b;
public:
    Hyperbola(double k = 1.0, double b = 0.0);
    double evaluate(double x) const override;
};

// Парабола: f(x) = a*x^2 + b*x + c
class Parabola : public Function {
private:
    double a, b, c;
public:
    Parabola(double a = 1.0, double b = 0.0, double c = 0.0);
    double evaluate(double x) const override;
};

// Экспонента: f(x) = a * exp(b*x) + c
class Exponenta : public Function {
private:
    double a, b, c;
public:
    Exponenta(double a = 1.0, double b = 1.0, double c = 0.0);
    double evaluate(double x) const override;
};

// Полином n-й степени: f(x) = a0 + a1*x + a2*x^2 + ... + an*x^n
class Polinom : public Function {
private:
    std::vector<double> coeffs; // 
public:
    explicit Polinom(const std::vector<double>& coeffs);
    double evaluate(double x) const override;
};
