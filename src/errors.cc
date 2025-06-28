#include "errors.h"

#include <print>

namespace errors {

void fatal(std::string_view msg) {
    std::println(stderr, "Encountered fatal error: {}", msg);
    std::exit(1);
}

} // namespace errors
