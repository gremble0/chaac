#pragma once

#include <string_view>

namespace errors {

[[noreturn]] void fatal(std::string_view msg);

}
