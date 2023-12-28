#ifndef _PYPP_H
#define _PYPP_H

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

using strings = std::vector<std::string>;

namespace pypp {

/// @brief Return a copy of the string with leading digit characters removed
///
/// @param s a string
/// @return a copy of @s with leading digits removed
std::string lstripDigit(std::string s);

/// @brief Return a copy of the string with trailing digit characters removed
///
/// @param s a string
/// @return a copy of @s with trailing digits removed
std::string rstripDigit(std::string s);

/// @brief Return a copy of the string with leading alphabetical characters removed
///
/// @param s a string
/// @return a copy of @s with leading alphas removed
std::string lstripAlpha(std::string s);

/// @brief Return a copy of the string with trailing alphabetical characters removed
///
/// @param s a string
/// @return a copy of @s with trailing alphas removed
std::string rstripAlpha(std::string s);

/// @brief Return a copy of the string with leading characters removed
///        if predicate holds true
///
/// @tparam p predicate that determines which characters shall be removed
/// @param s a string
/// @return a copy of @s with leading characters removed if @p holds true
template <typename UnaryPredicate> std::string lstrip(std::string s, UnaryPredicate p)
{
    s.erase(s.begin(), std::find_if_not(s.begin(), s.end(), p));
    return s;
}

/// @brief Return a copy of the string with trailing characters removed
///        if predicate holds true
///
/// @tparam p predicate that determines which characters shall be removed
/// @param s a string
/// @return a copy of @s with trailing characters removed if @p holds true
template <typename UnaryPredicate> std::string rstrip(std::string s, UnaryPredicate p)
{
    s.erase(std::find_if_not(s.rbegin(), s.rend(), p).base(), s.end());
    return s;
}

/// @brief Return a copy of the string with leading and trailing characters removed
///        if predicate holds true
///
/// @tparam p predicate that determines which characters shall be removed
/// @param s a string
/// @return a copy of @s with leading and trailing characters removed if @p holds true
template <typename UnaryPredicate> std::string strip(std::string s, UnaryPredicate p)
{
    return lstrip(rstrip(s, p), p);
}

///@brief Split a string into a vector of strings
///
/// @param  input_s string to split
/// @param  split_on charcater by which to split the string
/// @param  at_most number of (sub)strings generated
/// @return a vector of substrings obtained by splitting @input_s every @split_on
strings split(const std::string& input_s, char split_on, int at_most = -1);

///@brief Split a string into lines and store them as a vector
///
/// @param s string to split
/// @return a vector of substrings obtained by splitting @s on newline characters
strings splitLines(const std::string& s);

///@brief Split the contents of a file into lines and store them as a vector
///
/// @param from_location file path
/// @return a vector of strings containing the lines of the file
/// @note empty lines are discarded
strings splitFileLines(const std::string& from_location);

} // namespace pypp

#endif // PYPP_H
