/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyi <mbouyi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 04:05:19 by mbouyi            #+#    #+#             */
/*   Updated: 2026/04/30 01:45:29 by mbouyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
RPN::RPN() {}

RPN::RPN(const RPN& obj)
{
    *this = obj;
}

RPN& RPN::operator=(const RPN& obj)
{
    if(this != &obj)
        this->s = obj.s;
    return *this;
}

RPN::~RPN() {}

bool RPN::isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool RPN::applyOperator(char op)
{
    if(s.size() < 2)
        return false;
    int b = s.top();
    s.pop();
    int a = s.top();
    s.pop();
    long res = 0;
    if(op == '+')
        res = (long)a + b;
    else if(op == '-')
        res = (long)a - b;
    else if(op == '*')
        res = (long)a * b;
    else if(op == '/')
    {
        if(b == 0)
            return false;
        res = (long)a / b;
    }
    s.push((int)res);
    return true;
}

bool RPN::calculate(const std::string& n)
{
    std::stringstream ss(n);
    std::string token;
    bool hasToken = false;

    while(ss >> token)
    {
        hasToken = true;
        if(token.length() == 1 && isdigit(token[0]))
        {
            s.push(token[0] - '0');
        }
        else if(token.length() == 1 && isOperator(token[0]))
        {
            if(!applyOperator(token[0]))
            {
                std::cout << "Error" << std::endl;
                return false;
            }
        }
        else
        {
            std::cout << "Error" << std::endl;
            return false;
        }
    }
    if(!hasToken || s.size() != 1)
    {
        std::cout << "Error" << std::endl;
        return false;
    }
    std::cout << s.top() << std::endl;
    return true;
}