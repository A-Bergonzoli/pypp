#include "../pypp.hpp"
#include "gtest/gtest.h"
#include <filesystem>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <string>
#include <tuple>
#include <vector>

using strings = std::vector<std::string>;

/// @brief Fixture class to facilitate parameterized tests of lstripDigit
class LStripDigitFixture : public testing::TestWithParam<std::tuple<std::string, std::string>> { };

TEST_P(LStripDigitFixture, GivenString_WhenLStripDigit_ExpectCorrectResult)
{
    // Given
    const auto s = std::get<0>(GetParam());
    const auto expected = std::get<1>(GetParam());

    // When
    const auto result = pypp::lstripDigit(s);

    // Then
    ASSERT_EQ(result, expected);
}

INSTANTIATE_TEST_SUITE_P(LStripDigitTests, LStripDigitFixture,
    testing::Values(std::make_tuple("abcdef", "abcdef"), std::make_tuple("123abcdef", "abcdef"),
        std::make_tuple("", "")));

/// @brief Fixture class to facilitate parameterized tests of rstripDigit
class RStripDigitFixture : public testing::TestWithParam<std::tuple<std::string, std::string>> { };

TEST_P(RStripDigitFixture, GivenString_WhenRStripDigit_ExpectCorrectResult)
{
    // Given
    const auto s = std::get<0>(GetParam());
    const auto expected = std::get<1>(GetParam());

    // When
    const auto result = pypp::rstripDigit(s);

    // Then
    ASSERT_EQ(result, expected);
}

INSTANTIATE_TEST_SUITE_P(RStripDigitTests, RStripDigitFixture,
    testing::Values(std::make_tuple("abcdef", "abcdef"), std::make_tuple("abcdef123", "abcdef"),
        std::make_tuple("", "")));

/// @brief Fixture class to facilitate parameterized tests of lstripAlpha
class LStripAlphaFixture : public testing::TestWithParam<std::tuple<std::string, std::string>> { };

TEST_P(LStripAlphaFixture, GivenString_WhenLStripAlpha_ExpectCorrectResult)
{
    // Given
    const auto s = std::get<0>(GetParam());
    const auto expected = std::get<1>(GetParam());

    // When
    const auto result = pypp::lstripAlpha(s);

    // Then
    ASSERT_EQ(result, expected);
}

INSTANTIATE_TEST_SUITE_P(LStripAlphaTests, LStripAlphaFixture,
    testing::Values(std::make_tuple("123456", "123456"), std::make_tuple("abc123456", "123456"),
        std::make_tuple("", "")));

/// @brief Fixture class to facilitate parameterized tests of rstripAlpha
class RStripAlphaFixture : public testing::TestWithParam<std::tuple<std::string, std::string>> { };

TEST_P(RStripAlphaFixture, GivenString_WhenRStripAlpha_ExpectCorrectResult)
{
    // Given
    const auto s = std::get<0>(GetParam());
    const auto expected = std::get<1>(GetParam());

    // When
    const auto result = pypp::rstripAlpha(s);

    // Then
    ASSERT_EQ(result, expected);
}

INSTANTIATE_TEST_SUITE_P(RStripAlphaTests, RStripAlphaFixture,
    testing::Values(std::make_tuple("123456", "123456"), std::make_tuple("123456abc", "123456"),
        std::make_tuple("", "")));

/// @brief Fixture class to facilitate parameterized tests of lstrip
class LStripFixture : public testing::TestWithParam<std::tuple<std::string, std::string>> { };

TEST_P(LStripFixture, GivenString_WhenLStripWithPredicate_ExpectCorrectResult)
{
    // Given
    const auto s = std::get<0>(GetParam());
    const auto expected = std::get<1>(GetParam());

    // When
    auto is_space = [](unsigned char ch) { return std::isspace(ch); };
    const auto result = pypp::lstrip(s, is_space);

    // Then
    ASSERT_EQ(result, expected);
}

INSTANTIATE_TEST_SUITE_P(LStripTests, LStripFixture,
    testing::Values(std::make_tuple("a1b2c3", "a1b2c3"), std::make_tuple(" a1b2c3", "a1b2c3"),
        std::make_tuple("  a1b2c3", "a1b2c3"), std::make_tuple("", "")));

/// @brief Fixture class to facilitate parameterized tests of rstrip
class RStripFixture : public testing::TestWithParam<std::tuple<std::string, std::string>> { };

TEST_P(RStripFixture, GivenString_WhenRStripWithPredicate_ExpectCorrectResult)
{
    // Given
    const auto s = std::get<0>(GetParam());
    const auto expected = std::get<1>(GetParam());

    // When
    auto is_space = [](unsigned char ch) { return std::isspace(ch); };
    const auto result = pypp::rstrip(s, is_space);

    // Then
    ASSERT_EQ(result, expected);
}

INSTANTIATE_TEST_SUITE_P(RStripTests, RStripFixture,
    testing::Values(std::make_tuple("a1b2c3", "a1b2c3"), std::make_tuple("a1b2c3 ", "a1b2c3"),
        std::make_tuple("a1b2c3  ", "a1b2c3"), std::make_tuple("", "")));

struct SplitRecord {
    std::string sample;
    char split_on;
    strings expected;
    int at_most = -1;
};

/// @brief Fixture class to facilitate parameterized tests of split
class SplitFixture : public testing::TestWithParam<SplitRecord> { };

TEST_P(SplitFixture, GivenString_WhenSplittingOnSomechar_ExpectCorrectResult)
{
    // Given
    strings expected = GetParam().expected;

    // When
    const auto result = pypp::split(GetParam().sample, GetParam().split_on, GetParam().at_most);

    // Then
    ASSERT_EQ(result, expected);
}

const std::vector<SplitRecord> split_records
    = { { { "foo;ba, r,  ,dead, c;ode$be; ef" }, ',',
            { { "foo;ba" }, { " r" }, { "  " }, { "dead" }, { " c;ode$be; ef" } } },
          { { "foo;ba, r,  ,dead, c;ode$be; ef" }, ';',
              { { "foo" }, { "ba, r,  ,dead, c" }, { "ode$be" }, { " ef" } } },
          { { "foo;ba, r,  ,dead, c;ode$be; ef" }, '$', { { "foo;ba, r,  ,dead, c;ode" }, { "be; ef" } } },
          { { "foo;ba, r,  ,dead, c;ode$be; ef" }, '$', { { "foo;ba, r,  ,dead, c;ode" }, { "be; ef" } }, 5 },
          { { "foo;ba, r,  ,dead, c;ode$be; ef" }, '@', { { "foo;ba, r,  ,dead, c;ode$be; ef" } } },
          { { "" }, ',', {} }, { { "foo;ba, r,  ,dead, c;ode$be; ef" }, ',', { { "foo;ba" }, { " r" } }, 2 },
          { { "ab cd ef gh  i " }, ' ', { { "ab" }, { "cd" }, { "ef" }, { "gh" }, { "i" } } } };

INSTANTIATE_TEST_SUITE_P(SplitTests, SplitFixture, testing::ValuesIn(split_records));

struct SplitFileLinesRecord {
    std::string filepath;
    strings expected;
};

/// @brief Fixture class to facilitate parameterized tests of splitFileLines
class SplitFileLinesFixture : public testing::TestWithParam<SplitFileLinesRecord> { };

TEST_P(SplitFileLinesFixture, Sometest)
{
    // Given
    strings expected = GetParam().expected;

    // When
    const auto result = pypp::splitFileLines(GetParam().filepath);

    // Then
    ASSERT_EQ(result, expected);
}

namespace fs = std::filesystem;
const std::string cpath = fs::current_path().u8string();

const std::vector<SplitFileLinesRecord> split_file_lines_records
    = { { { cpath + "/../test/for_files/input.txt" }, { { "123456789" } } },
          { { cpath + "/../test/for_files/input_multiline.txt" },
              { { "111" }, { "222" }, { "333" }, { "444" }, { "555" } } },
          { { cpath + "/../test/for_files/empty.txt" }, { { "" } } },
          { { cpath + "/../test/for_files/empty_multiline.txt" }, { { "" } } },
          { { cpath + "/../test/for_files/half_empty.txt" }, { { "111" }, { "222" }, { "444" } } } };

INSTANTIATE_TEST_CASE_P(
    SplitFilesLinesTess, SplitFileLinesFixture, testing::ValuesIn(split_file_lines_records));

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
