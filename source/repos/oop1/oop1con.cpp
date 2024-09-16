#include <iostream>
#include <stdexcept>

class Rational {
private:
    int numerator;   // числитель
    int denominator; // знаменатель

    // Метод для нахождения наибольшего общего делителя (алгоритм Евклида)
    int gcd(int a, int b) const {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    // Метод для редуцирования дроби (приведение к наименьшему знаменателю)
    void reduce() {
        int divisor = gcd(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;

        // Если знаменатель отрицательный, переносим знак в числитель
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    // Конструктор по умолчанию (создает дробь 0/1)
    Rational() : numerator(0), denominator(1) {
        std::cout << "Created: " << numerator << "/" << denominator << std::endl;
    }

    // Конструктор с параметрами
    Rational(int num, int denom) {
        if (denom == 0) {
            throw std::invalid_argument("Denominator cannot be zero.");
        }
        numerator = num;
        denominator = denom;

        std::cout << "Created: " << numerator << "/" << denominator << " (before reduction)" << std::endl;

        reduce(); // Приводим дробь к редуцированной форме

        std::cout << "Reduced to: " << numerator << "/" << denominator << std::endl;
    }

    // Метод для вывода дроби
    void display() const {
        if (denominator == 1) {
            std::cout << numerator << std::endl; // Если знаменатель 1, выводим только числитель
        }
        else {
            std::cout << numerator << "/" << denominator << std::endl;
        }
    }

    // Операции сложения
    Rational operator+(const Rational& other) const {
        int num = numerator * other.denominator + other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Rational(num, denom); // Результат автоматически будет редуцирован
    }

    // Операции вычитания
    Rational operator-(const Rational& other) const {
        int num = numerator * other.denominator - other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Rational(num, denom);
    }

    // Операции умножения
    Rational operator*(const Rational& other) const {
        int num = numerator * other.numerator;
        int denom = denominator * other.denominator;
        return Rational(num, denom);
    }

    // Операции деления
    Rational operator/(const Rational& other) const {
        if (other.numerator == 0) {
            throw std::invalid_argument("Division by zero.");
        }
        int num = numerator * other.denominator;
        int denom = denominator * other.numerator;
        return Rational(num, denom);
    }

    // Операция сравнения на равенство
    bool operator==(const Rational& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }

    // Операция сравнения на неравенство
    bool operator!=(const Rational& other) const {
        return !(*this == other);
    }

    // Отношения (меньше)
    bool operator<(const Rational& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }

    // Отношения (больше)
    bool operator>(const Rational& other) const {
        return numerator * other.denominator > other.numerator * denominator;
    }

    // Отношения (меньше или равно)
    bool operator<=(const Rational& other) const {
        return !(*this > other);
    }

    // Отношения (больше или равно)
    bool operator>=(const Rational& other) const {
        return !(*this < other);
    }
};

int main() {
    // Пример использования класса Rational
    Rational r1(2, 3);  // Создаем дробь 2/3
    Rational r2(4, 6);  // Создаем дробь 4/6 (которая будет редуцирована)

    Rational sum = r1 + r2;  // Сложение дробей
    std::cout << "Sum: ";
    sum.display();

    Rational diff = r1 - r2; // Вычитание дробей
    std::cout << "Difference: ";
    diff.display();

    Rational prod = r1 * r2; // Умножение дробей
    std::cout << "Product: ";
    prod.display();

    Rational quot = r1 / r2; // Деление дробей
    std::cout << "Quotient: ";
    quot.display();

    return 0;
}
