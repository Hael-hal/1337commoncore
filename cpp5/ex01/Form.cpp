#include "Form.hpp"

const char* Form::GradeTooHighException::what() const throw()
{
    return "grade is too high !";
}

const char* Form::GradeTooLowException::what() const throw()
{
    return "grade is too low !";
}

Form::Form(const std::string & name, const int sign_grade, const int exe_grade): name(name), _signed(false) , sign_grade(sign_grade), exe_grade(exe_grade) 
{
    if(this->exe_grade < 1 || this->sign_grade < 1)
        throw GradeTooHighException();
    else if(this->exe_grade > 150 || this->exe_grade > 150)
        throw GradeTooLowException();
    std::cout << "new form to sign" << std::endl;
}

Form::Form(const Form& rhs): name(rhs.name), _signed(rhs._signed), sign_grade(rhs.sign_grade),  exe_grade(rhs.exe_grade)
{
    std::cout << "copying..." << std::endl;
}

Form& Form::operator=(const Form& rhs)
{
    if(this != &rhs)
       this->_signed = rhs._signed;
    return *this;
}

void Form::beSigned(Bureaucrat& b)
{
    if(b.getGrade() <= this->get_to_sign())
    {
        _signed = true;
    }
    else 
        throw GradeTooLowException();
}

const std::string Form::getName() const
{
    return(name);
}

int Form::get_to_sign() const
{
    return(this->sign_grade);
}

int Form::get_to_exe() const
{
    return(this->exe_grade);
}

bool Form::check() const
{
    return(this->_signed);
}

Form::~Form()
{
    std::cout << "form no longer avalaible" << std::endl;
}

std::ostream& operator<<(std::ostream& os , const Form& f)
{
    os << "Form entitled: " << f.getName() << " -Signing grade: "
    << f.get_to_sign() << " -Execution grade: " << f.get_to_exe() << '.';
    if(f.check() == true)
        os << " is signed .";
    else
        os << " is not signed .";
    return (os);
}
