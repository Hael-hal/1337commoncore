#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <cctype> 
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <limits>
#include <iostream>

class ScalarConverter {
private:
  ScalarConverter();
  ScalarConverter(const ScalarConverter &other);
  ScalarConverter &operator=(const ScalarConverter &other);
  ~ScalarConverter();

static bool isChar(const std::string& literal);

static bool isInt(const std::string& literal);

static bool isFloat(const std::string& literal);

static bool isDouble(const std::string& literal);

static bool isPseudoLiteral(const std::string& literal);

static void printFromChar(const std::string& literal);

static void printFromInt(const std::string& literal);

static void printFromFloat(const std::string& literal);

static void printFromDouble(const std::string& literal);

public:
  static void convert(const std::string& literal);
};

#endif // SCALARCONVERTER_HPP
