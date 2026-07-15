#include <gtest/gtest.h>

#include "view/ConsoleView.h"

TEST(ConsoleViewTest, ShowItemsPrintsEachItem) {
    ConsoleView view;
    std::vector<Item> items{{1, "apple", 100}, {2, "banana", 200}};

    testing::internal::CaptureStdout();
    view.showItems(items);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("apple"), std::string::npos);
    EXPECT_NE(output.find("100"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
    EXPECT_NE(output.find("banana"), std::string::npos);
    EXPECT_NE(output.find("200"), std::string::npos);
}

TEST(ConsoleViewTest, ShowItemsPrintsMessageWhenEmpty) {
    ConsoleView view;

    testing::internal::CaptureStdout();
    view.showItems({});
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("No items"), std::string::npos);
}

TEST(ConsoleViewTest, ShowItemPrintsItemDetail) {
    ConsoleView view;
    Item item{1, "apple", 100};

    testing::internal::CaptureStdout();
    view.showItem(item);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("apple"), std::string::npos);
    EXPECT_NE(output.find("100"), std::string::npos);
}

TEST(ConsoleViewTest, ShowMessagePrintsMessage) {
    ConsoleView view;

    testing::internal::CaptureStdout();
    view.showMessage("hello");
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST(ConsoleViewTest, ShowErrorPrintsErrorPrefixedMessage) {
    ConsoleView view;

    testing::internal::CaptureStdout();
    view.showError("something went wrong");
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Error"), std::string::npos);
    EXPECT_NE(output.find("something went wrong"), std::string::npos);
}
