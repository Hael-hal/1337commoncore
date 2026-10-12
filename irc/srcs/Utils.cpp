#include "../includes/Utils.hpp"

namespace Utils {

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

std::vector<std::string> splitWhitespace(const std::string& str) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream iss(str);
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

std::string toUpper(const std::string& str) {
    std::string result = str;
    for (size_t i = 0; i < result.length(); ++i) {
        result[i] = static_cast<char>(std::toupper(result[i]));
    }
    return result;
}

std::string toLower(const std::string& str) {
    std::string result = str;
    for (size_t i = 0; i < result.length(); ++i) {
        result[i] = static_cast<char>(std::tolower(result[i]));
    }
    return result;
}

std::string getCurrentDateTime() {
    std::time_t rawtime;
    std::tm* timeinfo;
    char buffer[80];

    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return std::string(buffer);
}

bool isValidNickname(const std::string& nick) {
    if (nick.empty() || nick.length() > 9)
        return false;
    // RFC 2812: letter / special first char, followed by letter / digit / special / '-'
    // special = %x5B-60 / %x7B-7D ; [ ] \ ` _ ^ { | }
    char first = nick[0];
    if (!std::isalpha(first) && first != '[' && first != ']' && first != '\\' &&
        first != '`' && first != '^' && first != '{' && first != '|' && first != '}') {
        return false;
    }
    for (size_t i = 1; i < nick.length(); ++i) {
        char c = nick[i];
        if (!std::isalnum(c) && c != '-' && c != '[' && c != ']' && c != '\\' &&
            c != '`' && c != '^' && c != '{' && c != '|' && c != '}') {
            return false;
        }
    }
    return true;
}

bool isValidChannelName(const std::string& name) {
    if (name.empty() || name.length() < 2 || name.length() > 50)
        return false;
    // Must begin with '#' or '&'
    if (name[0] != '#' && name[0] != '&')
        return false;
    for (size_t i = 1; i < name.length(); ++i) {
        char c = name[i];
        if (c == ' ' || c == 7 /* \a / CTRL+G */ || c == ',' || c == ':')
            return false;
    }
    return true;
}

} // namespace Utils
