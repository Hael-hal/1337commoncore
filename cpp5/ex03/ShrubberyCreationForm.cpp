#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() 
 : AForm("ShrubberyCreationForm", 145, 137) , target("")
{    
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target)
 : AForm("ShrubberyCreationForm", 145, 137) , target(target)
{    
}


ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& rhs) 
: AForm(rhs) , target(rhs.target)
{    
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& rhs)
{
    if(this != &rhs)
    {
        AForm::operator=(rhs);
        target = rhs.target;
    }
    return *this;    
} 

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

void ShrubberyCreationForm::executeAction() const
{
    std::ofstream f((target + "_shrubbery").c_str());

    if (!f)
        return;

    f << "       /\\       " << std::endl;
    f << "      /**\\      " << std::endl;
    f << "     /****\\     " << std::endl;
    f << "    /******\\    " << std::endl;
    f << "       ||       " << std::endl;

    f.close();
}





