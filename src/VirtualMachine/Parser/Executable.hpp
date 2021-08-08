#ifndef executable_h
#define executable_h

#include <string>
#include <map>
#include <memory>

namespace vm {
    class Executable {
        public:
            Executable();
            bool isValid() const;
            std::unique_ptr<std::string> binary;
            std::unique_ptr<std::map<std::string, uint64_t>> attributes;
    };
}

#endif
