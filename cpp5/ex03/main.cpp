#include "Intern.hpp"
 
int main()
{
    try
    {
        Intern autom;

        AForm* robot;

        robot = autom.makeForm("robotomy request", "Bender");

        Bureaucrat hamza("hamza", 1);

        if (robot)
        {
            hamza.signForm(*robot);
            hamza.executeForm(*robot);

            delete robot;
        }
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}