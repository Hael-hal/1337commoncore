/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyi <mbouyi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 00:19:44 by mbouyi            #+#    #+#             */
/*   Updated: 2026/04/30 02:04:43 by mbouyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <cstdlib>

class PmergeMe
{
    private:
        std::vector<int> vec;
        std::deque<int> deq;
        void insertvector(std::vector<int>& v);
        void insertdeque(std::deque<int>& d);
        std::vector<int> getJacobs(int n);

    public:
        PmergeMe();
        PmergeMe(const PmergeMe& obj);
        PmergeMe& operator=(const PmergeMe& obj);
        ~PmergeMe();
        bool parse(int argc, char** argv);
        void sort();
};
#endif