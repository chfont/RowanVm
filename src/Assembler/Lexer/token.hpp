#ifndef token_h
#define token_h

#include <string>
namespace token {

    enum class TokenType {
        NUM,
        LABEL,
        OPCODE,
        REG,
        COND,
        COLON
    };

class Token {
public:
  virtual std::string emitDebugString() const = 0;
  virtual std::string emit() const = 0;
  virtual TokenType getType() const = 0;
};

inline bool operator==(const Token &lhs, const Token &rhs) {
  return lhs.emit() == rhs.emit() && lhs.getType() == rhs.getType();
}
}

#endif
