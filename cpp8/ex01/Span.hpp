#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <vector>
#include <algorithm>

class Span
{
	private:
		unsigned int	_maxSize;
		std::vector<int>	_numbers;
		Span();
	public:
		Span(unsigned int N);
		Span(const Span& other);
		Span& operator=(const Span& other);
		~Span();

		void addNumber(int num);
		unsigned int shortestSpan() const;
		unsigned int longestSpan() const;

		class SpanFullException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class NotEnoughNumbersException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};

#endif
