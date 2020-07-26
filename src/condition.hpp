#ifndef cond_h
#define cond_h

#include <map>

namespace Condition{
    enum Condition{
        EQ,
        NEQ,
        LT,
        GT,
        GE,
        LE,
        BAD
    };

    const auto condMap = std::map<Condition,std::string>{
            {EQ, "EQ" },
            {NEQ, "NEQ"},
            {LT,"LT"},
            {LE, "LE"},
            {GT, "GT"},
            {GE, "GE"},
            {LE, "LE"},
            {BAD, "BAD"}
    };

    const auto stringCondMap = std::map<std::string, Condition>{
            {"eq", EQ },
            {"neq", NEQ},
            {"lt",LT},
            {"le", LE},
            {"gt", GT},
            {"ge", GE},
            {"le", LE},
            {"bad", BAD}
    };
}

#endif
