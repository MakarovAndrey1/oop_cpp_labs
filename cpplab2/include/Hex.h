#ifndef HEX_H
#define HEX_H

#include <string>
#include <initializer_list>

class Hex {
private:
    unsigned char* digits;  // Динамический массив цифр (0-15)
    size_t size;            // Количество цифр (размер числа)
    
    // Вспомогательные методы
    void normalize();       // Удаление ведущих нулей
    unsigned char charToDigit(char c) const; // Преобразование char в цифру (0-15)
    char digitToChar(unsigned char d) const; // Преобразование цифры в char ('0'-'F')
    
public:
    // Конструкторы и деструктор
    Hex();
    Hex(const size_t& n, unsigned char t = 0);
    Hex(const std::initializer_list<unsigned char>& list);
    Hex(const std::string& str);
    Hex(const Hex& other);           // Конструктор копирования
    Hex(Hex&& other) noexcept;      // Конструктор перемещения
    ~Hex() noexcept;                // Деструктор

    // Методы доступа
    size_t getSize() const noexcept;
    std::string toString() const;    // Представление в виде строки

    // Арифметические операции (с созданием нового объекта)
    Hex add(const Hex& other) const;     // Сложение
    Hex subtract(const Hex& other) const; // Вычитание (если результат отрицательный - исключение)
    Hex copy() const;                    // Копирование

    // Операции сравнения
    bool equals(const Hex& other) const noexcept; // Равно
    bool greaterThan(const Hex& other) const;     // Больше
    bool lessThan(const Hex& other) const;        // Меньше

    // Операции с присваиванием (возвращают новый объект)
    Hex addAssign(const Hex& other) const;        // +=
    Hex subtractAssign(const Hex& other) const;   // -=

    // Вспомогательные методы для тестирования
    const unsigned char* getDigits() const noexcept;
};

#endif // HEX_H
