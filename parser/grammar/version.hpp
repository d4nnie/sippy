#ifndef SIPPY_PARSER_GRAMMAR_VERSION_HPP
#define SIPPY_PARSER_GRAMMAR_VERSION_HPP

#include "parser/grammar/qi.hpp"
#include "parser/parser.hpp"
#include "parser/sip/version.hpp"

#include <format>

namespace sippy::parser::grammar::details {

struct version : qi::symbols<char, sip::version_t> {
    version() {
        add(to_lower_t<sip::sip20_t>::value, sip::version_t{sip::sip20_t{}});
    }
};

} // namespace sippy::parser::grammar::details

namespace sippy::parser::grammar {

template<class IteratorT>
class version : public qi::grammar<IteratorT, sip::version_t()> {
public:
    version() : version::base_type{start_} {
        start_ = qi::expect[qi::no_case[version_]];
        qi::on_error<qi::fail>(start_, phoenix::bind(&version::fail, qi::_2, qi::_3));
    }

private:
    static auto fail(IteratorT end, IteratorT begin) -> void {
        throw unknown_version_error{
            std::format("Unknown version: \"{}\"! Parser failure.", std::string_view{begin, end})};
    }

    qi::rule<IteratorT, sip::version_t()> start_{};
    details::version version_{};
};

} // namespace sippy::parser::grammar

#endif
