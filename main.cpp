#include <iostream>

int main()
{
    enum test
    {
        a = 1,
        b = 2,
        c = 4,

    };
    test t = test::a;

    if (t & test::a)
    {
        std::cout << "a";
        return 1;
    }
    std::cout << "~a";
}