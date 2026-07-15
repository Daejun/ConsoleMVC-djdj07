#pragma once

#include <string>
#include <vector>

#include "../model/Item.h"

class IView {
public:
    virtual ~IView() = default;
    virtual void showItems(const std::vector<Item>& items) = 0;
    virtual void showItem(const Item& item) = 0;
    virtual void showMessage(const std::string& message) = 0;
    virtual void showError(const std::string& message) = 0;
};
