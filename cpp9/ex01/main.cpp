/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyi <mbouyi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 00:10:14 by mbouyi            #+#    #+#             */
/*   Updated: 2026/04/30 01:42:44 by mbouyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
int main(int argc, char **argv)
{
    if(argc != 2)
    {
        std::cout << "Error" << std::endl;
        return 1;
    }
    RPN rpn;
    if(!rpn.calculate(argv[1]))
        return 1;
    return 0;
}