#include <boost/variant2/variant.hpp>
#include <gtest/gtest.h>
#include <parser/grammar/method.hpp>

using namespace sippy::parser;
using namespace std::string_literals;

namespace variant2 = boost::variant2;

TEST(TestParserMethodInvite, UpperCase) {
    auto raw = "INVITE"s;
    grammar::method<decltype(raw)::iterator> parser{};
    sip::method_t result{};

    auto begin = raw.begin();
    auto match = qi::parse(begin, raw.end(), parser, result);

    ASSERT_TRUE(match);
    ASSERT_TRUE(variant2::get_if<sip::invite_t>(&result));
}

TEST(TestParserMethodInvite, LowerCase) {
    auto raw = "invite"s;
    grammar::method<decltype(raw)::iterator> parser{};
    sip::method_t result{};

    auto begin = raw.begin();
    auto match = qi::parse(begin, raw.end(), parser, result);

    ASSERT_TRUE(match);
    ASSERT_TRUE(variant2::get_if<sip::invite_t>(&result));
}

TEST(TestParserMethodRegister, UpperCase) {
    auto raw = "REGISTER"s;
    grammar::method<decltype(raw)::iterator> parser{};
    sip::method_t result{};

    auto begin = raw.begin();
    auto match = qi::parse(begin, raw.end(), parser, result);

    ASSERT_TRUE(match);
    ASSERT_TRUE(variant2::get_if<sip::register_t>(&result));
}

TEST(TestParserMethodRegister, LowerCase) {
    auto raw = "register"s;
    grammar::method<decltype(raw)::iterator> parser{};
    sip::method_t result{};

    auto begin = raw.begin();
    auto match = qi::parse(begin, raw.end(), parser, result);

    ASSERT_TRUE(match);
    ASSERT_TRUE(variant2::get_if<sip::register_t>(&result));
}

TEST(TestParserMethodError, Unknown) {
    auto raw = "Hello, World!"s;
    grammar::method<decltype(raw)::iterator> parser{};
    sip::method_t result{};
    auto begin = raw.begin();
    ASSERT_THROW({ qi::parse(begin, raw.end(), parser, result); },
                 sippy::parser::unknown_method_error);
}
