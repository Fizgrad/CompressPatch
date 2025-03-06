#ifndef PATCHCOMPRESSOR_H
#define PATCHCOMPRESSOR_H


#include "PatchMapKind.h"
#include "Item.h"
#include <vector>


class PatchCompressor
{
public:
    bool addItem(const Item& item);

    void compress();

    void output(std::ostream& os) const;

    [[nodiscard]] size_t size() const { return this->storage.size(); }

    [[nodiscard]] size_t invariantCount() const;

    std::vector<Item> storage;
    std::vector<InvariantItem> invariantItems;
    std::vector<Item> plainItems;
};

#endif
