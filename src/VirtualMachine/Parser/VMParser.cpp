#include "VMParser.hpp"
#include "VirtualMachine/Translation/attributes.hpp"
#include <iostream>

namespace vm {

    const uint32_t MAGIC_NUM_LEN = 3;

    // INVARIANT: data is exactly 8 characters
    uint64_t parse_uint64_t(std::string data){
        auto value = 0;
        for(int i = 0; i < 8; i++) {
            value += (reinterpret_cast<unsigned char &>(data[i]) << (i * 8));
        }
        return value;
    }

    std::optional<Executable> VMParser::parse(const std::string& data) {
        auto executable = Executable();
        try {
            // Check Magic Number
            if(data.length() > MAGIC_NUM_LEN && data.substr(0,MAGIC_NUM_LEN) == "RWN") {
                auto res = parseAttributes(data.substr(MAGIC_NUM_LEN, data.length() - MAGIC_NUM_LEN), executable);
                if(res < 0) {
                    return std::nullopt;
                }
                parseExecutable(data.substr(res + MAGIC_NUM_LEN, data.length() - MAGIC_NUM_LEN - res), executable);
                if (executable.isValid()){
                    return executable;
                }
                return std::nullopt;
            } else {
                throw std::logic_error("ERROR: Magic Number does not match, file is invalid.");
            }
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            return std::nullopt;
        }
    }

    int64_t VMParser::parseAttributes(std::string data, Executable& exe){
        try {
            // Check if heading is valid
            if(data.length() < 2 || data[0] != 1){
                throw std::logic_error("ERROR: Attribute header is invalid.");
            } else {
                std::map<std::string, uint64_t> attributes;
                int attribute_count = data[1];
                int64_t current_location = 2;
                for (auto i = 0; i < attribute_count; i++){
                    auto identifier = data[current_location];
                    current_location++;
                    auto attribute_len = translate::attribute_lengths[identifier];
                    if (attribute_len == 8){
                        auto value = parse_uint64_t(data.substr(current_location, 8));
                        attributes[translate::valid_attributes[identifier]] = value;
                        current_location += 8;
                    } else {
                        throw std::domain_error("ERROR: Attribute has invalid length.");
                    }
                }
                exe.attributes = std::make_unique<std::map<std::string,uint64_t>>(attributes);
                return current_location;
            }
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            return -1;
        }
    }

    void VMParser::parseExecutable(std::string data, Executable &exe) {
        if(data.length() < 9){
            std::cerr << "ERROR: Invalid executable header" << std::endl;
        } else {
            auto len = parse_uint64_t(data.substr(1, 8));
            exe.binary = std::make_unique<std::string>(data.substr(9, len));
        }
    }
}