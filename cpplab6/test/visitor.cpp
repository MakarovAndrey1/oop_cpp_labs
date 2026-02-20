#include <gtest/gtest.h>

#include "npc.hpp"
#include "elf.hpp"
#include "bandit.hpp"
#include "squirrel.hpp"
#include "visitor.hpp"


class VisitorTest : public testing::Test {
protected:
    void SetUp() override {
        elf = std::make_shared<Elf>("George", 0, 15);
        bandit = std::make_shared<Bandit>("John", 50, 15);
        squirrel = std::make_shared<Squirrel>("David", 100, 15);

        elf_visitor = std::make_shared<ElfVisitor>();
        bandit_visitor = std::make_shared<BanditVisitor>();
        squirrel_visitor = std::make_shared<SquirrelVisitor>();
    }

    std::shared_ptr<NPC> elf, bandit, squirrel;
    std::shared_ptr<Visitor> elf_visitor, bandit_visitor, squirrel_visitor;
};

TEST_F(VisitorTest, VisitTest) {
    ASSERT_TRUE(squirrel_visitor->visit(std::static_pointer_cast<Elf>(elf)));
    ASSERT_FALSE(squirrel_visitor->visit(std::static_pointer_cast<Bandit>(bandit)));
    ASSERT_FALSE(squirrel_visitor->visit(std::static_pointer_cast<Squirrel>(squirrel)));

    ASSERT_FALSE(elf_visitor->visit(std::static_pointer_cast<Elf>(elf)));
    ASSERT_TRUE(elf_visitor->visit(std::static_pointer_cast<Bandit>(bandit)));
    ASSERT_FALSE(elf_visitor->visit(std::static_pointer_cast<Squirrel>(squirrel)));

    ASSERT_FALSE(bandit_visitor->visit(std::static_pointer_cast<Elf>(elf)));
    ASSERT_FALSE(bandit_visitor->visit(std::static_pointer_cast<Bandit>(bandit)));
    ASSERT_TRUE(bandit_visitor->visit(std::static_pointer_cast<Squirrel>(squirrel)));
}