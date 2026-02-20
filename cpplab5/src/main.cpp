#include <iostream>
#include <string>
#include "FixedBlockMemoryResource.h"
#include "PmrStack.h"
#include <memory> // Для std::make_unique

struct ComplexType {
    int id;
    double value;
    std::string name;

    // Конструктор
    ComplexType(int i, double v, std::string n)
        : id(i), value(v), name(std::move(n)) {}

    // Конструктор по умолчанию (для clear, например)
    ComplexType() : id(0), value(0.0), name("") {}

    // Оператор вывода для удобства
    friend std::ostream& operator<<(std::ostream& os, const ComplexType& obj) {
        os << "ComplexType{id=" << obj.id << ", value=" << obj.value << ", name='" << obj.name << "'}";
        return os;
    }
};

int main() {
    std::cout << "=== Тестирование PmrStack с int ===\n";

    // Создаем memory_resource с блоком 64 байта
    // Размер пула 1MB (1024 * 1024 байт)
    auto resource = std::make_unique<FixedBlockMemoryResource>(64, 1024 * 1024);

    // Создаем стек, используя наш ресурс
    PmrStack<int> int_stack(resource.get()); 

    // Заполняем стек
    for (int i = 1; i <= 10; ++i) {
        int_stack.push(i * 10);
    }

    std::cout << "Размер стека: " << int_stack.size() << "\n";

    // Выводим содержимое через итератор
    std::cout << "Содержимое стека (от первого добавленного до последнего): ";
    for (auto it = int_stack.begin(); it != int_stack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Тестируем операции
    std::cout << "Верхний элемент: " << int_stack.top() << "\n";
    int_stack.pop();
    std::cout << "После pop(), размер: " << int_stack.size() << ", верхний элемент: " << int_stack.top() << "\n";

    std::cout << "\n=== Тестирование PmrStack с ComplexType ===\n";

    PmrStack<ComplexType> complex_stack(resource.get());

    // Заполняем стек сложными объектами
    complex_stack.push(ComplexType(1, 3.14, "first"));
    complex_stack.push(ComplexType(2, 2.718, "second"));
    complex_stack.push(ComplexType(3, 1.414, "third"));

    std::cout << "Размер стека: " << complex_stack.size() << "\n";
    std::cout << "Верхний элемент: " << complex_stack.top() << "\n";

    // Выводим через range-based for loop (использует итераторы)
    std::cout << "Содержимое стека: ";
    for (const auto& item : complex_stack) {
        std::cout << item << " ";
    }
    std::cout << "\n";

    // Очищаем стек
    complex_stack.clear();
    std::cout << "После clear(), пуст ли стек: " << (complex_stack.empty() ? "да" : "нет") << "\n";

    // Проверка повторного использования после pop()
    std::cout << "После clear(), размер: " << complex_stack.size() << "\n";
    complex_stack.push(ComplexType(4, 1.618, "fourth"));
    std::cout << "После push(), размер: " << complex_stack.size() << ", верхний элемент: " << complex_stack.top() << "\n";

    std::cout << "\n=== Демонстрация переиспользования памяти ===\n";

    // Многократное использование одного и того же стека
    // Важно: Используем один и тот же resource.
    for (int test = 0; test < 3; ++test) {
        std::cout << "Тест " << test + 1 << ": ";
        PmrStack<int> temp_stack(resource.get()); // Создаем стек с тем же аллокатором
        for (int i = 0; i < 5; ++i) {
            temp_stack.push(i);
        }
        std::cout << "размер = " << temp_stack.size() << ", top = " << temp_stack.top() << "\n";
        // temp_stack уничтожается здесь, вызывая do_deallocate через свой деструктор
    }

    std::cout << "\nЗавершение работы. FixedBlockMemoryResource при уничтожении очистит весь выделенный пул.\n";

    return 0;
}