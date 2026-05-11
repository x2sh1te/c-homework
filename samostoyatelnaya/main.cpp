#include "function.h"
#include <iostream>
#include <iomanip>
#include <vector>

void testFunction(const Function& f, const std::string& name, double x, double a, double b) {
    std::cout << "\n========== " << name << " ==========\n";
    std::cout << std::fixed << std::setprecision(4);

    f.display(x);
    std::cout << "Производная f'(" << x << ") = " << f.differentiate(x) << "\n";
    std::cout << "Интеграл ∫[" << a << ", " << b << "] = " << f.integrate(a, b) << "\n";
    std::cout << "Минимум на [" << a << ", " << b << "] = " << f.findMin(a, b) << "\n";
    std::cout << "Максимум на [" << a << ", " << b << "] = " << f.findMax(a, b) << "\n";
}

int main() {
    try {
        // 1. Парабола: f(x) = 2x² - 4x + 1
        Parabola parabola(2.0, -4.0, 1.0);
        testFunction(parabola, "Parabola: f(x) = 2x^2 - 4x + 1", 3.0, -1.0, 3.0);

        // 2. Гипербола: f(x) = 5/x + 2
        Hyperbola hyperbola(5.0, 2.0);
        testFunction(hyperbola, "Hyperbola: f(x) = 5/x + 2", 2.0, 1.0, 5.0);

        // 3. Экспонента: f(x) = 3*exp(0.5x) - 1
        Exponenta expFunc(3.0, 0.5, -1.0);
        testFunction(expFunc, "Exponenta: f(x) = 3*exp(0.5x) - 1", 0.0, 0.0, 2.0);

        // 4. Полином 3-й степени: f(x) = x³ - 6x² + 11x - 6 
        std::vector<double> polyCoeffs = { -6.0, 11.0, -6.0, 1.0 };
        Polinom poly(polyCoeffs);
        testFunction(poly, "Polinom: f(x) = x^3 - 6x^2 + 11x - 6", 1.5, 0.0, 4.0);

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
