#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <ctime>
#include <cctype>

namespace Utils {
    std::vector<std::string> split(const std::string& str, char delimiter);
    std::vector<std::string> splitWhitespace(const std::string& str);
    std::string trim(const std::string& str);
    std::string toUpper(const std::string& str);
    std::string toLower(const std::string& str);
    std::string getCurrentDateTime();
    bool isValidNickname(const std::string& nick);
    bool isValidChannelName(const std::string& name);

    template <typename T>
    std::string toString(const T& value) {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }
}

#endif
