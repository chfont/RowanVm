#include "Executable.hpp"

namespace vm {
    bool Executable::isValid() const {
        return binary != nullptr && attributes != nullptr;
    }

    Executable::Executable() = default;
}