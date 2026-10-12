#include "Span.hpp"

const char* Span::SpanFullException::what() const throw()
{
	return "Span is full, you can't add a number";
}

const char* Span::NotEnoughNumbersException::what() const throw()
{
	return "atleast two numbers to calculate the distance";
}

Span::Span() : _maxSize(0) {}

Span::Span(unsigned int N) : _maxSize(N) {}

Span::Span(const Span& other) : _maxSize(other._maxSize), _numbers(other._numbers){}

Span& Span::operator=(const Span& other)
{
	if (this != &other)
	{
		this->_maxSize = other._maxSize;
		this->_numbers = other._numbers;
	}
	return *this;
}

Span::~Span() {}

void Span::addNumber(int num)
{
	if (_numbers.size() >= _maxSize)
	{
		throw SpanFullException();
	}
	_numbers.push_back(num);
}

unsigned int Span::longestSpan() const
{
	if (_numbers.size() < 2)
		throw NotEnoughNumbersException();

	// std::vector<int>::const_iterator min = std::min_element(_numbers.begin(), _numbers.end());
	// std::vector<int>::const_iterator max = std::max_element(_numbers.begin(), _numbers.end());
	// int min_val = *min;
	// int max_val = *max;
	int min_val = *std::min_element(_numbers.begin(), _numbers.end());
	int max_val = *std::max_element(_numbers.begin(), _numbers.end());
	return static_cast<unsigned int>(max_val - min_val);
}

unsigned int Span::shortestSpan() const
{
	if (_numbers.size() < 2)
		throw NotEnoughNumbersException();

	std::vector<int> sorted_numbers = _numbers;
	std::sort(sorted_numbers.begin(), sorted_numbers.end());
	unsigned int min_span = static_cast<unsigned int>(sorted_numbers[1] - sorted_numbers[0]);

	for (size_t i = 1; i < sorted_numbers.size() - 1; i++)
	{
		unsigned int current_span = static_cast<unsigned int>(sorted_numbers[i + 1] - sorted_numbers[i]);
		if (current_span < min_span)
		{
			min_span = current_span;
		}
	}
	return min_span;
}
