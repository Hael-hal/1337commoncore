

#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
    try
    {
        Bureaucrat hamza("hamza", 40);
        std::cout << hamza << std::endl;
        Bureaucrat cocokria("cocokria", 100);
        std::cout << cocokria << std::endl;

        Form tax("Taxes", 50, 20);
        hamza.signForm(tax);
        std::cout << tax << std::endl;
        
        Form _private("_private", 30, 10);
        cocokria.signForm(_private);
        std::cout << _private << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
