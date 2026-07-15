#include "ItemRepository.h"

#include <algorithm>

Item ItemRepository::add(const std::string& name, int value) {
    Item item{nextId_++, name, value};
    items_.push_back(item);
    return item;
}

bool ItemRepository::remove(int id) {
    auto it = std::find_if(items_.begin(), items_.end(),
                            [id](const Item& item) { return item.id == id; });
    if (it == items_.end()) {
        return false;
    }
    items_.erase(it);
    return true;
}

std::optional<Item> ItemRepository::find(int id) const {
    auto it = std::find_if(items_.begin(), items_.end(),
                            [id](const Item& item) { return item.id == id; });
    if (it == items_.end()) {
        return std::nullopt;
    }
    return *it;
}

std::vector<Item> ItemRepository::list() const {
    return items_;
}
