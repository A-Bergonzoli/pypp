#include "../pypp.h"
#include "gtest/gtest.h"
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

class SplitFixture : public testing::TestWithParam<SplitRecord> {
public:
protected:
};

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
            { { "foo;ba" }, { "r" }, { "" }, { "dead" }, { "c;ode$be; ef" } } },
          { { "foo;ba, r,  ,dead, c;ode$be; ef" }, ';',
              { { "foo" }, { "ba, r,  ,dead, c" }, { "ode$be" }, { "ef" } } },
          { { "foo;ba, r,  ,dead, c;ode$be; ef" }, '$', { { "foo;ba, r,  ,dead, c;ode" }, { "be; ef" } } },
          { { "foo;ba, r,  ,dead, c;ode$be; ef" }, '$', { { "foo;ba, r,  ,dead, c;ode" }, { "be; ef" } }, 5 },
          { { "foo;ba, r,  ,dead, c;ode$be; ef" }, '@', { { "foo;ba, r,  ,dead, c;ode$be; ef" } } },
          { { "" }, ',', {} }, { { "foo;ba, r,  ,dead, c;ode$be; ef" }, ',', { { "foo;ba" }, { "r" } }, 2 } };

INSTANTIATE_TEST_SUITE_P(SplitTests, SplitFixture, testing::ValuesIn(split_records));

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
