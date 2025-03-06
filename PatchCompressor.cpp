#include "PatchCompressor.h"

#include <ostream>
#include <regex>


bool PatchCompressor::addItem(const Item& item) {
  this->storage.push_back(item);
  return true;
}

void PatchCompressor::compress() {
  for (auto& it : this->storage) {
    if (canConvertToInvariant(it)) {
      this->invariantItems.emplace_back(itemToInvariantItem(it));
    } else
      this->plainItems.emplace_back(it);
  }
  std::sort(this->invariantItems.begin(), this->invariantItems.end());
  std::sort(this->plainItems.begin(), this->plainItems.end());
}

void PatchCompressor::output(std::ostream& os) const {
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