#ifndef B_HH
#define B_HH

#include <iostream>

class Form;

class Bureaucrat
{
    private:
        const std::string name;
        int grade;
    public:
        Bureaucrat();
        Bureaucrat(const std::string& name, int grade);
        Bureaucrat(const Bureaucrat& rhs);
        Bureaucrat& operator=(const Bureaucrat& rhs);
        ~Bureaucrat();
        void increment_Grade();
        void decrement_Grade();
        const std::string& getName() const;
        int getGrade() const;
        void signForm(Form& f);
        class GradeTooHighException : public std::exception 
        {
            public:
                virtual const char* what() const throw();
        };

        class GradeTooLowException : public std::exception {
            public:
               virtual const char* what() const throw();
        };
        
};
    
std::ostream& operator<<(std::ostream &os, const Bureaucrat& b);
#endif
