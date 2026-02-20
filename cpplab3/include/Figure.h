#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <vector>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Figure {
protected:
    std::vector<std::pair<double, double>> vertices;
    
public:
    virtual ~Figure() = default;
    
    // 1. Вычисление геометрического центра
    virtual std::pair<double, double> center() const = 0;
    
    // 2. Вывод координат вершин через operator<<
    virtual void print(std::ostream& os) const = 0;
    
    // 3. Чтение данных через operator>>
    virtual void read(std::istream& is) = 0;
    
    // 4. Площадь через оператор приведения к double
    virtual operator double() const = 0;
    
    // Для удобства
    virtual double area() const = 0;
    
    // Операторы сравнения
    virtual bool operator==(const Figure& other) const = 0;
    
    // Оператор присваивания
    virtual Figure& operator=(const Figure& other) = 0;
};

// Глобальные операторы ввода/вывода
inline std::ostream& operator<<(std::ostream& os, const Figure& figure) {
    figure.print(os);
    return os;
}

inline std::istream& operator>>(std::istream& is, Figure& figure) {
    figure.read(is);
    return is;
}

#endif