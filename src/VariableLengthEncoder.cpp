//
// Created by david on 2025/3/10.
//

#include "VariableLengthEncoder.h"
#include <iostream>
#include <iomanip>

std::ostream& operator<<(std::ostream& os, const VariableLengthEncoding& encoding) {
  std::ios_base::fmtflags originalFlags = os.flags(); // 保存原始格式标志
  os << "0x"; // 输出前缀
  for (unsigned char byte : encoding) {
    os << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
  }
  os.flags(originalFlags); // 恢复原始格式标志
  return os;
}

VariableLengthEncoding VariableLengthEncoder::variableLengthEncodeValue(int32_t value) {
  VariableLengthEncoding encodedBytes;
  bool isNegative = value < 0;
  if (isNegative) {
    value = -value;
  }
  unsigned char byte = value & 0x3F; // 取低6位
  value >>= 6; // 右移6位
  if (value > 0) {
    byte |= 0x80; // 设置最高位为1，表示还有后续字节
  }
  if (isNegative) {
    byte |= 0x40; // 设置第二为1，表示为负数
  }
  encodedBytes.push_back(byte);
  // 使用位宽动态调整的方式进行变长编码
  while (value > 0) {
    byte = value & 0x7F; // 取低7位
    value >>= 7; // 右移7位
    if (value > 0) {
      byte |= 0x80; // 设置最高位为1，表示还有后续字节
    }
    encodedBytes.push_back(byte);
  }
  return encodedBytes;
}

int32_t VariableLengthEncoder::variableLengthDecodeValue(const VariableLengthEncoding& encodedBytes) {
  int32_t value = 0;
  int shift = 0;
  bool isNegative = false;

  for (size_t i = 0; i < encodedBytes.size(); ++i) {
    unsigned char byte = encodedBytes[i];
    // 检查是否为负数
    if (i == 0 && (byte & 0x40)) {
      isNegative = true;
    }
    // 提取有效数据位
    int data = byte & 0x7F; // 后续字节取低7位
    if (i == 0) {
      data = byte & 0x3F; // 第一个字节取低6位
    }
    // 将数据位左移并累加到最终值
    value |= data << shift;
    // 更新位移量
    shift += (i == 0) ? 6 : 7;

    // 检查是否还有后续字节
    if (!(byte & 0x80)) {
      break; // 最高位为0，表示这是最后一个字节
    }
  }
  // 如果是负数，将值转换为负数
  if (isNegative) {
    value = -value;
  }
  return value;
}

