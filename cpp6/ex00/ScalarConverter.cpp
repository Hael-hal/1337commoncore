#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {
}

ScalarConverter::ScalarConverter(const ScalarConverter &other) {
  *this = other;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other) {
  (void)other;
  return (*this);
}

ScalarConverter::~ScalarConverter() {
}


bool ScalarConverter::isInt(const std::string& literal)
{
  size_t i = 0;
  if (literal.empty()) return false;
  if (literal[0] == '-' || literal[0] == '+') i++;
  if (i == literal.length()) return false;
  for (; i < literal.length(); i++)  
  {
    if (!std::isdigit(literal[i])) return false;
  }
  return true;
}

bool ScalarConverter::isChar(const std::string& literal)
{
  if (literal.length() != 1) return false;
  if (std::isdigit(literal[0])) return false;
  if (!std::isprint(literal[0])) return false;
  return true;
}

bool ScalarConverter::isDouble(const std::string& literal)
{
    bool hasDot = false;
    if (literal.empty()) return false;

    size_t i = 0;
    if (literal[0] == '-' || literal[0] == '+') i++;
    if (i == literal.length()) return false;

    for (; i < literal.length(); i++)
    {
        if (literal[i] == '.')
        {
            if (hasDot) return false;
            hasDot = true;
        }
        else if (!std::isdigit(literal[i]))
            return false;
    }
    return hasDot;
}

bool ScalarConverter::isFloat(const std::string& literal)
{
   if (literal.length() < 2 || literal[literal.length() - 1] != 'f') return false;
   return isDouble(literal.substr(0, literal.length() - 1));
}

bool ScalarConverter::isPseudoLiteral(const std::string& literal)
{
    return (literal == "-inff" || literal == "+inff" || literal == "nanf" ||
            literal == "-inf" || literal == "+inf" || literal == "nan");
}

void ScalarConverter::printFromChar(const std::string& literal)
{
    char c = literal[0];
    std::cout << "char: '" << c << "'" << std::endl;
    std::cout << "int: " << static_cast<int>(c) << std::endl;
    std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(c) << "f" << std::endl;
    std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(c) << std::endl;
}

void ScalarConverter::printFromInt(const std::string& literal)
{
    long l = std::strtol(literal.c_str(), NULL, 10);

    if (l < 0 || l > 255)
        std::cout << "char: impossible" << std::endl;
    else if (!std::isprint(static_cast<int>(l)))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(l) << "'" << std::endl;

    if (l < std::numeric_limits<int>::min() || l > std::numeric_limits<int>::max())
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(l) << std::endl;

    std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(l) << "f" << std::endl;
    std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(l) << std::endl;
}

void ScalarConverter::printFromDouble(const std::string& literal)
{
    double d = std::strtod(literal.c_str(), NULL);

    if (d < 0.0 || d > 255.0)
        std::cout << "char: impossible" << std::endl;
    else if (!std::isprint(static_cast<int>(d)))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;

    if (d < std::numeric_limits<int>::min() || d > std::numeric_limits<int>::max())
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(d) << std::endl;

    std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(d) << "f" << std::endl;
    std::cout << "double: " << std::fixed << std::setprecision(1) << d << std::endl;
}

void ScalarConverter::printFromFloat(const std::string& literal)
{
    float f = std::strtod(literal.c_str(), NULL);

    if (f < 0.0 || f > 255.0)
        std::cout << "char: impossible" << std::endl;
    else if (!std::isprint(static_cast<int>(f)))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(f) << "'" << std::endl;

    if (f < std::numeric_limits<int>::min() || f > std::numeric_limits<int>::max())
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(f) << std::endl;

    std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(f) << "f" << std::endl;
    std::cout << "double: " << std::fixed << std::setprecision(1) << f << std::endl;
}

void ScalarConverter::convert(const std::string& literal)
{
    if (isPseudoLiteral(literal))
    {
        std::cout << "char: impossible\n";
        std::cout << "int: impossible\n";

        if (literal == "nan" || literal == "nanf")
        {
            std::cout << "float: nanf\n";
            std::cout << "double: nan\n";
        }
        else if (literal == "+inf" || literal == "+inff")
        {
            std::cout << "float: +inff\n";
            std::cout << "double: +inf\n";
        }
        else if (literal == "-inf" || literal == "-inff")
        {
            std::cout << "float: -inff\n";
            std::cout << "double: -inf\n";
        }
    }
    else if (isChar(literal))
        printFromChar(literal);
    else if (isInt(literal))
        printFromInt(literal);
    else if (isFloat(literal))
        printFromFloat(literal);
    else if (isDouble(literal))
        printFromDouble(literal);
    else
        std::cerr << "Error: impossible to parse literal." << std::endl;
}
