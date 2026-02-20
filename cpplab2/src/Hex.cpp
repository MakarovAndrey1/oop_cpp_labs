#include "../include/Hex.h"
#include <stdexcept>
#include <algorithm>
#include <cctype>

// Конструктор по умолчанию (число 0)
Hex::Hex() : size(1) {
    digits = new unsigned char[1];
    digits[0] = 0;
}

// Конструктор с размером и значением
Hex::Hex(const size_t& n, unsigned char t) : size(n) {
    if (n == 0) throw std::invalid_argument("Size cannot be zero");
    digits = new unsigned char[n];
    for (size_t i = 0; i < n; ++i) {
        digits[i] = t & 0x0F; // Оставляем только младшие 4 бита
    }
    normalize();
}

// Конструктор из списка инициализации
Hex::Hex(const std::initializer_list<unsigned char>& list) : size(list.size()) {
    if (list.size() == 0) throw std::invalid_argument("Initializer list cannot be empty");
    digits = new unsigned char[size];
    size_t i = 0;
    for (auto it = list.begin(); it != list.end(); ++it, ++i) {
        digits[i] = *it & 0x0F;
    }
    normalize();
}

// Конструктор из строки
Hex::Hex(const std::string& str) {
    if (str.empty()) throw std::invalid_argument("String cannot be empty");
    
    size = str.length();
    digits = new unsigned char[size];
    
    for (size_t i = 0; i < size; ++i) {
        digits[size - 1 - i] = charToDigit(str[i]); // Старший разряд в конце строки -> младший в начале массива
    }
    normalize();
}

// Конструктор копирования
Hex::Hex(const Hex& other) : size(other.size) {
    digits = new unsigned char[size];
    for (size_t i = 0; i < size; ++i) {
        digits[i] = other.digits[i];
    }
}

// Конструктор перемещения
Hex::Hex(Hex&& other) noexcept : digits(other.digits), size(other.size) {
    other.digits = nullptr;
    other.size = 0;
}

// Деструктор
Hex::~Hex() noexcept {
    delete[] digits;
}

// Нормализация (удаление ведущих нулей)
void Hex::normalize() {
    size_t newSize = size;
    while (newSize > 1 && digits[newSize - 1] == 0) {
        --newSize;
    }
    
    if (newSize != size) {
        unsigned char* newDigits = new unsigned char[newSize];
        for (size_t i = 0; i < newSize; ++i) {
            newDigits[i] = digits[i];
        }
        delete[] digits;
        digits = newDigits;
        size = newSize;
    }
}

// Преобразование char в цифру
unsigned char Hex::charToDigit(char c) const {
    c = std::toupper(c);
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    throw std::invalid_argument("Invalid hexadecimal digit: " + std::string(1, c));
}

// Преобразование цифры в char
char Hex::digitToChar(unsigned char d) const {
    d &= 0x0F;
    if (d < 10) return '0' + d;
    return 'A' + (d - 10);
}

// Получение размера
size_t Hex::getSize() const noexcept {
    return size;
}

// Преобразование в строку
std::string Hex::toString() const {
    if (size == 0) return "0";
    std::string result;
    for (size_t i = size; i > 0; --i) {
        result += digitToChar(digits[i - 1]);
    }
    return result;
}

// Сложение
Hex Hex::add(const Hex& other) const {
    size_t maxSize = std::max(size, other.size) + 1;
    unsigned char* resultDigits = new unsigned char[maxSize]();
    
    unsigned char carry = 0;
    for (size_t i = 0; i < maxSize; ++i) {
        unsigned char d1 = (i < size) ? digits[i] : 0;
        unsigned char d2 = (i < other.size) ? other.digits[i] : 0;
        
        unsigned char sum = d1 + d2 + carry;
        resultDigits[i] = sum & 0x0F;
        carry = sum >> 4;
    }
    
    Hex result;
    delete[] result.digits;
    result.digits = resultDigits;
    result.size = maxSize;
    result.normalize();
    return result;
}

// Вычитание
Hex Hex::subtract(const Hex& other) const {
    if (lessThan(other)) {
        throw std::invalid_argument("Result would be negative");
    }
    
    size_t maxSize = size;
    unsigned char* resultDigits = new unsigned char[maxSize]();
    
    unsigned char borrow = 0;
    for (size_t i = 0; i < maxSize; ++i) {
        unsigned char d1 = digits[i];
        unsigned char d2 = (i < other.size) ? other.digits[i] : 0;
        
        int diff = d1 - d2 - borrow;
        if (diff < 0) {
            diff += 16;
            borrow = 1;
        } else {
            borrow = 0;
        }
        resultDigits[i] = diff;
    }
    
    Hex result;
    delete[] result.digits;
    result.digits = resultDigits;
    result.size = maxSize;
    result.normalize();
    return result;
}

// Копирование
Hex Hex::copy() const {
    return Hex(*this);
}

// Сравнение на равенство
bool Hex::equals(const Hex& other) const noexcept {
    if (size != other.size) return false;
    for (size_t i = 0; i < size; ++i) {
        if (digits[i] != other.digits[i]) return false;
    }
    return true;
}

// Сравнение: больше
bool Hex::greaterThan(const Hex& other) const {
    if (size != other.size) return size > other.size;
    for (size_t i = size; i > 0; --i) {
        if (digits[i - 1] != other.digits[i - 1]) {
            return digits[i - 1] > other.digits[i - 1];
        }
    }
    return false;
}

// Сравнение: меньше
bool Hex::lessThan(const Hex& other) const {
    if (size != other.size) return size < other.size;
    for (size_t i = size; i > 0; --i) {
        if (digits[i - 1] != other.digits[i - 1]) {
            return digits[i - 1] < other.digits[i - 1];
        }
    }
    return false;
}

// Сложение с присваиванием
Hex Hex::addAssign(const Hex& other) const {
    return add(other);
}

// Вычитание с присваиванием
Hex Hex::subtractAssign(const Hex& other) const {
    return subtract(other);
}

// Получение цифр (для тестирования)
const unsigned char* Hex::getDigits() const noexcept {
    return digits;
}
