#pragma once

#include <format>
#include <print>
#include <utility>

namespace ch::errors {

template <typename... Args> [[noreturn]] void fatal(std::format_string<Args...> msg, Args &&...args) {
    std::println(stderr, "Encountered fatal error: {}", std::format(msg, std::forward<Args>(args)...));
    std::exit(EXIT_FAILURE);
}

template <typename... Args> void warning(std::format_string<Args...> msg, Args &&...args) {
    std::println(stderr, "Warning: {}", std::format(msg, std::forward<Args>(args)...));
}

} // namespace ch::errors
