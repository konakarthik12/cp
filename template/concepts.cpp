#pragma once
#include "wrapper.h"

template <typename T>
struct HasValueType{
  template <typename U>
  static std::true_type test(typename U::value_type*);

  template <typename>
  static std::false_type test(...);

  static constexpr bool value = decltype(test<T>(nullptr))::value;
};

template <typename T>
struct HasValueType2D {
  template <typename U>
  static std::true_type test(typename U::value_type::value_type*);

  template <typename>
  static std::false_type test(...);

  static constexpr bool value = decltype(test<T>(nullptr))::value;
};

template <typename T>
struct HasValueType1D {
  static constexpr bool value = HasValueType<T>::value && !HasValueType2D<T>::value;
};


template <typename T>
struct HasIter {
  template <typename U>
  static auto test(U& container) -> decltype(container.begin(), container.end(), std::true_type{});

  template <typename>
  static auto test(...) -> std::false_type;

  static constexpr bool value = decltype(test<T>(std::declval<T&>()))::value;
};

template <typename T>
struct Printable {
  template <typename U>
  static auto test(std::ostream& os, const U& val) -> decltype(os << val, std::true_type{});

  template <typename>
  static auto test(...) -> std::false_type;

  static constexpr bool value = decltype(test<T>(std::cout, std::declval<const T&>()))::value;
};


template <typename T>
struct is_readable {
  template <typename U>
  static auto test(U* ptr) -> decltype(std::declval<std::istream&>() >> *ptr, std::true_type{});

  template <typename>
  static auto test(...) -> std::false_type;

  static constexpr bool value = decltype(test<T>(nullptr))::value;
};

template<typename T1>
constexpr bool Readable = is_readable<T1>::value;

template <typename T1>
struct is_readable_1d {
  template <typename U>
  static constexpr bool test(...) {
    return false;
  }

  template <typename U>
  static constexpr auto test(int)
      -> decltype(is_readable<typename std::remove_reference_t<U>::value_type>::value, bool{}) {
    return true;
  }

  static constexpr bool value = test<T1>(0);
};

template<typename T1>
constexpr bool Readable1D = is_readable_1d<T1>::value;


template <typename T1>
struct is_readable_2d {
  template <typename U>
  static constexpr bool test(...) {
    return false;
  }

  template <typename U>
  static constexpr auto test(int) -> decltype(is_readable<typename std::remove_reference_t<
                                                  typename std::remove_reference_t<U>::value_type>::value_type>::value,
                                              bool{}) {
    return true;
  }

  static constexpr bool value = test<T1>(0);
};

template<typename T1>
constexpr bool Readable2D = is_readable_2d<T1>::value;
