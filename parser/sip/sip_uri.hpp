#ifndef SIPPY_PARSER_SIP_SIP_URI_HPP
#define SIPPY_PARSER_SIP_SIP_URI_HPP

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>

namespace sippy::parser::sip {

using headers_t    = std::unordered_map<std::string, std::string>;
using parameters_t = std::unordered_map<std::string, std::string>;

struct sip_uri {
    parameters_t parameters;
    headers_t headers;

    std::optional<std::string> user;
    std::optional<std::string> password;

    std::optional<std::uint16_t> port;
    std::string host;

    bool is_secure;
};

} // namespace sippy::parser::sip

#endif
