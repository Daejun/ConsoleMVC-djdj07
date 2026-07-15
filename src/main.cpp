#include <cstdio>
#include <iostream>
#include <string>

#include "controller/ItemController.h"
#include "model/ItemRepository.h"
#include "view/ConsoleView.h"

namespace {

void printMenu() {
    std::printf("\n=== Item Menu ===\n");
    std::printf("1. List items\n");
    std::printf("2. Add item\n");
    std::printf("3. Show item detail\n");
    std::printf("4. Remove item\n");
    std::printf("0. Exit\n");
    std::printf("Select: ");
}

}  // namespace

int main() {
    ItemRepository repository;
    ConsoleView view;
    ItemController controller(repository, view);

    std::string line;
    while (true) {
        printMenu();
        if (!std::getline(std::cin, line)) {
            break;
        }

        if (line == "1") {
            controller.listItems();
        } else if (line == "2") {
            std::printf("Name: ");
            std::string name;
            std::getline(std::cin, name);

            std::printf("Value: ");
            std::string valueLine;
            std::getline(std::cin, valueLine);
            int value = 0;
            try {
                value = std::stoi(valueLine);
            } catch (const std::exception&) {
                view.showError("Invalid value: " + valueLine);
                continue;
            }
            controller.addItem(name, value);
        } else if (line == "3") {
            std::printf("Id: ");
            std::string idLine;
            std::getline(std::cin, idLine);
            try {
                controller.showItem(std::stoi(idLine));
            } catch (const std::exception&) {
                view.showError("Invalid id: " + idLine);
            }
        } else if (line == "4") {
            std::printf("Id: ");
            std::string idLine;
            std::getline(std::cin, idLine);
            try {
                controller.removeItem(std::stoi(idLine));
            } catch (const std::exception&) {
                view.showError("Invalid id: " + idLine);
            }
        } else if (line == "0") {
            break;
        } else {
            view.showError("Unknown option: " + line);
        }
    }

    return 0;
}
