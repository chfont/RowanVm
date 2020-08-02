#ifndef translator_h
#define translator_h
#include "ast.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace translate {
  class Translator {
  public:
    Translator() noexcept;
    std::string translate(std::vector<std::unique_ptr<parser::AST>> const& nodes);
  private:
    void translateLine(std::unique_ptr<parser::AST> const& node);
    void fillHoles();
    std::map<std::string, uint64_t> labelDeclarations;
    std::vector<std::pair<uint64_t , std::string>> labelHoles;
    void addToHoles(std::string label, uint64_t location);
    bool addToLabelDeclaration(const std::string& label, uint64_t location);
    std::string hexData;
  };
}

#endif
