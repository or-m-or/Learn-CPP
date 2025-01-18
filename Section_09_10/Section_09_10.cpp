#include <iostream>
#include <cassert>
using namespace std;

class Fraction
{
private:
    int m_numerator;
    int m_denominator;
public:
    Fraction(char) = delete;

    // explicit 사용할 경우 doSomething(7) 동작 안함
    explicit Fraction(int num = 0, int den = 1)
        : m_numerator(num), m_denominator(den)
    {
        assert(den != 0);
    }

    Fraction(const Fraction& fraction) // 복사 생성자(copy constrctor)
        : m_numerator(fraction.m_numerator), m_denominator(fraction.m_denominator)
    {
        cout << "Copy constructor called" << endl;
    }

    friend std::ostream& operator << (std::ostream& out, const Fraction& f)
    {
        out << f.m_numerator << " / " << f.m_denominator << endl;
        return out;
    }
};

void doSomething(Fraction frac) {
    cout << frac << endl;
}

int main()
{
    // Fraction frac('a'); // delete 키워드에 의해 막힘
    Fraction frac(7);        

    doSomething(frac);           
    doSomething(Fraction(7));
    // doSomething(7); // explicit 에 의해 막힘

    return 0;
}