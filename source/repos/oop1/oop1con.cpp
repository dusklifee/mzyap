#include <iostream>
#include <stdexcept>

class Rational {
private:
    int numerator;   // ���������
    int denominator; // �����������

    // ����� ��� ���������� ����������� ������ �������� (�������� �������)
    int gcd(int a, int b) const {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    // ����� ��� ������������� ����� (���������� � ����������� �����������)
    void reduce() {
        int divisor = gcd(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;

        // ���� ����������� �������������, ��������� ���� � ���������
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    // ����������� �� ��������� (������� ����� 0/1)
    Rational() : numerator(0), denominator(1) {
        std::cout << "Created: " << numerator << "/" << denominator << std::endl;
    }

    // ����������� � �����������
    Rational(int num, int denom) {
        if (denom == 0) {
            throw std::invalid_argument("Denominator cannot be zero.");
        }
        numerator = num;
        denominator = denom;

        std::cout << "Created: " << numerator << "/" << denominator << " (before reduction)" << std::endl;

        reduce(); // �������� ����� � �������������� �����

        std::cout << "Reduced to: " << numerator << "/" << denominator << std::endl;
    }

    // ����� ��� ������ �����
    void display() const {
        if (denominator == 1) {
            std::cout << numerator << std::endl; // ���� ����������� 1, ������� ������ ���������
        }
        else {
            std::cout << numerator << "/" << denominator << std::endl;
        }
    }

    // �������� ��������
    Rational operator+(const Rational& other) const {
        int num = numerator * other.denominator + other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Rational(num, denom); // ��������� ������������� ����� �����������
    }

    // �������� ���������
    Rational operator-(const Rational& other) const {
        int num = numerator * other.denominator - other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Rational(num, denom);
    }

    // �������� ���������
    Rational operator*(const Rational& other) const {
        int num = numerator * other.numerator;
        int denom = denominator * other.denominator;
        return Rational(num, denom);
    }

    // �������� �������
    Rational operator/(const Rational& other) const {
        if (other.numerator == 0) {
            throw std::invalid_argument("Division by zero.");
        }
        int num = numerator * other.denominator;
        int denom = denominator * other.numerator;
        return Rational(num, denom);
    }

    // �������� ��������� �� ���������
    bool operator==(const Rational& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }

    // �������� ��������� �� �����������
    bool operator!=(const Rational& other) const {
        return !(*this == other);
    }

    // ��������� (������)
    bool operator<(const Rational& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }

    // ��������� (������)
    bool operator>(const Rational& other) const {
        return numerator * other.denominator > other.numerator * denominator;
    }

    // ��������� (������ ��� �����)
    bool operator<=(const Rational& other) const {
        return !(*this > other);
    }

    // ��������� (������ ��� �����)
    bool operator>=(const Rational& other) const {
        return !(*this < other);
    }
};

int main() {
    // ������ ������������� ������ Rational
    Rational r1(2, 3);  // ������� ����� 2/3
    Rational r2(4, 6);  // ������� ����� 4/6 (������� ����� ������������)

    Rational sum = r1 + r2;  // �������� ������
    std::cout << "Sum: ";
    sum.display();

    Rational diff = r1 - r2; // ��������� ������
    std::cout << "Difference: ";
    diff.display();

    Rational prod = r1 * r2; // ��������� ������
    std::cout << "Product: ";
    prod.display();

    Rational quot = r1 / r2; // ������� ������
    std::cout << "Quotient: ";
    quot.display();

    return 0;
}
