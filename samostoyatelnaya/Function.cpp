#include "function.h"


void Function::display(double x) const {
    std::cout << "f(" << x << ") = " << evaluate(x) << "\n";
}

double Function::differentiate(double x, double h) const {

    return (evaluate(x + h) - evaluate(x - h)) / (2.0 * h);
}

double Function::integrate(double a, double b, int steps) const {
    if (a > b) std::swap(a, b);
    if (steps < 2) steps = 2;
    double h = (b - a) / steps;
    double sum = 0.5 * (evaluate(a) + evaluate(b));
    for (int i = 1; i < steps; ++i) {
        sum += evaluate(a + i * h);
    }
    return sum * h;
}

double Function::findMin(double a, double b, int steps) const {
    if (a > b) std::swap(a, b);
    double h = (b - a) / steps;
    double minVal = std::numeric_limits<double>::max();

    for (int i = 0; i <= steps; ++i) {
        double val = evaluate(a + i * h);
        if (val < minVal) minVal = val;
    }
    return minVal;
}

double Function::findMax(double a, double b, int steps) const {
    if (a > b) std::swap(a, b);
    double h = (b - a) / steps;
    double maxVal = std::numeric_limits<double>::lowest();

    for (int i = 0; i <= steps; ++i) {
        double val = evaluate(a + i * h);
        if (val > maxVal) maxVal = val;
    }
    return maxVal;
}

Hyperbola::Hyperbola(double k, double b) : k(k), b(b) {}
double Hyperbola::evaluate(double x) const {
    if (std::abs(x) < 1e-9) throw std::domain_error("Hyperbola: division by zero");
    return k / x + b;
}

Parabola::Parabola(double a, double b, double c) : a(a), b(b), c(c) {}
double Parabola::evaluate(double x) const {
    return a * x * x + b * x + c;
}

Exponenta::Exponenta(double a, double b, double c) : a(a), b(b), c(c) {}
double Exponenta::evaluate(double x) const {
    return a * std::exp(b * x) + c;
}

Polinom::Polinom(const std::vector<double>& coeffs) : coeffs(coeffs) {
    if (coeffs.empty()) throw std::invalid_argument("Polynom: coefficients cannot be empty");
}
double Polinom::evaluate(double x) const {
    double result = 0.0;
    for (int i = static_cast<int>(coeffs.size()) - 1; i >= 0; --i) {
        result = result * x + coeffs[i];
    }
    return result;
}
