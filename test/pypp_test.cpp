#include "../pypp.h"
#include "gtest/gtest.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>

using strings = std::vector<std::string>;

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
