#ifndef SIPPY_PARSER_SIP_VERSION_HPP
#define SIPPY_PARSER_SIP_VERSION_HPP

#include "parser/literal.hpp"
#include "parser/variant.hpp"

namespace sippy::parser::sip {

using sip20_t   = literal<"SIP/2.0">;
using version_t = details::variant<sip20_t>;

} // namespace sippy::parser::sip

#endif
