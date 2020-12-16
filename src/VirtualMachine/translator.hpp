#ifndef translator_h
#define translator_h
#include "Assembler/Parser/ast.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace translate {
  class Translator {
  public:
    Translator() noexcept;
    std::string translate(std::vector<std::unique_ptr<parser::AST>> const& nodes);
    std::map<std::string, uint64_t> getAttributes();
    bool validate_attributes();
  private:
    void translateLine(std::unique_ptr<parser::AST> const& node);
    void fillHoles();
    void translateAttributes(std::vector<std::unique_ptr<parser::AST>> const& nodes);
    std::map<std::string, uint64_t> labelDeclarations;
    std::vector<std::pair<uint64_t , std::string>> labelHoles;
    void addToHoles(std::string label, uint64_t location);
    bool addToLabelDeclaration(const std::string& label, uint64_t location);
    std::string hexData;
    std::map<std::string, uint64_t> attributes;
  };
}

#endif
