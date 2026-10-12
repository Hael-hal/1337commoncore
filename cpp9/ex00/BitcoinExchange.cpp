/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyi <mbouyi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 23:15:54 by mbouyi            #+#    #+#             */
/*   Updated: 2026/04/30 01:28:10 by mbouyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

static std::string trim(const std::string& s)
{
    size_t start = s.find_first_not_of(" \t\n\r\f\v");
    if(start == std::string::npos)
        return "";
    size_t end = s.find_last_not_of(" \t\n\r\f\v");
    return s.substr(start, end - start + 1);
}

BitcoinExchange::BitcoinExchange()
{
    std::ifstream file("data.csv");
    if(!file.is_open())
        file.open("ex00/data.csv");
    if(!file.is_open())
    {
        std::cout << "Error: could not open file." << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line);
    while(std::getline(file, line))
    {
        size_t pos = line.find(',');
        if(pos == std::string::npos)
            continue;
        std::string date = line.substr(0, pos);
        float value = std::atof(line.substr(pos + 1).c_str());
        data[date] = value;
    }
    file.close();
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& obj)
{
    *this = obj;
}
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& obj)
{
    if(this != &obj)
        data = obj.data;
    return *this;
}
BitcoinExchange::~BitcoinExchange()
{
}
bool BitcoinExchange::isValidDate(const std::string& date)
{
    if(date.length() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    for(size_t i = 0; i < date.length(); i++)
    {
        if(i == 4 || i == 7)
            continue;
        if(!isdigit(date[i]))
            return false;
    }
    int year = std::atoi(date.substr(0, 4).c_str());
    int mth = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());
    if(year < 2009 || year > 2026 || mth < 1 || mth > 12 || day < 1 || day > 31)
        return false;
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if(isLeap && mth == 2)
    {
        if(day > 29)
            return false;
    }
    else if(day > daysInMonth[mth])
        return false;
    return true;
}

void BitcoinExchange::processFile (const std::string& file)
{
    if(data.empty())
        return;
    std::ifstream input(file.c_str());
    if(!input.is_open())
    {
        std::cout << "Error: could not open file." << std::endl;
        return;
    }
    std::string line;
    while(std::getline(input, line))
    {
        if(line.empty())
            continue;
        if(trim(line) == "date | value")
            continue;
        size_t pos = line.find('|');
        if(pos == std::string::npos)
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        std::string date = trim(line.substr(0, pos));
        std::string val = trim(line.substr(pos + 1));
        if(val.empty())
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        bool valid = true;
        int dotCount = 0;
        for(size_t i = 0; i < val.length(); i++)
        {
            if(val[i] == '.')
            {
                dotCount++;
                if(dotCount > 1)
                {
                    valid = false;
                    break;
                }
            }
            else if(val[i] == '-')
            {
                if(i != 0)
                {
                    valid = false;
                    break;
                }
            }
            else if(!isdigit(val[i]))
            {
                valid = false;
                break;
            }
        }
        if(!valid || (val.length() == 1 && (val[0] == '-' || val[0] == '.')))
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        if(!isValidDate(date))
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }
        float value = std::atof(val.c_str());
        if(value < 0)
        {
            std::cout << "Error: not a positive number." << std::endl;
            continue;
        }
        if(value > 1000)
        {
            std::cout << "Error: too large a number." << std::endl;
            continue;
        }
        std::map<std::string, float>::iterator it = data.lower_bound(date);
        if(it == data.begin() && it->first != date)
        {
            std::cout << "Error: bad input => " << date << std::endl;
            continue;
        }
        if(it == data.end())
            --it;
        else if(it->first != date)
            --it;
        std::cout << date << " => " << value << " = " << value * it->second << std::endl;
    }
    input.close();
}
