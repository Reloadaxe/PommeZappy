#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <exception>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <regex>

int convert_assert_str_int(std::string value, std::string source);
int convert_assert_str_int(std::string value, std::string source, int min_value);
int convert_assert_str_int(std::string value, std::string source, int min_value, int max_value);
bool assert_ip(std::string value, std::string source);

#endif // PARSER_UTILS_H
