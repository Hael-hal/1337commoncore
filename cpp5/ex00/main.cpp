#include "Bureaucrat.hpp"

int main()
{
    try
    {
        Bureaucrat cocokria("cocokria", 150);
        std::cout << cocokria << std::endl;
        Bureaucrat hamza("hamza", 1);
        hamza.decrement_Grade();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}