#include "easyfind.hpp"

int main()
{
	std::vector<int> numbers;
	numbers.push_back(10);
	numbers.push_back(20);
	numbers.push_back(30);

	try
	{
		std::cout << "vector container" << std::endl;
		std::vector<int>::iterator it = easyfind(numbers, 20);
		std::cout << "Found: " << *it << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	std::list<int> values;
	values.push_back(1);
	values.push_back(2);
	values.push_back(3);

	try
	{
		std::cout << "list container" << std::endl;
		std::list<int>::iterator it = easyfind(values, 3);
		std::cout << "Found: " << *it << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
