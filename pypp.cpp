#include "pypp.h"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <utility>

namespace {

// Utility to print std::string s
void printString(const std::string& s)
{
    std::cout << "String: \t{";
    for (char ch : s) {
        std::cout << ch;
    }
    std::cout << "}" << std::endl;
}

} // namespace

namespace pypp {

std::string lstripDigit(std::string s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }));
    return s;
}

std::string rstripDigit(std::string s)
{
    s.erase(
        std::find_if(s.rbegin(), s.rend(), [](unsigned char c) { return !std::isdigit(c); }).base(), s.end());
    return s;
}

std::string lstripAlpha(std::string s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isalpha(c); }));
    return s;
}

std::string rstripAlpha(std::string s)
{
    s.erase(
        std::find_if(s.rbegin(), s.rend(), [](unsigned char c) { return !std::isalpha(c); }).base(), s.end());
    return s;
}

strings split(const std::string& input_s, char ch, int at_most)
{
    strings s {};

    if (input_s.empty())
        return s;

    std::string t_input_s = input_s;
    std::string::size_type pos { 0 };
    auto is_space = [](unsigned char c) { return std::isspace(c); };

    do {
        pos = t_input_s.find(ch);
        s.push_back(strip(t_input_s.substr(0, pos), is_space));
        t_input_s.erase(0, pos + 1);
    } while (pos != std::string::npos);

    if (at_most > 0 and at_most < s.size())
        s.erase(s.begin() + at_most, s.end());

    return s;
}

} // namespace pypp
