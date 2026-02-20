#include "../include/Figure.h"

// Явная инстанциация шаблонов
template class Figure<int>;
template class Figure<float>;
template class Figure<double>;

template std::ostream& operator<<(std::ostream& os, const Figure<int>& figure);
template std::ostream& operator<<(std::ostream& os, const Figure<float>& figure);
template std::ostream& operator<<(std::ostream& os, const Figure<double>& figure);

template std::istream& operator>>(std::istream& is, Figure<int>& figure);
template std::istream& operator>>(std::istream& is, Figure<float>& figure);
template std::istream& operator>>(std::istream& is, Figure<double>& figure);