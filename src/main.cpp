#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <fstream>
#include "PatchCompressor.h"
#include <string>
#include "VariableLengthEncoder.h"
#include <utility> // for std::pair


int main() {
  // 输入数据
  std::ifstream ifile("/Users/david/Projects/CompressPatch/data/patch.map");

  if (!ifile) {
    std::cerr << "Failed to open file.\n";
    return 1;
  }

  std::string line;
  PatchCompressor compressor;
  while (std::getline(ifile, line)) {
    auto item = stringToItem(line);
    compressor.addItem(item);
  }
  // compressor.output(std::cout);

  compressor.compress();

  // compressor.output(std::cout);
  std::cout << 4 * 2 * compressor.size() << std::endl;
  std::cout << compressor.invariantCount() << std::endl;
  std::cout << 4 * compressor.invariantItems.size() + 8 * compressor.plainItems.size() << std::endl;
  std::cout << compressor.getVariableLengthEncodedSize() << std::endl;
  return 0;
}