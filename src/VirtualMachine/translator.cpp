#include "translator.hpp"
#include "attributes.hpp"
#include <Parser/attribute.hpp>
#include <algorithm>
#include <iostream>
namespace translate {
  Translator::Translator() noexcept{
    hexData = "";
    attributes = std::map<std::string, uint64_t>();
    labelDeclarations = std::map<std::string, uint64_t>();
    labelHoles = std::vector<std::pair<uint64_t , std::string>>();
  }

  void Translator::addToHoles(std::string label, uint64_t location) {
    labelHoles.emplace_back(location, std::move(label));
  }

  bool Translator::addToLabelDeclaration(const std::string& label, uint64_t location) {
    if(labelDeclarations.count(label) == 0){
      labelDeclarations.emplace(label, location);
      return true;
    }
    return false;
  }

  void Translator::translateLine(std::unique_ptr<parser::AST> const& node) {
    auto type = node->getType();
    switch (type){
    case parser::ASTType::Label: {
      addToLabelDeclaration(node->emitLabel(), hexData.size());
      break;
    }
    case parser::ASTType::LabelInstr:
    case parser::ASTType::Conditional: {
      hexData += node->emit();
      addToHoles(node->emitLabel(), hexData.size()-4);
      break;
    }
    default:
      hexData += node->emit();
      break;
    }
  }

  void Translator::fillHoles(){
    for(const auto& hole : labelHoles){
      if(labelDeclarations.count(hole.second) == 1){
        auto loc = labelDeclarations.at(hole.second);
        auto locBytes = (char *)(&loc);
        auto start= hole.first;
        for(int i =0; i < 4; i++){
          hexData[start+i] = locBytes[i];
        }
      } else {
        std::cerr << "Label " << hole.second << "not found" << std::endl;
      }
    }
  }

  std::string Translator::translate(const std::vector<std::unique_ptr<parser::AST>> &nodes) {
    translateAttributes(nodes);
    for(const auto & node : nodes){
      if(node->getType() != parser::ASTType::Attribute){
        translateLine(node);
      }
    }
    fillHoles();
    return hexData;
  }

  void Translator::translateAttributes(const std::vector<std::unique_ptr<parser::AST>> &nodes) {
    for (auto& node : nodes){
      if (node->getType() == parser::ASTType::Attribute){
        auto raw_ptr = node.get();
        auto cast_node = static_cast<parser::Attribute*>(raw_ptr);
        attributes[cast_node->getAttributeName()]=cast_node->getAttributeValue();
      }
    }
  }

  bool Translator::validate_attributes(){
    for(auto & attribute : attributes){
      if(std::find(validAttributes.begin(), validAttributes.end(), attribute.first) == validAttributes.end()){
        return false;
      }
    }
    return true;
  }
  std::map<std::string, uint64_t> Translator::getAttributes(){ return attributes;}

}
