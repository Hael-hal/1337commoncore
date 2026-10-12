#ifndef PRESIDENTIAL_HPP
#define PRESIDENTIAL_HPP

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
private:
    std::string target;

public:
    PresidentialPardonForm();
    PresidentialPardonForm(std::string target);
    PresidentialPardonForm(const PresidentialPardonForm& rhs);
    PresidentialPardonForm& operator=(const PresidentialPardonForm& rhs);
    ~PresidentialPardonForm();

    void executeAction() const;
};

#endif