#ifndef SIPPY_PARSER_GRAMMAR_SIP_URI_HPP
#define SIPPY_PARSER_GRAMMAR_SIP_URI_HPP

#include "parser/grammar/qi.hpp"
#include "parser/sip/sip_uri.hpp"

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/mpl/int.hpp>

BOOST_FUSION_ADAPT_STRUCT(sippy::parser::sip::sip_uri, (bool, is_secure),
                          (std::optional<std::string>, user),
                          (std::optional<std::string>, password), (std::string, host),
                          (std::optional<std::uint16_t>, port),
                          (sippy::parser::sip::parameters_t, parameters),
                          (sippy::parser::sip::headers_t, headers))

namespace sippy::parser::grammar::details {

using userinfo_t =
    boost::optional<boost::fusion::vector<std::string, boost::optional<std::string>>>;

auto assign_is_secure(bool is_secure, sippy::parser::sip::sip_uri& uri) {
    uri.is_secure = is_secure;
}

auto assign_host(std::string& host, sippy::parser::sip::sip_uri& uri) {
    uri.host = std::move(host);
}

auto assign_userinfo(userinfo_t const& value, sippy::parser::sip::sip_uri& uri) -> void {
    if (value)
        uri.user = boost::fusion::at<boost::mpl::int_<0>>(*value);
    if (value && boost::fusion::at<boost::mpl::int_<1>>(*value))
        uri.password = *boost::fusion::at<boost::mpl::int_<1>>(*value);
}

struct is_secure : qi::symbols<char, bool> {
    is_secure() {
        add("sip", false);
        add("sips", true);
    }
};

} // namespace sippy::parser::grammar::details

namespace sippy::parser::grammar {

template<class IteratorT>
class sip_uri : public qi::grammar<IteratorT, sip::sip_uri()> {
public:
    sip_uri() : sip_uri::base_type{start_} {
        auto assign_is_secure = phoenix::bind(&details::assign_is_secure, qi::_1, qi::_val);
        auto assign_host      = phoenix::bind(&details::assign_host, qi::_1, qi::_val);
        auto assign_userinfo  = phoenix::bind(&details::assign_userinfo, qi::_1, qi::_val);

        start_ = qi::expect[uri_];

        uri_ = (schema_[assign_is_secure] >> qi::lit(':') >> userinfo_[assign_userinfo] >>
                host_[assign_host]);

        userinfo_ = -qi::hold[user_ >> -qi::hold[qi::lit(':') >> password_] >> qi::lit('@')];
        user_     = +(+unreserved_ | +user_unreserved_ | escaped_);
        password_ = *(+unreserved_ | +qi::char_("&=+$,") | escaped_);

        host_ = +qi::char_;

        unreserved_      = qi::alnum | mark_;
        user_unreserved_ = qi::char_("&=+$,;?/");
        mark_            = qi::char_("-_.!~*'()");
        escaped_         = qi::char_('%') >> qi::repeat(2)[qi::char_("0-9a-fA-F")];

        schema_ = is_secure_;
    }

private:
    qi::rule<IteratorT, sip::sip_uri()> start_{};
    qi::rule<IteratorT, sip::sip_uri()> uri_{};

    qi::rule<IteratorT, details::userinfo_t> userinfo_;
    qi::rule<IteratorT, std::string()> user_{};
    qi::rule<IteratorT, std::string()> password_{};

    qi::rule<IteratorT, std::string()> host_{};

    qi::rule<IteratorT, char()> user_unreserved_{};
    qi::rule<IteratorT, char()> unreserved_{};
    qi::rule<IteratorT, char()> mark_{};

    qi::rule<IteratorT, std::string()> escaped_{};

    qi::rule<IteratorT, bool()> schema_{}; // true if the schema is "sips", false otherwise
    details::is_secure is_secure_{};
};

} // namespace sippy::parser::grammar

#endif
