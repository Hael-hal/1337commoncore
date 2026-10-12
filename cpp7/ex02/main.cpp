#include "Array.hpp"


int main() {
    Array<int> intArray(5);
    for (unsigned int i = 0; i < intArray.size(); ++i)
        intArray[i] = i * 10;

    for (unsigned int i = 0; i < intArray.size(); ++i)
        std::cout << "intArray[" << i << "] = " << intArray[i] << std::endl;

    Array<std::string> strArray(3);
    strArray[0] = "Hello";
    strArray[1] = "World";
    strArray[2] = "!";

    for (unsigned int i = 0; i < strArray.size(); ++i)
        std::cout << "strArray[" << i << "] = " << strArray[i] << std::endl;

    return 0;
}