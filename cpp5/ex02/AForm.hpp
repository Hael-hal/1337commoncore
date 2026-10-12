#ifndef AFORM_H
#define AFORM_H

#include <exception>
#include "Bureaucrat.hpp"
#include <iostream>

class AForm
{
    private:
        const std::string name;
        bool _signed;
        const int sign_grade;
        const int exe_grade;
    public:
        AForm(const std::string & name, const int sign_grade, const int exe_grade);
        virtual ~AForm();
        AForm(const AForm& rhs);  
        AForm& operator=(const AForm& rhs);
        void beSigned(Bureaucrat& b);
        const std::string getName() const;
        int get_to_sign() const;
        int get_to_exe() const ;
        bool check() const;
        void execute(Bureaucrat const & executor) const;
        virtual void executeAction() const = 0;

    class FormNotSignedException : public std::exception
    {
        public:
            const char* what() const throw();
    };

    class GradeTooHighException : public std::exception 
    {
        public:
            const char* what() const throw();
    };

    class GradeTooLowException : public std::exception
    {
        public:
            const char* what() const throw();
    };
};

std::ostream& operator<<(const std::ostream& os, const AForm& f);

#endif
