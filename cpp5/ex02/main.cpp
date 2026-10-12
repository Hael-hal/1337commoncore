#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
 
int main()
{
    std::srand(std::time(NULL));
    try
    {
        Bureaucrat hamza("hamza", 1);
        ShrubberyCreationForm shub("garden_of");
        hamza.signForm(shub);
        hamza.executeForm(shub);


        RobotomyRequestForm robot("Autom");
        hamza.signForm(robot);
        hamza.executeForm(robot);
            
        PresidentialPardonForm pardon("Batman");
        hamza.signForm(pardon);
        hamza.executeForm(pardon);
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}