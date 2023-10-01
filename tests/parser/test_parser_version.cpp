#include <boost/variant2/variant.hpp>
#include <gtest/gtest.h>
#include <parser/grammar/version.hpp>

using namespace sippy::parser;
using namespace std::string_literals;

namespace variant2 = boost::variant2;

TEST(TestParserVersion20, UpperCase) {
    auto raw = "SIP/2.0"s;
    grammar::version<decltype(raw)::iterator> parser{};
    sip::version_t result{};

    auto begin = raw.begin();
    auto match = qi::parse(begin, raw.end(), parser, result);

    ASSERT_TRUE(match);
    ASSERT_TRUE(variant2::get_if<sip::sip20_t>(&result));
}

TEST(TestParserVersion20, LowerCase) {
    auto raw = "sip/2.0"s;
    grammar::version<decltype(raw)::iterator> parser{};
    sip::version_t result{};

    auto begin = raw.begin();
    auto match = qi::parse(begin, raw.end(), parser, result);

    ASSERT_TRUE(match);
    ASSERT_TRUE(variant2::get_if<sip::sip20_t>(&result));
}

TEST(TestParserVersionError, UnknownVersion) {
    auto raw = "SIP/3.0"s;
    grammar::version<decltype(raw)::iterator> parser{};
    sip::version_t result{};
    auto begin = raw.begin();
    ASSERT_THROW({ qi::parse(begin, raw.end(), parser, result); },
                 sippy::parser::unknown_version_error);
}
