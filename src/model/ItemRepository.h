#pragma once

#include <optional>
#include <string>
#include <vector>

#include "Item.h"

class ItemRepository {
public:
    Item add(const std::string& name, int value);
    bool remove(int id);
    std::optional<Item> find(int id) const;
    std::vector<Item> list() const;

private:
    std::vector<Item> items_;
    int nextId_ = 1;
};
