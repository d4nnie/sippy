#ifndef SIPPY_PARSER_GRAMMAR_METHOD_HPP
#define SIPPY_PARSER_GRAMMAR_METHOD_HPP

#include "parser/grammar/qi.hpp"
#include "parser/parser.hpp"
#include "parser/sip/method.hpp"

#include <format>

namespace sippy::parser::grammar::details {

struct method : qi::symbols<char, sip::method_t> {
    method() {
        add(to_lower_t<sip::invite_t>::value, sip::method_t{sip::invite_t{}});
        add(to_lower_t<sip::register_t>::value, sip::method_t{sip::register_t{}});
    }
};

} // namespace sippy::parser::grammar::details

namespace sippy::parser::grammar {

template<class IteratorT>
class method : public qi::grammar<IteratorT, sip::method_t()> {
public:
    method() : method::base_type{start_} {
        start_ = qi::expect[qi::no_case[method_]];
        qi::on_error<qi::fail>(start_, phoenix::bind(&method::fail, qi::_2, qi::_3));
    }

private:
    static auto fail(IteratorT end, IteratorT begin) -> void {
        throw unknown_method_error{
            std::format("Unknown method: \"{}\"! Parser failure.", std::string_view{begin, end})};
    }

    qi::rule<IteratorT, sip::method_t()> start_{};
    details::method method_{};
};

} // namespace sippy::parser::grammar

#endif
