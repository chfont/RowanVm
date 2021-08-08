#include "translator.hpp"
#include "attributes.hpp"
#include <Assembler/Parser/attribute.hpp>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>

namespace translate {
  Translator::Translator() noexcept{
    hexData = "";
    length=0;
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
      length += node->size();
      addToHoles(node->emitLabel(), hexData.size()-4);
      break;
    }
    default:
      hexData += node->emit();
      length += node->size();
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
      if(std::find(valid_attributes.begin(), valid_attributes.end(), attribute.first) == valid_attributes.end()){
        return false;
      }
    }
    return true;
  }

  std::map<std::string, uint64_t> Translator::getAttributes(){ return attributes;}

  // Short helper method
  void write_uint64_t_to_file(std::ofstream& file_stream, uint64_t integer) {
      unsigned char value[sizeof(integer)];
      std::memcpy(value, &integer, sizeof(integer));
      for(int i = 0; i < sizeof(integer); i++){
          file_stream << value[i];
      }
  }

  bool Translator::writeToFile(const std::string &file_name) {
    auto file_stream = std::ofstream(file_name, std::ios::binary);
    if (file_stream.good()){
        file_stream << "RWN";
        file_stream << char(1); // Start attribute section
        file_stream << char(attributes.size());
        for (const auto& k : attributes){
            file_stream << char(std::find(translate::valid_attributes.begin(), translate::valid_attributes.end(), k.first) -
            translate::valid_attributes.begin());

            write_uint64_t_to_file(file_stream, k.second);
        }
        file_stream << char(2);
        write_uint64_t_to_file(file_stream, length);
        file_stream << hexData;
        file_stream.close();
        return true;
    } else {
        return false;
    }
  }
}
