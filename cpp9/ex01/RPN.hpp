/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyi <mbouyi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 04:05:22 by mbouyi            #+#    #+#             */
/*   Updated: 2026/04/30 02:14:30 by mbouyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cstdlib>

class RPN
{
    private:
        std::stack<int> s;
        bool isOperator(char c);
        bool applyOperator(char op);
    public:
        RPN();
        RPN(const RPN& obj);
        RPN& operator=(const RPN& obj);
        ~RPN();
        bool calculate(const std::string& n);
};
#endif