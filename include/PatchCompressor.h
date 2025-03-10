#ifndef PATCHCOMPRESSOR_H
#define PATCHCOMPRESSOR_H


#include "PatchMapKind.h"
#include "Item.h"
#include "VariableLengthEncoder.h"
#include <vector>


class PatchCompressor
{
public:
    bool addItem(const Item& item);
    void splitInvariant();
    void sortTwoTypesItems();

    void compress();

    void output(std::ostream& os) const;

    [[nodiscard]] size_t size() const { return this->storage.size(); }

    [[nodiscard]] size_t invariantCount() const;

    void differentialEncode();

    void variableLengthEncode();

    size_t getVariableLengthEncodedSize() const;

    std::vector<Item> storage;
    std::vector<InvariantItem> invariantItems;
    std::vector<Item> plainItems;
    std::vector<VariableLengthEncodingInvariantItem> variableLengthEncodingForInvariantItems;
    std::vector<VariableLengthEncodingItem> variableLengthEncodingForPlainItems;
};

#endif
