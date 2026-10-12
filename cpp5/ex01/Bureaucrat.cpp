# include "Bureaucrat.hpp"
# include "Form.hpp"

Bureaucrat::Bureaucrat() : name("inkonnu"), grade(1)
{
    std::cout << "default constructor ..." << std::endl;
}

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
    return "Grade is too high! < minimum is 1 >";
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
    return "Grade is too low! < maximum is 150 >";
}

static void  validate_grade(int grade)
{
    if(grade < 1)
        throw Bureaucrat::GradeTooHighException() ;
    if(grade > 150 )
        throw Bureaucrat::GradeTooLowException() ;
}

Bureaucrat::Bureaucrat(const std::string& name, int gr) : name(name) , grade(gr)
{
    std::cout << "Constructing Bureaucrat ..." << std::endl;
    validate_grade(this->grade);
}


Bureaucrat::Bureaucrat(const Bureaucrat& rhs) : name(rhs.name) , grade(rhs.grade)
{
    std::cout << "Copying ..." << std::endl;
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& rhs)
{
    if(this != &rhs)
    {
        this->grade = rhs.grade;
    }
    return *this;
}

Bureaucrat::~Bureaucrat()
{
    std::cout << "destructor pending ..." << name << std::endl;
}

const std::string& Bureaucrat::getName() const
{
    return name;
}

int Bureaucrat::getGrade() const
{
    return grade;
}


void Bureaucrat::increment_Grade()
{
    validate_grade(this->grade + 1);
    this->grade++;
}


void Bureaucrat::decrement_Grade()
{
    validate_grade(this->grade - 1);
    this->grade--;
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b)
{
    os << b.getName() << ", bureaucrat grade " << b.getGrade() << ".";
    return os;
}

void Bureaucrat::signForm(Form& f)
{
    try 
    {
        f.beSigned(*this);
		std::cout << this->name + " signed " + f.getName() << std::endl;
    }
    catch (const std::exception &e)
    {
		std::cout << this->name + " couldn't sign " + f.getName() + " because " + e.what() << std::endl;
    }
}
