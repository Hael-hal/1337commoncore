/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyi <mbouyi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 00:19:49 by mbouyi            #+#    #+#             */
/*   Updated: 2026/04/28 01:57:56 by mbouyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
int main(int argc, char **argv)
{
    if(argc < 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    PmergeMe p;
    if(!p.parse(argc, argv))
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    p.sort();
    return 0;
}