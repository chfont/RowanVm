#ifndef rowan_attr_h
#define rowan_attr_h

#include <vector>
#include <string>

namespace translate {

  //Hold all valid attributes
  const std::vector<std::string> valid_attributes {
    "stack_size",
    "mem_size"
    };
  const std::vector<std::size_t> attribute_lengths  { // id is same as position in valid_attributes
    8,
    8
  };
}
#endif
