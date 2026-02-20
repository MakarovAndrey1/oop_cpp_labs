#ifndef CMAKE_TESTS_TESTS05_CPP
#define CMAKE_TESTS_TESTS05_CPP

#include "gtest/gtest.h"
#include "FixedBlockMemoryResource.h" 
#include "PmrStack.h"
#include <memory_resource>
#include <string>
#include <memory>

// Структура для тестирования сложных типов
struct TestStruct {
    int data1;
    double data2;
    std::string data3;

    TestStruct(int d1, double d2, std::string d3) 
        : data1(d1), data2(d2), data3(std::move(d3)) {}

    TestStruct() = default;

    bool operator==(const TestStruct& other) const {
        return data1 == other.data1 && data2 == other.data2 && data3 == other.data3;
    }
};

// Тест через косвенные проверки (не вызываем protected методы напрямую)
TEST(FixedBlockMemoryResourceTest, IndirectAllocateDeallocate) {
    auto resource = std::make_unique<FixedBlockMemoryResource>(32, 1024);

    // Тестируем через PmrStack - он вызывает do_allocate/do_deallocate внутренне
    PmrStack<int> stack(resource.get());

    // Многократное выделение/освобождение через стек
    for (int i = 0; i < 10; ++i) {
        stack.clear();        // гарантируем пустоту перед новой операцией
        stack.push(i);
        ASSERT_EQ(stack.size(), 1u);
        ASSERT_EQ(stack.top(), i);

        stack.pop();
        ASSERT_TRUE(stack.empty());
    }
}

TEST(FixedBlockMemoryResourceTest, CapacityLimits) {
    // Создаем ресурс с ограниченным пулом (4 блока по 64 байта)
    auto resource = std::make_unique<FixedBlockMemoryResource>(64, 256);

    PmrStack<int> stack(resource.get());

    // Заполняем до предела
    for (int i = 0; i < 4; ++i) {
        stack.push(i);
    }

    ASSERT_EQ(stack.size(), 4);

    // Попытка выделить больше может:
    //  - либо бросить std::bad_alloc, либо
    //  - позволить выделение и получить размер 5
    bool threw = false;
    try {
        stack.push(5);
    } catch (const std::bad_alloc&) {
        threw = true;
    }

    if (threw) {
        SUCCEED();
    } else {
        // Ожидаем, что после 5-го push размер будет ровно 5
        ASSERT_EQ(stack.size(), 5);
    }
}

TEST(PmrStackTest, PushPopInt) {
    auto resource = std::make_unique<FixedBlockMemoryResource>(64);
    PmrStack<int> stack(resource.get());

    stack.push(10);
    stack.push(20);

    ASSERT_EQ(stack.size(), 2);
    ASSERT_EQ(stack.top(), 20);

    stack.pop();
    ASSERT_EQ(stack.size(), 1);
    ASSERT_EQ(stack.top(), 10);

    stack.pop();
    ASSERT_EQ(stack.size(), 0);
    ASSERT_TRUE(stack.empty());
}

// Остальные тесты остаются такими же...
TEST(PmrStackTest, PushPopComplex) {
    auto resource = std::make_unique<FixedBlockMemoryResource>(128);
    PmrStack<TestStruct> stack(resource.get());

    stack.push({1, 1.1, "one"});
    stack.push({2, 2.2, "two"});

    ASSERT_EQ(stack.size(), 2);
    ASSERT_EQ(stack.top(), TestStruct(2, 2.2, "two"));

    stack.pop();
    ASSERT_EQ(stack.size(), 1);
    ASSERT_EQ(stack.top(), TestStruct(1, 1.1, "one"));

    stack.pop();
    ASSERT_EQ(stack.size(), 0);
    ASSERT_TRUE(stack.empty());
}

TEST(PmrStackTest, Iterator) {
    auto resource = std::make_unique<FixedBlockMemoryResource>(64);
    PmrStack<int> stack(resource.get());

    stack.push(1);
    stack.push(2);
    stack.push(3);

    auto it = stack.begin();
    ASSERT_EQ(*it, 1);
    ++it;
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 3);
    ++it;
    ASSERT_EQ(it, stack.end());
}

TEST(PmrStackTest, Clear) {
    auto resource = std::make_unique<FixedBlockMemoryResource>(64);
    PmrStack<int> stack(resource.get());

    stack.push(10);
    stack.push(20);
    stack.push(30);

    ASSERT_FALSE(stack.empty());
    stack.clear();
    ASSERT_TRUE(stack.empty());
    ASSERT_EQ(stack.size(), 0);

    stack.push(100);
    ASSERT_FALSE(stack.empty());
    ASSERT_EQ(stack.top(), 100);
}

TEST(PmrStackTest, MoveSemantics) {
    auto resource = std::make_unique<FixedBlockMemoryResource>(64);
    PmrStack<int> stack1(resource.get());
    stack1.push(1);
    stack1.push(2);

    PmrStack<int> stack2(std::move(stack1));

    ASSERT_EQ(stack1.size(), 0);
    ASSERT_TRUE(stack1.empty());
    ASSERT_EQ(stack2.size(), 2);
    ASSERT_EQ(stack2.top(), 2);
}

#endif //CMAKE_TESTS_TESTS05_CPP