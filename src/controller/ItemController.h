#pragma once

#include <string>

#include "../model/ItemRepository.h"
#include "../view/IView.h"

class ItemController {
public:
    ItemController(ItemRepository& repository, IView& view);

    void listItems();
    void addItem(const std::string& name, int value);
    void showItem(int id);
    void removeItem(int id);

private:
    ItemRepository& repository_;
    IView& view_;
};
