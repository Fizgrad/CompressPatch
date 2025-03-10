//
// Created by david on 2025/3/10.
//

#ifndef VLAENCODING_H
#define VLAENCODING_H

#include <vector>

using VariableLengthEncoding = std::vector<unsigned char>;

std::ostream& operator<<(std::ostream& os, const VariableLengthEncoding& encoding);

class VariableLengthEncoder {
public:
  static VariableLengthEncoding variableLengthEncodeValue(int32_t value);
  static int32_t variableLengthDecodeValue(const VariableLengthEncoding& encodedBytes);
};


#endif //VLAENCODING_H