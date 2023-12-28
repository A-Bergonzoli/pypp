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

strings splitLines(const std::string& s) { return split(s, '\n'); }

strings splitFileLines(const std::string& from_location)
{
    std::fstream in_f(from_location, std::ios::in);
    std::string line_read {};
    strings lines {};

    if (in_f.is_open()) {
        for (; std::getline(in_f, line_read);)
            if (!line_read.empty())
                lines.emplace_back(line_read);
    } else {
        std::cerr << "Error: could not open file." << std::endl;
    }

    if (lines.empty())
        lines.emplace_back("");

    return lines;
}

} // namespace pypp
