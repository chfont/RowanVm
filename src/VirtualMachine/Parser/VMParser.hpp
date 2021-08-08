#ifndef vmparser_h
#define vmparser_h

#include <string>
#include <map>
#include <optional>
#include "Executable.hpp"

namespace vm {
    class VMParser {
    public:
        static std::optional<Executable> parse(const std::string&);
        static int64_t parseAttributes(std::string data, Executable& exe);
        static void parseExecutable(std::string data, Executable& exe);
    };
}


#endif
