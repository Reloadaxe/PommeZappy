#include "parser_utils.h"

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

int convert_assert_str_int(std::string value, std::string source)
{
    if (is_number(value)) {
        return std::stoi(value);
    }
    std::ostringstream stream;
    stream << "Invalid argument provided for : ";
    stream << source;
    stream << " (provided: " << value << ")";
    std::string exception_str = stream.str();
    throw std::invalid_argument(exception_str);
}

int convert_assert_str_int(std::string value, std::string source, int min_value)
{
    if (is_number(value)) {
        int converted_value = std::stoi(value);
        if (converted_value >= min_value)
            return converted_value;
    }
    std::ostringstream stream;
    stream << "Invalid argument provided for : ";
    stream << source;
    stream << " (provided: " << value << ", minimum required is ";
    stream << min_value << ")";
    std::string exception_str = stream.str();
    throw std::invalid_argument(exception_str);
}

int convert_assert_str_int(std::string value, std::string source, int min_value, int max_value)
{
    if (is_number(value)) {
        int converted_value = std::stoi(value);
        if (converted_value >= min_value && converted_value <= max_value)
            return converted_value;
    }
    std::ostringstream stream;
    stream << "Invalid argument provided for :  ";
    stream << source;
    stream << " (provided: " << value << ", minimum required is ";
    stream << min_value << ")";
    std::string exception_str = stream.str();
    throw std::invalid_argument(exception_str);
}

bool assert_regex(std::string value, std::string expression)
{
    std::regex r(expression);
    std::smatch m;
    return std::regex_match(value, m, r);
}

bool assert_ip(std::string value, std::string source)
{
    if (assert_regex(value, "^(?:[0-9]{1,3}\\.){3}[0-9]{1,3}$"))
        return true;
    std::ostringstream stream;
    stream << "Invalid argument provided for : ";
    stream << source;
    stream << " (invalid IP format : " << value << ")";
    std::string exception_str = stream.str();
    throw std::invalid_argument(exception_str);
}
