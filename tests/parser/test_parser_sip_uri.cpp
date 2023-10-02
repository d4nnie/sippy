#include <chrono>

#include <boost/variant2/variant.hpp>
#include <gtest/gtest.h>
#include <parser/grammar/sip_uri.hpp>

using namespace sippy::parser;
using namespace std::string_literals;

namespace variant2 = boost::variant2;

TEST(TestSipUri, IsSecure) {
    auto raw = "sips:2020@172.16.4.172"s;
    sip::sip_uri result{};
    auto start_time = std::chrono::high_resolution_clock::now();
    grammar::sip_uri<decltype(raw)::iterator> parser{};
    auto end_time = std::chrono::high_resolution_clock::now();

    auto begin = raw.begin();
    auto match = qi::parse(begin, raw.end(), parser, result);
    auto time  = end_time - start_time;

    ASSERT_EQ(100, time / std::chrono::nanoseconds(1));

    ASSERT_TRUE(match);
    ASSERT_TRUE(result.is_secure);
    ASSERT_TRUE(result.user.has_value());
    ASSERT_EQ(*result.user, "2020"s);
    ASSERT_EQ(result.host, "172.16.4.172"s);
    ASSERT_FALSE(result.port.has_value());
}

TEST(TestSipUri, IPv4) {
    auto raw = "sip:2020@172.16.4.172"s;
    grammar::sip_uri<decltype(raw)::iterator> parser{};
    sip::sip_uri result{};

    auto begin = raw.begin();
    auto match = qi::parse(begin, raw.end(), parser, result);

    ASSERT_TRUE(match);
    ASSERT_FALSE(result.is_secure);
    ASSERT_TRUE(result.user.has_value());
    ASSERT_EQ(*result.user, "2020"s);
    ASSERT_EQ(result.host, "172.16.4.172"s);
    ASSERT_FALSE(result.port.has_value());
}

TEST(TestSipUri, IPv4WithPort) {
    auto raw = "sip:2020@172.16.4.172:4000"s;
    grammar::sip_uri<decltype(raw)::iterator> parser{};
    sip::sip_uri result{};

    auto begin = raw.begin();
    auto match = qi::parse(begin, raw.end(), parser, result);

    ASSERT_TRUE(match);
    ASSERT_TRUE(result.user.has_value());
    ASSERT_EQ(*result.user, "2020"s);
    ASSERT_EQ(result.host, "172.16.4.172"s);
    ASSERT_TRUE(result.port.has_value());
    ASSERT_EQ(*result.port, 4000);
    ASSERT_FALSE(result.is_secure);
}

TEST(TestSipUri, IPv6) {
    auto raw = "sip:2020@[7e:d2:2bdb:7968:f826::bcd1]"s;
    grammar::sip_uri<decltype(raw)::iterator> parser{};
    sip::sip_uri result{};

    auto begin = raw.begin();
    auto match = qi::parse(begin, raw.end(), parser, result);

    ASSERT_TRUE(match);
    ASSERT_TRUE(result.user.has_value());
    ASSERT_EQ(*result.user, "2020"s);
    ASSERT_EQ(result.host, "7e:d2:2bdb:7968:f826::bcd1"s);
    ASSERT_FALSE(result.port.has_value());
    ASSERT_FALSE(result.is_secure);
}

TEST(TestSipUri, IPv6WithPort) {
    auto raw = "sip:2020@[7e:d2:2bdb:7968:f826::bcd1]:4000"s;
    grammar::sip_uri<decltype(raw)::iterator> parser{};
    sip::sip_uri result{};

    auto begin = raw.begin();
    auto match = qi::parse(begin, raw.end(), parser, result);

    ASSERT_TRUE(match);
    ASSERT_TRUE(result.user.has_value());
    ASSERT_EQ(*result.user, "2020"s);
    ASSERT_EQ(result.host, "7e:d2:2bdb:7968:f826::bcd1"s);
    ASSERT_TRUE(result.port.has_value());
    ASSERT_EQ(*result.port, 4000);
    ASSERT_FALSE(result.is_secure);
}

TEST(TestSipUri, DomainName) {
    auto raw = "sip:2020@atlanta.com"s;
    grammar::sip_uri<decltype(raw)::iterator> parser{};
    sip::sip_uri result{};

    auto begin = raw.begin();
    auto match = qi::parse(begin, raw.end(), parser, result);

    ASSERT_TRUE(match);
    ASSERT_TRUE(result.user.has_value());
    ASSERT_EQ(*result.user, "2020"s);
    ASSERT_EQ(result.host, "atlanta.com"s);
    ASSERT_FALSE(result.port.has_value());
    ASSERT_FALSE(result.is_secure);
}

TEST(TestSipUri, DomainNameWithPort) {
    auto raw = "sip:2020@atlanta.com:4000"s;
    grammar::sip_uri<decltype(raw)::iterator> parser{};
    sip::sip_uri result{};

    auto begin = raw.begin();
    auto match = qi::parse(begin, raw.end(), parser, result);

    ASSERT_TRUE(match);
    ASSERT_TRUE(result.user.has_value());
    ASSERT_EQ(*result.user, "2020"s);
    ASSERT_EQ(result.host, "atlanta.com"s);
    ASSERT_TRUE(result.port.has_value());
    ASSERT_EQ(*result.port, 4000);
    ASSERT_FALSE(result.is_secure);
}

TEST(TestSipUri, AlhanumericUser) {
    auto raw = "sip:user@atlanta.com"s;
    grammar::sip_uri<decltype(raw)::iterator> parser{};
    sip::sip_uri result{};

    auto begin = raw.begin();
    auto match = qi::parse(begin, raw.end(), parser, result);

    ASSERT_TRUE(match);
    ASSERT_TRUE(result.user.has_value());
    ASSERT_EQ(*result.user, "user"s);
    ASSERT_FALSE(result.password.has_value());
    ASSERT_EQ(result.host, "atlanta.com"s);
    ASSERT_FALSE(result.port.has_value());
    ASSERT_FALSE(result.is_secure);
}

TEST(TestSipUri, IPv4WithoutUser) {
    auto raw = "sip:172.16.4.172"s;
    grammar::sip_uri<decltype(raw)::iterator> parser{};
    sip::sip_uri result{};

    auto begin = raw.begin();
    auto match = qi::parse(begin, raw.end(), parser, result);

    ASSERT_TRUE(match);
    ASSERT_FALSE(result.user.has_value());
    ASSERT_EQ(result.host, "172.16.4.172"s);
    ASSERT_FALSE(result.port.has_value());
    ASSERT_FALSE(result.is_secure);
}

TEST(TestSipUri, IPv6WithoutUser) {
    auto raw = "sip:[7e:d2:2bdb:7968:f826::bcd1]"s;
    grammar::sip_uri<decltype(raw)::iterator> parser{};
    sip::sip_uri result{};

    auto begin = raw.begin();
    auto match = qi::parse(begin, raw.end(), parser, result);

    ASSERT_TRUE(match);
    ASSERT_FALSE(result.user.has_value());
    ASSERT_EQ(result.host, "7e:d2:2bdb:7968:f826::bcd1"s);
    ASSERT_FALSE(result.port.has_value());
    ASSERT_FALSE(result.is_secure);
}

TEST(TestSipUri, DomainNameWithoutUser) {
    auto raw = "sip:atlanta.com"s;
    grammar::sip_uri<decltype(raw)::iterator> parser{};
    sip::sip_uri result{};

    auto begin = raw.begin();
    auto match = qi::parse(begin, raw.end(), parser, result);

    ASSERT_TRUE(match);
    ASSERT_FALSE(result.user.has_value());
    ASSERT_EQ(result.host, "atlanta.com"s);
    ASSERT_FALSE(result.port.has_value());
    ASSERT_FALSE(result.is_secure);
}

TEST(TestSipUri, AlhanumericUserWithPassword) {
    auto raw = "sip:user:123@atlanta.com"s;
    grammar::sip_uri<decltype(raw)::iterator> parser{};
    sip::sip_uri result{};

    auto begin = raw.begin();
    auto match = qi::parse(begin, raw.end(), parser, result);

    ASSERT_TRUE(match);
    EXPECT_TRUE(result.user.has_value());
    if (result.user.has_value())
        EXPECT_EQ(*result.user, "user"s);
    EXPECT_TRUE(result.password.has_value());
    if (result.password.has_value())
        EXPECT_EQ(*result.password, "123"s);
    EXPECT_EQ(result.host, "atlanta.com"s);
    EXPECT_FALSE(result.port.has_value());
    EXPECT_FALSE(result.is_secure);
}
