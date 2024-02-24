#pragma once
#include "wrapper.h"
template <typename T>
concept HasValueType = requires { typename T::value_type; };
template <typename T>
concept HasValueType2D = requires { typename T::value_type::value_type; };

template <typename T>
concept HasValueType1D = requires {
  requires HasValueType<T>;
  requires !HasValueType2D<T>;
};
template <typename T>
concept HasIter = requires(T& container) {
  { container.begin() } -> same_as<decltype(container.end())>;
  { container.end() } -> same_as<decltype(container.begin())>;
};
template <typename T>
concept Printable = requires(ostream& os, const T& val) {
  { os << val } -> same_as<ostream&>;
};

template <typename T>
concept Readable = requires(std::istream& is, T& val) {
  { is >> val } -> std::same_as<std::istream&>;
};

template <typename T1>
concept Readable1D = requires(istream& is, const T1&) {
  { Readable<typename remove_reference_t<T1>::value_type> };
};

template <typename T1>
concept Readable2D = requires(istream& is, const T1&) {
  { Readable<typename remove_reference_t<T1>::value_type::value_type> };
};
