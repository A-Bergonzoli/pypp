#ifndef _PYPP_H
#define _PYPP_H

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using strings = std::vector<std::string>;

namespace pypp {

/// @brief Return a copy of the string with leading digit characters removed
///
/// @param s a string
/// @return a copy of @s with leading digits removed
std::string lstripDigit(std::string s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }));
    return s;
}

/// @brief Return a copy of the string with trailing digit characters removed
///
/// @param s a string
/// @return a copy of @s with trailing digits removed
std::string rstripDigit(std::string s)
{
    s.erase(
        std::find_if(s.rbegin(), s.rend(), [](unsigned char c) { return !std::isdigit(c); }).base(), s.end());
    return s;
}

/// @brief Return a copy of the string with leading alphabetical characters removed
///
/// @param s a string
/// @return a copy of @s with leading alphas removed
std::string lstripAlpha(std::string s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isalpha(c); }));
    return s;
}

/// @brief Return a copy of the string with trailing alphabetical characters removed
///
/// @param s a string
/// @return a copy of @s with trailing alphas removed
std::string rstripAlpha(std::string s)
{
    s.erase(
        std::find_if(s.rbegin(), s.rend(), [](unsigned char c) { return !std::isalpha(c); }).base(), s.end());
    return s;
}

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
/// @param  split_on character by which to split the string
/// @param  at_most number of (sub)strings generated
/// @return a vector of substrings obtained by splitting @input_s every @split_on
strings split(const std::string& input_s, char split_on, int at_most = -1)
{
    strings result {};
    std::string buffer {};
    buffer.reserve(input_s.size());

    if (input_s.empty())
        return result;

    for (const char ch : input_s) {
        if (ch != split_on)
            buffer.push_back(ch);
        else if (!buffer.empty()) {
            result.push_back(buffer);
            buffer.clear();
        }
    }

    if (!buffer.empty())
        result.push_back(buffer);

    if (at_most > 0 and at_most < result.size())
        result.erase(result.begin() + at_most, result.end());

    return result;
}

///@brief Split a string into a vector of strings, return an element of said vector
///
/// @param  input_s string to split
/// @param  split_on character by which to split the string
/// @param  at_most number of (sub)strings generated
/// @param  index of the (sub)string to be returned
/// @return a substring of @input_s, identified by @index
std::string splitThenGetAt(const std::string& input_s, char split_on, std::size_t index)
{
    const auto splits { split(input_s, split_on) };

    return splits.at(index);
}

///@brief Split a string into lines and store them as a vector
///
/// @param s string to split
/// @return a vector of substrings obtained by splitting @s on newline characters
strings splitLines(const std::string& s)
{
    return split(s, '\n');
}

///@brief Split the contents of a file into lines and store them as a vector
///
/// @param from_location file path
/// @return a vector of strings containing the lines of the file
/// @note empty lines are discarded
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

namespace collections {

/// @brief A collection of key-value pairs, where:
///        - elements [Generic] are stored as <Keys>
///        - element counts [int] are stored as <Values>
template <class Key, class Hash = std::hash<Key>> class Counter {
public:
    using vecKeyIt = typename std::vector<Key>::iterator;
    using vecValueIt = typename std::vector<int>::iterator;
    using vecKeyValueIt = typename std::vector<std::pair<Key, int>>::iterator;

    Counter() = default;

    template <class InputIt> Counter(InputIt first, InputIt last)
    {
        for (; first != last; ++first) {
            umap_[*first] += 1;
        }

        keys_.reserve(umap_.size());
        counts_.reserve(umap_.size());
        items_.reserve(umap_.size());
    }

    Counter(const Counter& other) = delete;

    Counter& operator=(const Counter& other) = delete;

    Counter(Counter&& other) = delete;

    Counter& operator=(Counter&& other) = delete;

    /// @brief (Psuedo-) copy-constructor
    ///        Implicit conversion from std::unordered_map<Key, int> -> Counter is allowed
    template <class T> Counter(const std::unordered_map<T, int>& other_map)
    {
        static_assert(std::is_same_v<Key, T> == true,
            "Assignment Error: Can not construct Counter from incompatible Key type: {}");

        this->umap_ = other_map;
    }

    /// @brief (Psuedo-) copy-assignment
    ///        Implicit conversion from std::unordered_map<Key, int> -> Counter is allowed
    template <class T> Counter& operator=(const std::unordered_map<T, int>& other_map)
    {
        static_assert(std::is_same_v<Key, T> == true,
            "Assignment Error: Can not assing to Counter from incompatible Key type: {}");
        // @note, possible TODO : cannot check for equality to existing map;
        // would need to overload operator==

        this->umap_ = other_map;
        return *this;
    }

    /// @brief Retrieve underlying map
    std::unordered_map<Key, int, Hash> getUnderlyingMap() const
    {
        return umap_;
    }

    /// @brief Wrapper of std::unordered_map<>::size()
    std::size_t size()
    {
        return umap_.size();
    }

    /// @brief Wrapper of std::unordered_map<>::empty()
    bool empty()
    {
        return umap_.empty();
    }

    /// @brief Wrapper of std::unordered_map<>::operator[]
    ///
    /// @note Return value is reference to int (int&) to allow to modify it
    /// @note Complexity:
    ///       - avg: constant
    ///       - woc: linear in size
    ///
    /// @param key
    int& operator[](const Key& key)
    {
        typename std::vector<Key>::iterator start {};
        typename std::vector<Key>::iterator end {};
        std::tie(start, end) = this->keys();
        std::set<Key> key_set(start, end);
        if (!key_set.contains(key))
            umap_[key] = 0;
        return umap_[key];
    }
    int& operator[](Key&& key)
    {
        typename std::vector<Key>::iterator start {};
        typename std::vector<Key>::iterator end {};
        std::tie(start, end) = this->keys();
        std::set<Key> key_set(start, end);
        if (!key_set.contains(key))
            umap_[key] = 0;
        return umap_[key];
    }

    /// @brief Return a pair of begin and end iterators to the keys
    ///
    /// @return A pair of iterators to a std::vector<Key>
    std::pair<vecKeyIt, vecKeyIt> keys()
    {
        keys_.clear();
        for (const auto& pair : umap_)
            keys_.push_back(pair.first);

        return std::make_pair<vecKeyIt, vecKeyIt>(keys_.begin(), keys_.end());
    }

    /// @brief Return a pair of begin and end iterarors to the counts
    ///
    /// @return A pair of iterators to a std::vector<int>
    std::pair<vecValueIt, vecValueIt> values()
    {
        counts_.clear();
        for (const auto& pair : umap_)
            counts_.push_back(pair.second);

        return std::make_pair<vecValueIt, vecValueIt>(counts_.begin(), counts_.end());
    }

    /// @brief Return a pair of begin and end iterators to the keys and counts
    ///
    /// @return A pair of iterators to a std::vector<std::pair<Key, int>>
    std::pair<vecKeyValueIt, vecKeyValueIt> items()
    {
        items_.clear();
        for (const auto& pair : umap_)
            items_.push_back(pair);

        return std::make_pair<vecKeyValueIt, vecKeyValueIt>(items_.begin(), items_.end());
    }

    /// @brief Return an iterator over elements, repeating each as many time as its count.
    /// @note If an element's count is < 1 it is ignored
    ///
    /// @return A pair of iterators to a std::vector<Key>
    std::pair<vecKeyIt, vecKeyIt> elements()
    {
        auto vec_pair_key_int = this->mostCommon();

        elems_.clear();
        for (const auto& pair : vec_pair_key_int) {
            int count = pair.second;
            while (count-- > 0)
                elems_.push_back(pair.first);
        }

        return std::make_pair<vecKeyIt, vecKeyIt>(elems_.begin(), elems_.end());
    }

    /// @brief Return the `n` most common elements and their counts sorted by most to least common.
    ///
    /// @param n Max number of elements returned
    /// @return A std::vector of std::pair<Key, int> representing the elements and their corresponding counts
    /// @note By default returns all elements in the Counter
    std::vector<std::pair<Key, int>> mostCommon(int8_t n = 0) const
    {
        std::vector<std::pair<Key, int>> t_v {};
        t_v.reserve(umap_.size());

        for (const auto& pair : umap_)
            t_v.push_back(pair);

        std::sort(std::begin(t_v), std::end(t_v),
            [](const std::pair<Key, int> p1, const std::pair<Key, int> p2) { return p1.second > p2.second; });

        const auto endIt = (n > 0 && n < umap_.size()) ? std::begin(t_v) + n : std::end(t_v);
        return std::vector<std::pair<Key, int>>(std::begin(t_v), endIt);
    }

    /// @brief Return the sum of all counts.
    ///
    /// @return The sum of all counts
    int total() const
    {
        if (umap_.empty())
            return 0;

        int sum { 0 };
        for (const auto& pair : umap_)
            sum += pair.second;

        return sum;
    }

    // for debugging purposes
    void pprint()
    {
        std::cout << "-----" << std::endl;
        for (const auto elem : umap_)
            std::cout << elem.first << ": " << elem.second << std::endl;
        std::cout << "-----" << std::endl;
    }

private:
    std::unordered_map<Key, int, Hash> umap_ {};
    std::vector<Key> elems_ {};
    std::vector<Key> keys_ {};
    std::vector<int> counts_ {};
    std::vector<std::pair<Key, int>> items_ {};
};

template<typename T>
concept TupleLike = requires (T t)
{
    std::get<0>(t);
    std::get<1>(t);
};

struct TupleHash {
    template <TupleLike T>
    auto operator()(const T& t) const noexcept -> std::size_t
    {
        return std::hash<typename std::tuple_element<0, T>::type>{}(std::get<0>(t)) ^
               std::hash<typename std::tuple_element<1, T>::type>{}(std::get<1>(t));
    }
};

} // namespace collections

namespace pypp {

/// @brief Default case, when all other arguments have been dealt with.
///        Advances the last iterator.
template <class Iterator> void advanceIterators(Iterator&& iterator)
{
    std::advance(iterator, 1);
}

/// @brief Advances the first iterator and forwards the rest of the variadic arguments
template <class Iterator, class... Iterators>
void advanceIterators(Iterator&& iterator, Iterators&&... iterators)
{
    std::advance(iterator, 1);
    advanceIterators(std::forward<Iterators>(iterators)...);
}

/// @brief Return an iterable of tuples, where the i-th tuple contains the i-th element
///        from each of the argument iterables.
///        It turns rows into columns, and colums into rows (similar to transposing a matrix)
template <class Iterator, class... Iterators> auto zip(Iterator begin, Iterator end, Iterators... iterators)
{
    std::vector<std::tuple<typename Iterator::value_type, typename Iterators::value_type...>> result {};
    for (; begin != end; ++begin, advanceIterators(iterators...))
        result.push_back(std::make_tuple(*begin, *iterators...));

    return result;
}

} // namespace pypp

#endif // PYPP_H
