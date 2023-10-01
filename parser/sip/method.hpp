#ifndef SIPPHONY_PARSER_SIP_METHOD_HPP
#define SIPPHONY_PARSER_SIP_METHOD_HPP

#include "parser/literal.hpp"
#include "parser/variant.hpp"

namespace sipphony::sip {

using invite_t   = literal<"INVITE">;
using register_t = literal<"REGISTER">;

using method_t = details::variant<invite_t, register_t>;

} // namespace sipphony::sip

#endif
