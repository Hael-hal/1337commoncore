#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

Base* generate(void)
{
    int r = rand() % 3;
    if (r == 0)
        return new A();
    else if (r == 1)
        return new B();
    else
        return new C();
}

void identify(Base* p)
{
    if (dynamic_cast<A*>(p) != NULL)
        std::cout << "A\n";
    else if (dynamic_cast<B*>(p) != NULL)
        std::cout << "B\n";
    else if (dynamic_cast<C*>(p) != NULL)
        std::cout << "C\n";
}

void identify(Base& p)
{
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A\n";
    } catch (...) {}
    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "B\n";
    } catch (...) {}
    try {
        (void)dynamic_cast<C&>(p);
        std::cout << "C\n";
    } catch (...) {}
}

int main()
{
    srand(time(NULL));

    Base* obj = generate();
    std::cout << "Pointer identify: ";
    identify(obj);
    std::cout << "Reference identify: ";
    identify(*obj);
    delete obj;

    return 0;
}
