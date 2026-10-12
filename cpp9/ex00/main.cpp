/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyi <mbouyi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 23:16:00 by mbouyi            #+#    #+#             */
/*   Updated: 2026/04/19 01:54:38 by mbouyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
int main(int argc, char **argv)
{
    if(argc != 2)
    {
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }
    BitcoinExchange btc;
    btc.processFile(argv[1]);
    return 0;
}