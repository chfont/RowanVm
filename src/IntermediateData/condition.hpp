#ifndef cond_h
#define cond_h

#include <map>
#include <string>

namespace condition {
  enum class Condition {
    EQ,
    NEQ,
    LT,
    GT,
    LE,
    GE,
    BAD
  };

  const auto condMap = std::map<Condition, std::string>{
    {Condition::EQ, "EQ"}, {Condition::NEQ, "NEQ"}, {Condition::LT, "LT"},
    {Condition::LE, "LE"}, {Condition::GT, "GT"},   {Condition::GE, "GE"},
    {Condition::LE, "LE"}, {Condition::BAD, "BAD"}};

  const auto stringCondMap = std::map<std::string, Condition>{
    {"eq", Condition::EQ}, {"neq", Condition::NEQ}, {"lt", Condition::LT},
    {"le", Condition::LE}, {"gt", Condition::GT},   {"ge", Condition::GE},
    {"le", Condition::LE}, {"bad", Condition::BAD}};
}

#endif
