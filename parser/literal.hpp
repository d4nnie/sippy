#ifndef SIPPY_PARSER_LITERAL_HPP
#define SIPPY_PARSER_LITERAL_HPP

#include <cstdint>

namespace sippy::parser {

template<std::size_t SizeT>
struct string {
    constexpr string(char const (&str)[SizeT]) {
        std::copy_n(str, SizeT, value);
    }

    inline constexpr static std::size_t size{SizeT};
    char value[SizeT];
};

template<string ValueT>
struct literal {
    inline constexpr static std::size_t size{decltype(ValueT)::size};
    inline constexpr static char const* value{ValueT.value};
};

namespace details {

constexpr auto to_lower(char char_) -> char {
    if (char_ >= 'A' && char_ <= 'Z')
        return char_ + 32;
    return char_;
}

constexpr auto to_upper(char char_) -> char {
    if (char_ >= 'a' && char_ <= 'z')
        return char_ - 32;
    return char_;
}

template<std::size_t SizeT>
constexpr auto to_lower(string<SizeT> source) -> string<SizeT> {
    char result[SizeT];
    for (std::size_t i{}; i < SizeT; ++i)
        result[i] = to_lower(source.value[i]);
    return result;
}

template<std::size_t SizeT>
constexpr auto to_upper(string<SizeT> source) -> string<SizeT> {
    char result[SizeT];
    for (std::size_t i{}; i < SizeT; ++i) {
        result[i] = to_upper(source.value[i]);
    }
    return result;
}

template<string StringT>
constexpr auto to_lower(literal<StringT>) -> literal<to_lower(StringT)> {
    return {};
}

template<string StringT>
constexpr auto to_upper(literal<StringT>) -> literal<to_upper(StringT)> {
    return {};
}

} // namespace details

template<class T>
using to_lower_t = decltype(details::to_lower(T{}));

template<class T>
using to_upper_t = decltype(details::to_upper(T{}));

} // namespace sippy::parser

#endif
