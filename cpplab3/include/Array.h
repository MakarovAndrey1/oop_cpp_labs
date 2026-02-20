#ifndef ARRAY_H
#define ARRAY_H

#include "Figure.h"
#include <vector>
#include <memory>

class Array {
private:
    std::vector<std::shared_ptr<Figure>> figures;
    
public:
    // Добавление фигуры
    void addFigure(std::shared_ptr<Figure> figure);
    
    // Удаление фигуры по индексу
    void removeFigure(size_t index);
    
    // Общая площадь всех фигур
    double totalArea() const;
    
    // Вывод информации о всех фигурах
    void printAll() const;
    
    // Размер массива
    size_t size() const;
    
    // Получение фигуры по индексу
    std::shared_ptr<Figure> getFigure(size_t index) const;
    
    // Очистка массива
    void clear();
};

#endif