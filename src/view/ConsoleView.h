#pragma once

#include "IView.h"

class ConsoleView : public IView {
public:
    void showItems(const std::vector<Item>& items) override;
    void showItem(const Item& item) override;
    void showMessage(const std::string& message) override;
    void showError(const std::string& message) override;
};
