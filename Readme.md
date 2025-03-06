对于有序整数数对的压缩，可以使用一些高效的算法来减少存储空间，特别是当整数范围较大但实际使用的值较小时。以下是一些常见的压缩方法和算法：


1.差分编码（Delta Encoding）
如果整数数对是有序的，且相邻数对之间的差值较小，可以使用差分编码来压缩数据。


原理：

• 对于第一个数对`(a1, b1)`，直接存储其值。

• 对于后续的数对`(ai, bi)`，存储与前一个数对`(ai-1, bi-1)`的差值`(ai - ai-1, bi - bi-1)`。


优点：

• 如果相邻数对之间的差值较小，差分编码可以显著减少存储空间。

• 解码过程简单，只需逐个累加差值即可恢复原始数据。


示例：
假设有序数对为：`(100, 200), (101, 201), (103, 205)`

差分编码后为：`(100, 200), (1, 1), (2, 4)`。


2.变长编码（Variable-Length Encoding）
如果整数的范围很大，但实际使用的值较小，可以使用变长编码来压缩整数。


常见的变长编码方法：

• Variable-Length Quantity(VLQ)：将整数编码为多个字节，每个字节的最高位表示是否还有后续字节。

• LZ77/LZ78：基于字典的压缩算法，适用于重复数据较多的场景。

• Huffman 编码：根据数据的频率分配不同的编码长度，频率高的数据使用较短的编码。


示例：
假设整数范围为`[0, 1000000]`，但实际使用的值大多在`[0, 100]`之间，使用变长编码可以显著减少存储空间。


3.字典编码（Dictionary Encoding）
如果整数数对中有大量重复值，可以使用字典编码。


原理：

• 构建一个字典，将每个唯一的数对映射到一个较短的索引。

• 存储时只存储索引，而不是完整的数对。


示例：
假设有序数对为：`(100, 200), (100, 200), (101, 201), (100, 200)`

字典为：`{(100, 200): 0, (101, 201): 1}`

压缩后存储为：`0, 0, 1, 0`。


4.位运算压缩（Bit-Packing）
如果整数的范围已知且较小，可以使用位运算将多个整数打包到一个更大的整数中。


原理：

• 假设整数范围为`[0, 255]`，可以用 8 位表示一个整数。

• 对于数对`(a, b)`，可以用 16 位表示，其中`a`占用低 8 位，`b`占用高 8 位。


示例：
假设有序数对为：`(10, 20), (30, 40)`

可以将它们打包为：`00001010 00010100`（二进制），即一个 16 位整数。


5.混合方法
在实际应用中，通常会结合多种方法来实现最佳的压缩效果。例如：

• 先对整数数对进行差分编码，然后对差值进行变长编码。

• 使用字典编码处理重复值，对字典索引进行变长编码。


示例代码：差分编码+变长编码
以下是一个简单的C++代码示例，展示如何使用差分编码和变长编码压缩有序整数数对：


```cpp
#include <iostream>
#include <vector>
#include <utility>

// 变长编码：将整数编码为多个字节
std::vector<uint8_t> encodeVLE(int value) {
    std::vector<uint8_t> result;
    while (value >= 0x80) {
        result.push_back((value & 0x7F) | 0x80);
        value >>= 7;
    }
    result.push_back(value & 0x7F);
    return result;
}

// 解码变长编码
int decodeVLE(const std::vector<uint8_t>& data, size_t& pos) {
    int result = 0;
    int shift = 0;
    while (true) {
        if (pos >= data.size()) throw std::runtime_error("Invalid VLE data");
        uint8_t byte = data[pos++];
        result |= (byte & 0x7F) << shift;
        if ((byte & 0x80) == 0) break;
        shift += 7;
    }
    return result;
}

// 压缩有序整数数对
std::vector<uint8_t> compressPairs(const std::vector<std::pair<int, int>>& pairs) {
    std::vector<uint8_t> result;
    int prevA = 0, prevB = 0;

    for (const auto& [a, b] : pairs) {
        int deltaA = a - prevA;
        int deltaB = b - prevB;
        auto encodedA = encodeVLE(deltaA);
        auto encodedB = encodeVLE(deltaB);
        result.insert(result.end(), encodedA.begin(), encodedA.end());
        result.insert(result.end(), encodedB.begin(), encodedB.end());
        prevA = a;
        prevB = b;
    }
    return result;
}

// 解压缩有序整数数对
std::vector<std::pair<int, int>> decompressPairs(const std::vector<uint8_t>& data) {
    std::vector<std::pair<int, int>> result;
    int prevA = 0, prevB = 0;
    size_t pos = 0;

    while (pos < data.size()) {
        int deltaA = decodeVLE(data, pos);
        int deltaB = decodeVLE(data, pos);
        int a = prevA + deltaA;
        int b = prevB + deltaB;
        result.emplace_back(a, b);
        prevA = a;
        prevB = b;
    }
    return result;
}

int main() {
    std::vector<std::pair<int, int>> pairs = {{100, 200}, {101, 201}, {103, 205}, {105, 210}};
    auto compressed = compressPairs(pairs);
    std::cout << "Compressed size: " << compressed.size() << " bytes\n";

    auto decompressed = decompressPairs(compressed);
    std::cout << "Decompressed pairs:\n";
    for (const auto& [a, b] : decompressed) {
        std::cout << "(" << a << ", " << b << ")\n";
    }
    return 0;
}
```



输出示例
对于输入数对：`{(100, 200), (101, 201), (103, 205), (105, 210)}`

压缩后大小可能为：`10 bytes`（具体取决于差值的大小）

解压缩后输出：

```
(100, 200)
(101, 201)
(103, 205)
(105, 210)
```



总结
选择合适的压缩算法取决于数据的特性：

• 如果数据有序且相邻差值较小，差分编码是不错的选择。

• 如果数据范围较大但实际值较小，变长编码可以显著减少存储空间。

• 如果数据有大量重复值，字典编码可以有效压缩。

• 对于更复杂的数据，可以结合多种方法以实现最佳压缩效果。