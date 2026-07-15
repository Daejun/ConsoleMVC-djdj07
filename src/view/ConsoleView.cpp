#include "ConsoleView.h"

#include <cstdio>

void ConsoleView::showItems(const std::vector<Item>& items) {
    if (items.empty()) {
        std::printf("No items.\n");
        return;
    }
    for (const auto& item : items) {
        std::printf("[%d] %s (%d)\n", item.id, item.name.c_str(), item.value);
    }
}

void ConsoleView::showItem(const Item& item) {
    std::printf("[%d] %s (%d)\n", item.id, item.name.c_str(), item.value);
}

void ConsoleView::showMessage(const std::string& message) {
    std::printf("%s\n", message.c_str());
}

void ConsoleView::showError(const std::string& message) {
    std::printf("Error: %s\n", message.c_str());
}
