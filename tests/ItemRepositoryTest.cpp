#include <gtest/gtest.h>
#include "model/ItemRepository.h"

TEST(ItemRepositoryTest, StartsEmpty) {
    ItemRepository repo;
    EXPECT_TRUE(repo.list().empty());
}

TEST(ItemRepositoryTest, AddAssignsIncrementingIds) {
    ItemRepository repo;
    Item first = repo.add("apple", 100);
    Item second = repo.add("banana", 200);

    EXPECT_EQ(first.id, 1);
    EXPECT_EQ(second.id, 2);
}

TEST(ItemRepositoryTest, AddStoresNameAndValue) {
    ItemRepository repo;
    Item added = repo.add("apple", 100);

    EXPECT_EQ(added.name, "apple");
    EXPECT_EQ(added.value, 100);
}

TEST(ItemRepositoryTest, ListReturnsAllAddedItems) {
    ItemRepository repo;
    repo.add("apple", 100);
    repo.add("banana", 200);

    auto items = repo.list();

    ASSERT_EQ(items.size(), 2);
    EXPECT_EQ(items[0].name, "apple");
    EXPECT_EQ(items[1].name, "banana");
}

TEST(ItemRepositoryTest, FindReturnsExistingItem) {
    ItemRepository repo;
    Item added = repo.add("apple", 100);

    auto found = repo.find(added.id);

    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->name, "apple");
}

TEST(ItemRepositoryTest, FindReturnsNulloptForMissingId) {
    ItemRepository repo;

    auto found = repo.find(999);

    EXPECT_FALSE(found.has_value());
}

TEST(ItemRepositoryTest, RemoveDeletesExistingItemAndReturnsTrue) {
    ItemRepository repo;
    Item added = repo.add("apple", 100);

    bool removed = repo.remove(added.id);

    EXPECT_TRUE(removed);
    EXPECT_FALSE(repo.find(added.id).has_value());
    EXPECT_TRUE(repo.list().empty());
}

TEST(ItemRepositoryTest, RemoveReturnsFalseForMissingId) {
    ItemRepository repo;

    bool removed = repo.remove(999);

    EXPECT_FALSE(removed);
}
