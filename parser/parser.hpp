#ifndef SIPPHONY_PARSER_PARSER_HPP
#define SIPPHONY_PARSER_PARSER_HPP

#include <stdexcept>
#include <string>

namespace sipphony {

struct parser_failure : std::runtime_error {
    explicit parser_failure(std::string const& what) : std::runtime_error{what} {}

    explicit parser_failure(char const* what) : std::runtime_error{what} {}
};

struct unknown_method_error : parser_failure {
    explicit unknown_method_error(std::string const& what) : parser_failure{what} {}

    explicit unknown_method_error(char const* what) : parser_failure{what} {}
};

struct unknown_version_error : parser_failure {
    explicit unknown_version_error(std::string const& what) : parser_failure{what} {}

    explicit unknown_version_error(char const* what) : parser_failure{what} {}
};

} // namespace sipphony

#endif
