//#pragma once
//#include <cstdint>
//#include <compare>
//#include <type_traits>
//#include <iostream>
//
//struct i32 {
//    int32_t value = 0;  // default initialize to 0
//
//    // Constructors
//    constexpr i32() = default;
//    constexpr i32(int32_t v) : value(v) {}
//
//    // Implicit conversion
//    constexpr operator int32_t() const { return value; }
//
//    // Unary operators
//    constexpr i32 operator+() const { return +value; }
//    constexpr i32 operator-() const { return -value; }
//    constexpr i32 operator~() const { return ~value; }
//
//    // Increment/Decrement
//    constexpr i32& operator++() { ++value; return *this; }
//    constexpr i32 operator++(int) { i32 tmp = *this; ++value; return tmp; }
//    constexpr i32& operator--() { --value; return *this; }
//    constexpr i32 operator--(int) { i32 tmp = *this; --value; return tmp; }
//
//    // Compound assignments with i32
//    constexpr i32& operator+=(const i32& other) { value += other.value; return *this; }
//    constexpr i32& operator-=(const i32& other) { value -= other.value; return *this; }
//    constexpr i32& operator*=(const i32& other) { value *= other.value; return *this; }
//    constexpr i32& operator/=(const i32& other) { value /= other.value; return *this; }
//    constexpr i32& operator%=(const i32& other) { value %= other.value; return *this; }
//    constexpr i32& operator&=(const i32& other) { value &= other.value; return *this; }
//    constexpr i32& operator|=(const i32& other) { value |= other.value; return *this; }
//    constexpr i32& operator^=(const i32& other) { value ^= other.value; return *this; }
//    constexpr i32& operator<<=(int shift) { value <<= shift; return *this; }
//    constexpr i32& operator>>=(int shift) { value >>= shift; return *this; }
//
//    // Three-way comparison with i32
//    constexpr auto operator<=>(const i32&) const = default;
//    constexpr bool operator==(const i32&) const = default;
//};
//
//// === Mixed-type operators ===
//
//#define BINARY_OP(op) \
//template <typename T> \
//requires std::is_integral_v<T> \
//constexpr i32 operator op(const i32& lhs, T rhs) { return i32(lhs.value op rhs); } \
//\
//template <typename T> \
//requires std::is_integral_v<T> \
//constexpr i32 operator op(T lhs, const i32& rhs) { return i32(lhs op rhs.value); }
//
//#define CMP_OP(op) \
//template <typename T> \
//requires std::is_integral_v<T> \
//constexpr bool operator op(const i32& lhs, T rhs) { return lhs.value op rhs; } \
//\
//template <typename T> \
//requires std::is_integral_v<T> \
//constexpr bool operator op(T lhs, const i32& rhs) { return lhs op rhs.value; }
//
//BINARY_OP(+)
//BINARY_OP(-)
//BINARY_OP(*)
//BINARY_OP(/)
//BINARY_OP(%)
//BINARY_OP(&)
//BINARY_OP(|)
//BINARY_OP(^)
//BINARY_OP(<<)
//BINARY_OP(>>)
//
//CMP_OP(==)
//CMP_OP(!=)
//CMP_OP(<)
//CMP_OP(<=)
//CMP_OP(>)
//CMP_OP(>=)
//
//#undef BINARY_OP
//#undef CMP_OP
//
//// Stream output
//inline std::ostream& operator<<(std::ostream& os, const i32& x) {
//    return os << x.value;
//}
