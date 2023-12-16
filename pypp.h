#ifndef _PYPP_H
#define _PYPP_H

#include <fstream>
#include <string>
#include <vector>

using strings = std::vector<std::string>;

namespace pypp {

///@brief Split a string into a vector of strings
///
/// @param  input_s string to split
/// @param  split_on charcater by which to split the string
/// @param  at_most number of (sub)strings generated
/// @return a vector of substrings obtained by splitting @input_s every @split_on
strings split(const std::string& input_s, char split_on, int at_most = -1);

strings splitlines(const std::string&);

strings splitlines(const std::fstream&);

} // namespace pypp

#endif // PYPP_H
