#ifndef F_H
#define F_H

#include "Bureaucrat.hpp"
#include <iostream>

class Form
{
    private:
        const std::string name;
        bool _signed;
        const int sign_grade;
        const int exe_grade;
    public:
        Form(const std::string & name, const int sign_grade, const int exe_grade);
        Form(const Form& rhs);  
        Form& operator=(const Form& rhs);
        ~Form();
        void beSigned(Bureaucrat& b);
        const std::string getName() const;
        int get_to_sign() const;
        int get_to_exe() const ;
        bool check() const;

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

std::ostream& operator<<(std::ostream& os, const Form& f);

#endif
