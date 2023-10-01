#ifndef SIPPHONY_PARSER_SIP_VERSION_HPP
#define SIPPHONY_PARSER_SIP_VERSION_HPP

#include "parser/literal.hpp"
#include "parser/variant.hpp"

namespace sipphony::sip {

using sip20_t   = literal<"SIP/2.0">;
using version_t = details::variant<sip20_t>;

} // namespace sipphony::sip

#endif
