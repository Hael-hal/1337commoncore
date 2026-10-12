/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouyi <mbouyi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 02:58:45 by mbouyi            #+#    #+#             */
/*   Updated: 2026/04/30 02:05:39 by mbouyi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe& obj)
{
    vec = obj.vec;
    deq = obj.deq;
}
PmergeMe& PmergeMe::operator=(const PmergeMe& obj)
{
    if(this != &obj)
    {
        vec = obj.vec;
        deq = obj.deq;
    }
    return *this;
}
PmergeMe::~PmergeMe() {}
std::vector<int> PmergeMe::getJacobs(int n)
{
    std::vector<int> jacob;
    jacob.push_back(0);
    jacob.push_back(1);
    while(jacob.back() < n)
    {
        int next = jacob[jacob.size() - 1] + 2 * jacob[jacob.size() - 2];
        jacob.push_back(next);
    }
    return jacob;
}
bool PmergeMe::parse(int argc, char **argv)
{
    for(int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if(arg.empty())
            return false;
        for(size_t j = 0; j < arg.length(); j++)
        {
            if(!isdigit(arg[j]))
                return false;
        }
        char *endptr;
        long n = std::strtol(arg.c_str(), &endptr, 10);
        if(*endptr != '\0' || n <= 0 || n > 2147483647)
            return false;
        vec.push_back((int)n);
        deq.push_back((int)n);
    }
    if(vec.empty())
        return false;
    return true;
}
int BinarySearchV(const std::vector<int>& vec, int val, int low, int high)
{
    while(low < high)
    {
        int mid = low + (high - low) / 2;
        if(vec[mid] < val)
            low = mid + 1;
        else
            high = mid;
    }
    return low;
}
int BinarySearchD(const std::deque<int>& deq, int val, int low, int high)
{
    while(low < high)
    {
        int mid = low + (high - low) / 2;
        if(deq[mid] < val)
            low = mid + 1;
        else
            high = mid;
    }
    return low;
}
void PmergeMe::insertvector(std::vector<int>& v)
{
    bool odd = false;
    int n = 0;
    
    if(v.size() <= 1)
        return;
    if(v.size() % 2 != 0)
    {
        odd = true;
        n = v.back();
        v.pop_back();
    }
    
    std::vector<std::pair<int, int> > pairs;
    for(size_t i = 0; i < v.size(); i+=2)
    {
        int l = v[i];
        int s = v[i + 1];
        if(s > l)
            std::swap(l, s);
        pairs.push_back(std::make_pair(l,s));
    }
    std::vector<int> larger;
    for(size_t i = 0; i < pairs.size(); i++)
        larger.push_back(pairs[i].first);
    insertvector(larger);
    std::vector<bool> used(pairs.size(), false);
    std::vector<int> pend;
    for(size_t i = 0; i < larger.size(); i++)
    {
        for(size_t j = 0; j < pairs.size(); j++)
        {
            if(pairs[j].first == larger[i] && !used[j])
            {
                pend.push_back(pairs[j].second);
                used[j] = true;
                break;
            }
        }
    }
    std::vector<int> main_chain = larger;
    if(pend.empty())
    {
        v = larger;
        return;
    }
    main_chain.insert(main_chain.begin(), pend[0]);
    std::vector<int> jacob = getJacobs(pend.size());
    size_t jacob_index = 3;
    size_t pend_index = 1;
    while(pend_index < pend.size())
    {
        size_t curr;
        if(jacob_index < jacob.size())
            curr = (size_t)jacob[jacob_index];
        else 
            curr = pend.size();
        if(curr > pend.size())
            curr = pend.size();
        for(int k = (int)curr - 1; k >= (int)pend_index; k--)
        {
            int partner = larger[k];
            int partner_pos = 0;
            for(size_t p = 0; p < main_chain.size(); p++)
            {
                if(main_chain[p] == partner)
                {
                    partner_pos = p;
                    break;
                }
            }
            int insert_pos = BinarySearchV(main_chain, pend[k], 0, partner_pos);
            main_chain.insert(main_chain.begin() + insert_pos, pend[k]);
        }
        pend_index = curr;
        jacob_index++;
    }
    if(odd)
    {
        int insert_pos = BinarySearchV(main_chain, n, 0, main_chain.size());
        main_chain.insert(main_chain.begin() + insert_pos, n);
    }
    v = main_chain;
}
void PmergeMe::insertdeque(std::deque<int>& d)
{
    bool odd = false;
    int n = 0;
    
    if(d.size() <= 1)
        return;
    if(d.size() % 2 != 0)
    {
        odd = true;
        n = d.back();
        d.pop_back();
    }
    
    std::vector<std::pair<int, int> > pairs;
    for(size_t i = 0; i < d.size(); i+=2)
    {
        int l = d[i];
        int s = d[i + 1];
        if(s > l)
            std::swap(l, s);
        pairs.push_back(std::make_pair(l,s));
    }
    std::deque<int> larger;
    for(size_t i = 0; i < pairs.size(); i++)
        larger.push_back(pairs[i].first);
    insertdeque(larger);
    std::vector<bool> used(pairs.size(), false);
    std::deque<int> pend;
    for(size_t i = 0; i < larger.size(); i++)
    {  
        for(size_t j = 0; j < pairs.size(); j++)
        {
            if(pairs[j].first == larger[i] && !used[j])
            {
                pend.push_back(pairs[j].second);
                used[j] = true;
                break;
            }
        }
    }
    std::deque<int> main_chain = larger;
    if(pend.empty())
    {
        d = larger;
        return;
    }
    main_chain.insert(main_chain.begin(), pend[0]);
    std::vector<int> jacob = getJacobs(pend.size());
    size_t jacob_index = 3;
    size_t pend_index = 1;
    while(pend_index < pend.size())
    {
        size_t curr;
        if(jacob_index < jacob.size())
            curr = (size_t)jacob[jacob_index];
        else 
            curr = pend.size();
        if(curr > pend.size())
            curr = pend.size();
        for(int k = (int)curr - 1; k >= (int)pend_index; k--)
        {
            int partner = larger[k];
            int partner_pos = 0;
            for(size_t p = 0; p < main_chain.size(); p++)
            {
                if(main_chain[p] == partner)
                {
                    partner_pos = p;
                    break;
                }
            }
            int insert_pos = BinarySearchD(main_chain, pend[k], 0, partner_pos);
            main_chain.insert(main_chain.begin() + insert_pos, pend[k]);
        }
        pend_index = curr;
        jacob_index++;
    }
    if(odd)
    {
        int insert_pos = BinarySearchD(main_chain, n, 0, main_chain.size());
        main_chain.insert(main_chain.begin() + insert_pos, n);
    }
    d = main_chain;
}
void PmergeMe::sort()
{
    std::cout << "Before: ";
    for(size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i];
        if(i + 1 < vec.size())
            std::cout << " ";
    }
    std::cout << std::endl;

    clock_t start = clock();
    insertvector(vec);
    clock_t end = clock();
    double vec_time = double(end - start) / CLOCKS_PER_SEC * 1000000;

    clock_t start2 = clock();
    insertdeque(deq);
    clock_t end2 = clock();
    double deq_time = double(end2 - start2) / CLOCKS_PER_SEC * 1000000;
    
    std::cout << "After: ";
    for(size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i];
        if(i + 1 < vec.size())
            std::cout << " ";
    }
    std::cout << std::endl;
    std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " << std::fixed << std::setprecision(5) << vec_time << " us" << std::endl;
    std::cout << "Time to process a range of " << deq.size() << " elements with std::deque : " << std::fixed << std::setprecision(5) << deq_time << " us" << std::endl;
}