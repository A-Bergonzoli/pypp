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

// Trim whitespaces from start of string
inline std::string ltrim(std::string s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
    return s;
}

// Trim whitespaces from end of string
inline std::string rtrim(std::string s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(),
        s.end());
    return s;
}

inline std::string trim(std::string s) { return ltrim(rtrim(s)); }

} // namespace

namespace pypp {

strings split(const std::string& input_s, char ch, int at_most)
{
    strings s {};

    if (input_s.empty())
        return s;

    std::string t_input_s = input_s;
    std::string::size_type pos { 0 };

    do {
        pos = t_input_s.find(ch);
        s.push_back(trim(t_input_s.substr(0, pos)));
        t_input_s.erase(0, pos + 1);
    } while (pos != std::string::npos);

    if (at_most > 0 and at_most < s.size())
        s.erase(s.begin() + at_most, s.end());

    return s;
}

} // namespace pypp
