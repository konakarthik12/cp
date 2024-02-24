#pragma once

#ifdef INLINER
#include "../main.cpp"
#else
#ifndef EDITOR
#define XSTR(x) #x
#define STR(x) XSTR(x)
#ifndef ENTRY
#define ENTRY main
#endif
// clang-format off
#define ENTRY_FILE STR(../ENTRY.cpp)
#include ENTRY_FILE
// clang-format on
#endif
#endif
