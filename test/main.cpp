//
// Created by david on 2025/3/10.
//

#include "VariableLengthEncoder.h"
#include <iostream>

int main(int argc, char* argv[]) {
  int num = 123123123;
  std::cout << VariableLengthEncoder::variableLengthEncodeValue(num) << std::endl;
  std::cout << num << " " << VariableLengthEncoder::variableLengthDecodeValue(
      VariableLengthEncoder::variableLengthEncodeValue(num)) << std::endl;

  num = 64;
  std::cout << VariableLengthEncoder::variableLengthEncodeValue(num) << std::endl;
  std::cout << num << " " << VariableLengthEncoder::variableLengthDecodeValue(
      VariableLengthEncoder::variableLengthEncodeValue(num)) << std::endl;
  num = 6400000;
  std::cout << VariableLengthEncoder::variableLengthEncodeValue(num) << std::endl;
  std::cout << num << " " << VariableLengthEncoder::variableLengthDecodeValue(
      VariableLengthEncoder::variableLengthEncodeValue(num)) << std::endl;
  num = -10;
  std::cout << VariableLengthEncoder::variableLengthEncodeValue(num) << std::endl;
  std::cout << num << " " << VariableLengthEncoder::variableLengthDecodeValue(
      VariableLengthEncoder::variableLengthEncodeValue(num)) << std::endl;
  num = -1;
  std::cout << VariableLengthEncoder::variableLengthEncodeValue(num) << std::endl;
  std::cout << num << " " << VariableLengthEncoder::variableLengthDecodeValue(
      VariableLengthEncoder::variableLengthEncodeValue(num)) << std::endl;
}