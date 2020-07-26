#ifndef token_h
#define token_h

#include <string>
namespace token {
class Token {
public:
  virtual std::string emit() const = 0;
};

inline bool operator==(const Token &lhs, const Token &rhs) {
  return lhs.emit() == rhs.emit();
}
} // namespace token

#endif
