#include <gtest/gtest.h>

#include "npc.hpp"
#include "elf.hpp"
#include "bandit.hpp"
#include "squirrel.hpp"


class NPCTest : public testing::Test {
protected:
    void SetUp() override {
        elf = std::make_shared<Elf>("George", 0, 15);
        bandit = std::make_shared<Bandit>("John", 50, 15);
        squirrel = std::make_shared<Squirrel>("David", 100, 15);
    }

    std::shared_ptr<NPC> elf, bandit, squirrel;
};

TEST_F(NPCTest, AcceptTest) {
    ASSERT_TRUE(elf->accept(squirrel));
    ASSERT_FALSE(bandit->accept(squirrel));
    ASSERT_FALSE(squirrel->accept(squirrel));

    ASSERT_FALSE(elf->accept(elf));
    ASSERT_TRUE(bandit->accept(elf));
    ASSERT_FALSE(squirrel->accept(elf));

    ASSERT_FALSE(elf->accept(bandit));
    ASSERT_FALSE(bandit->accept(bandit));
    ASSERT_TRUE(squirrel->accept(bandit));
}

TEST_F(NPCTest, IsCloseTest) {
    ASSERT_TRUE(elf->is_close(bandit, 50));
    ASSERT_TRUE(elf->is_close(squirrel, 100));
    ASSERT_FALSE(elf->is_close(bandit, 25));
    ASSERT_FALSE(elf->is_close(squirrel, 50));
}