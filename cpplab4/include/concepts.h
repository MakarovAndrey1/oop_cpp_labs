#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <type_traits>

// Concept для проверки скалярного типа (C++20)
#ifdef __cpp_concepts
#include <concepts>
template<typename T>
concept Scalar = std::is_scalar_v<T>;
#else
// Альтернатива для совместимости с C++17
template<typename T>
struct IsScalar {
    static constexpr bool value = std::is_scalar_v<T>;
};

template<typename T>
inline constexpr bool IsScalar_v = IsScalar<T>::value;
#endif

#endif