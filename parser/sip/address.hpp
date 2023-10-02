#ifndef SIPPHONY_PARSER_SIP_ADDRESS_HPP
#define SIPPHONY_PARSER_SIP_ADDRESS_HPP

#include <cstdint>
#include <string>

namespace sippy::parser::sip {

enum class address_type_t : std::uint_fast8_t {
    fqdn,
    ipv4,
    ipv6
};

struct address {
    std::string value;
    std::uint16_t port;
    address_type_t type;
};

} // namespace sippy::parser::sip

#endif SIPPHONY_PARSER_SIP_ADDRESS_HPP
