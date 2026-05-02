#pragma once
#include "bool.cpp"
#include "list.cpp"

template <typename T, const int offset = 0>
using vec = list<NotBool_t<T>, std::vector, offset>;