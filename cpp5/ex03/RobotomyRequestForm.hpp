#ifndef ROBOTOMY_H
#define ROBOTOMY_H

#include "AForm.hpp"
#include <cstdlib>
#include <ctime>

class RobotomyRequestForm : public AForm
{
private:
    std::string target;

public:
    RobotomyRequestForm();
    RobotomyRequestForm(std::string target);
    RobotomyRequestForm(const RobotomyRequestForm& rhs);
    RobotomyRequestForm& operator=(const RobotomyRequestForm& rhs);
    ~RobotomyRequestForm();

    void executeAction() const;
};

#endif