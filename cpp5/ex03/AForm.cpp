#include "AForm.hpp"

const char* AForm::GradeTooHighException::what() const throw()
{
    return "grade is too high !";
}

const char* AForm::GradeTooLowException::what() const throw()
{
    return "grade is too low !";
}


AForm::AForm(const std::string & name, const int sign_grade, const int exe_grade): name(name), _signed(false) , sign_grade(sign_grade), exe_grade(exe_grade) 
{
    if(this->exe_grade < 1 || this->sign_grade < 1)
        throw GradeTooHighException();
    else if(this->exe_grade > 150 || this->exe_grade > 150)
        throw GradeTooLowException();
    std::cout << "new form to sign" << std::endl;
}

AForm::AForm(const AForm& rhs): name(rhs.name), _signed(rhs._signed), sign_grade(rhs.sign_grade),  exe_grade(rhs.exe_grade)
{
    std::cout << "copying..." << std::endl;
}

AForm& AForm::operator=(const AForm& rhs)
{
    if(this != &rhs)
       this->_signed = rhs._signed;
    return *this;
}

void AForm::beSigned(Bureaucrat& b)
{
    if(b.getGrade() <= this->get_to_sign())
    {
        _signed = true;
    }
    else 
        throw GradeTooLowException();
}

const std::string AForm::getName() const
{
    return(name);
}

int AForm::get_to_sign() const
{
    return(this->sign_grade);
}

int AForm::get_to_exe() const
{
    return(this->exe_grade);
}

bool AForm::check() const
{
    return(this->_signed);
}

AForm::~AForm()
{
    std::cout << "form no longer avalaible" << std::endl;
}

std::ostream& operator<<(std::ostream& os , const AForm& f)
{
    os << "Form entitled: " << f.getName() << " -Signing grade: "
    << f.get_to_sign() << " -Execution grade: " << f.get_to_exe() << '.';
    if(f.check() == true)
        os << " is signed .";
    else
        os << " is not signed .";
    return (os);
}

const char *AForm::FormNotSignedException::what() const throw()
{
    return "This Form is not signed!";
}

void AForm::execute(const Bureaucrat& kaw) const
{
    if(!this->_signed)
        throw FormNotSignedException();
    if(kaw.getGrade() > this->exe_grade)
        throw GradeTooLowException();
    executeAction();
}
