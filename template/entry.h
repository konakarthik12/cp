#pragma once
// konakarthik12
// cpp20
#include "wrapper.h"

namespace wrapped_std {

using std::begin;
using std::cerr;
using std::cin;
using std::cout;
using std::declval;
using std::end;
using std::exit;
using std::fixed;
using std::gcd;
using std::greater;
using std::index_sequence;
using std::index_sequence_for;
using std::initializer_list;
using std::invoke;
using std::ios_base;
using std::istream;
using std::less;
using std::max;
using std::min;
using std::mt19937;
using std::nullopt;
using std::optional;
using std::ostream;
using std::plus;
using std::random_access_iterator_tag;
using std::setprecision;
using std::size;
using std::stringstream;
using std::swap;
using std::tie;

using std::common_type_t;
using std::conditional_t;
using std::invoke_result_t;
using std::is_integral_v;
using std::is_signed_v;
using std::is_unsigned_v;
using std::make_unsigned_t;
using std::remove_reference_t;
using std::enable_if_t;
using std::is_same_v;
using std::is_invocable_v;

using std::array;
using std::map;
using std::pair;
using std::tuple;
}



namespace chrono = std::chrono;

using namespace wrapped_std;