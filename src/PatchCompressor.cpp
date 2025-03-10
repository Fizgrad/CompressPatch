#include "PatchCompressor.h"

#include <iostream>
#include <ostream>
#include <regex>


bool PatchCompressor::addItem(const Item& item) {
  this->storage.push_back(item);
  return true;
}

void PatchCompressor::splitInvariant() {
  for (auto& it : this->storage) {
    if (canConvertToInvariant(it)) {
      this->invariantItems.emplace_back(itemToInvariantItem(it));
    } else
      this->plainItems.emplace_back(it);
  }
}

void PatchCompressor::sortTwoTypesItems() {
  std::sort(this->invariantItems.begin(), this->invariantItems.end());
  std::sort(this->plainItems.begin(), this->plainItems.end());
}

void PatchCompressor::compress() {
  splitInvariant();
  sortTwoTypesItems();
  differentialEncode();
  variableLengthEncode();
}

void PatchCompressor::output(std::ostream& os) const {
  if (invariantItems.size() > 0 || plainItems.size() > 0) {
    for (auto& item : this->invariantItems) {
      os << item << std::endl;
    }
    for (auto& item : this->plainItems) {
      os << item << std::endl;
    }
  } else
    for (auto& item : this->storage) {
      os << item << std::endl;
    }
}

size_t PatchCompressor::invariantCount() const {
  size_t count = 0;
  for (auto& item : this->storage) {
    if (canConvertToInvariant(item)) {
      count++;
    }
  }
  return count;
}

void PatchCompressor::differentialEncode() {
  // 对 invariantItems 进行差分编码
  if (!invariantItems.empty()) {
    int prevValue = std::get<1>(invariantItems[0]);
    for (size_t i = 1; i < invariantItems.size(); ++i) {
      int currentValue = std::get<1>(invariantItems[i]);
      int diff = currentValue - prevValue;
      std::get<1>(invariantItems[i]) = diff;
      prevValue = currentValue;
    }
  }
  // 对 plainItems 进行差分编码
  if (!plainItems.empty()) {
    int prevValue = std::get<1>(plainItems[0]);
    int diff = std::get<2>(plainItems[0]) - prevValue;
    if (diff < 0) {
      std::cerr << "Error diff : " << diff << std::endl;
    }
    std::get<2>(plainItems[0]) = diff;
    for (size_t i = 1; i < plainItems.size(); ++i) {
      int currentValue1 = std::get<1>(plainItems[i]);
      int currentValue2 = std::get<2>(plainItems[i]);
      int diff1 = currentValue1 - prevValue;
      int diff2 = currentValue2 - currentValue1;
      std::get<1>(plainItems[i]) = diff1;
      std::get<2>(plainItems[i]) = diff2;
      if (diff2 < 0) {
        std::cerr << "Error diff2 : " << diff2 << std::endl;
      }
      prevValue = currentValue1;
    }
  }
}

void PatchCompressor::variableLengthEncode() {
  if (invariantItems.empty() && plainItems.empty()) {
    throw std::runtime_error("No invariant items or plain items");
  }
  for (auto& item : this->invariantItems) {
    this->variableLengthEncodingForInvariantItems.emplace_back(std::make_tuple(std::get<0>(item),
      VariableLengthEncoder::variableLengthEncodeValue(std::get<1>(item))));
  }
  for (auto& item : this->plainItems) {
    this->variableLengthEncodingForPlainItems.emplace_back(std::make_tuple(std::get<0>(item),
      VariableLengthEncoder::variableLengthEncodeValue(std::get<1>(item)),
      VariableLengthEncoder::variableLengthEncodeValue(std::get<2>(item))));
  }
}

size_t PatchCompressor::getVariableLengthEncodedSize() const {
  size_t size = 0;
  for (auto& item : this->variableLengthEncodingForInvariantItems) {
    size += std::get<1>(item).size();
  }
  for (auto& item : this->variableLengthEncodingForPlainItems) {
    size += std::get<1>(item).size();
    size += std::get<2>(item).size();
  }
  return size;
}