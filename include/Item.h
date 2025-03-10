//
// Created by david on 2025/3/6.
//

#ifndef ITEM_H
#define ITEM_H


#include <tuple>
#include <VariableLengthEncoder.h>

using Item = std::tuple<PatchMapKind, int32_t, int32_t>;
using InvariantItem = std::tuple<PatchMapKind, int32_t>;

using VariableLengthEncodingItem = std::tuple<
  PatchMapKind, VariableLengthEncoding, VariableLengthEncoding>;
using VariableLengthEncodingInvariantItem = std::tuple<PatchMapKind, VariableLengthEncoding>;

inline std::ostream& operator<<(std::ostream& os, const Item& item) {
  os << PatchMapKindToString(std::get<0>(item)) << " " << std::get<1>(item) << ":"
      << std::get<2>(item);
  return os;
}

inline std::ostream& operator<<(std::ostream& os, const VariableLengthEncodingItem& item) {
  os << PatchMapKindToString(std::get<0>(item)) << " " << std::get<1>(item) << ":"
      << std::get<2>(item);
  return os;
}

inline std::ostream& operator<<(std::ostream& os, const VariableLengthEncodingInvariantItem& item) {
  os << PatchMapKindToString(std::get<0>(item)) << " " << std::get<1>(item) << ":" <<
      std::get<1>(item);
  return os;
}

inline std::ostream& operator<<(std::ostream& os, const InvariantItem& item) {
  os << PatchMapKindToString(std::get<0>(item)) << " " << std::get<1>(item) << ":" <<
      std::get<1>(item);
  return os;
}

inline Item stringToItem(const std::string& str) {
  std::regex pattern(R"((\w+ \w+ \w+) (\d+):(\d+))");
  std::smatch match;
  if (std::regex_match(str, match, pattern)) {
    std::string kindStr = match[1].str();
    int a = std::stoi(match[2].str());
    int b = std::stoi(match[3].str());
    PatchMapKind patchMapKind = stringToPatchMapKind(kindStr);
    return std::make_tuple(patchMapKind, a, b);
  } else {
    throw std::invalid_argument("Invalid patch map string");
  }
}

inline bool canConvertToInvariant(const Item& item) {
  return std::get<1>(item) == std::get<2>(item);
}

inline InvariantItem itemToInvariantItem(const Item& item) {
  return std::make_tuple(std::get<0>(item), std::get<1>(item));
}

#endif //ITEM_H