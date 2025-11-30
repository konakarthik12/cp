#pragma once
#include "bool.cpp"
#include "con.cpp"

template <typename T, const int offset = 0>
using vec = Con<NotBool_t<T>, std::vector, offset>;