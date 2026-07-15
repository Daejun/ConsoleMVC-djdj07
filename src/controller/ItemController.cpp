#include "ItemController.h"

ItemController::ItemController(ItemRepository& repository, IView& view)
    : repository_(repository), view_(view) {}

void ItemController::listItems() {
    view_.showItems(repository_.list());
}

void ItemController::addItem(const std::string& name, int value) {
    Item added = repository_.add(name, value);
    view_.showMessage("Added item: " + added.name);
}

void ItemController::showItem(int id) {
    auto found = repository_.find(id);
    if (!found.has_value()) {
        view_.showError("Item not found: " + std::to_string(id));
        return;
    }
    view_.showItem(*found);
}

void ItemController::removeItem(int id) {
    if (!repository_.remove(id)) {
        view_.showError("Item not found: " + std::to_string(id));
        return;
    }
    view_.showMessage("Removed item: " + std::to_string(id));
}
