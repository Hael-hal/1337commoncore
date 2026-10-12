#include "Intern.hpp"

Intern::Intern()
{
}

Intern::Intern(const Intern& rhs)
{
    (void)rhs;
}

Intern& Intern::operator=(const Intern& rhs)
{
    (void)rhs;
    return *this;
}

Intern::~Intern()
{
}

AForm* Intern::makeForm(std::string name, std::string target)
{
    std::string valid[3] =
    {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };

    AForm* Forms[3] =
    {
        new ShrubberyCreationForm(target),
        new RobotomyRequestForm(target),
        new PresidentialPardonForm(target)
    };

    for (int i = 0; i < 3; i++)
    {
        if (name == valid[i])
        {
            std::cout << "Intern creates " << name << std::endl;
            for (int j = 0; j < 3; j++)
            {
                if (j != i)
                    delete Forms[j];
            }

            return Forms[i];
        }
    }
    for (int i = 0; i < 3; i++)
        delete Forms[i];

    std::cout << "Form does not exist" << std::endl;
    return NULL;
}
