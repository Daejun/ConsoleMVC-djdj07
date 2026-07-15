#pragma once

#include <optional>
#include <string>
#include <vector>

#include "view/IView.h"

class StubView : public IView {
public:
    void showItems(const std::vector<Item>& items) override {
        lastItems = items;
    }

    void showItem(const Item& item) override {
        lastItem = item;
    }

    void showMessage(const std::string& message) override {
        lastMessage = message;
    }

    void showError(const std::string& message) override {
        lastError = message;
    }

    std::vector<Item> lastItems;
    std::optional<Item> lastItem;
    std::string lastMessage;
    std::string lastError;
};
