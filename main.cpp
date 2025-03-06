#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <fstream>
#include "PatchCompressor.h"
#include <string>
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
  compressor.compress();

  compressor.output(std::cout);
  std::cout << compressor.size() << std::endl;
  std::cout << compressor.invariantCount() << std::endl;
  std::cout << compressor.invariantItems.size() << std::endl;
  std::cout << compressor.invariantItems.size()  + compressor.plainItems.size()<< std::endl;
  return 0;
}