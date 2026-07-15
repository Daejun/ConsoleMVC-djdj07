#include <gtest/gtest.h>

#include "controller/ItemController.h"
#include "model/ItemRepository.h"
#include "StubView.h"

TEST(ItemControllerTest, ListItemsShowsAllItemsFromRepository) {
    ItemRepository repo;
    repo.add("apple", 100);
    repo.add("banana", 200);
    StubView view;
    ItemController controller(repo, view);

    controller.listItems();

    ASSERT_EQ(view.lastItems.size(), 2);
    EXPECT_EQ(view.lastItems[0].name, "apple");
    EXPECT_EQ(view.lastItems[1].name, "banana");
}

TEST(ItemControllerTest, AddItemAddsToRepositoryAndShowsMessage) {
    ItemRepository repo;
    StubView view;
    ItemController controller(repo, view);

    controller.addItem("apple", 100);

    ASSERT_EQ(repo.list().size(), 1);
    EXPECT_EQ(repo.list()[0].name, "apple");
    EXPECT_FALSE(view.lastMessage.empty());
}

TEST(ItemControllerTest, ShowItemShowsExistingItem) {
    ItemRepository repo;
    Item added = repo.add("apple", 100);
    StubView view;
    ItemController controller(repo, view);

    controller.showItem(added.id);

    ASSERT_TRUE(view.lastItem.has_value());
    EXPECT_EQ(view.lastItem->name, "apple");
}

TEST(ItemControllerTest, ShowItemShowsErrorForMissingId) {
    ItemRepository repo;
    StubView view;
    ItemController controller(repo, view);

    controller.showItem(999);

    EXPECT_FALSE(view.lastItem.has_value());
    EXPECT_FALSE(view.lastError.empty());
}

TEST(ItemControllerTest, RemoveItemDeletesExistingItemAndShowsMessage) {
    ItemRepository repo;
    Item added = repo.add("apple", 100);
    StubView view;
    ItemController controller(repo, view);

    controller.removeItem(added.id);

    EXPECT_FALSE(repo.find(added.id).has_value());
    EXPECT_FALSE(view.lastMessage.empty());
}

TEST(ItemControllerTest, RemoveItemShowsErrorForMissingId) {
    ItemRepository repo;
    StubView view;
    ItemController controller(repo, view);

    controller.removeItem(999);

    EXPECT_FALSE(view.lastError.empty());
}
