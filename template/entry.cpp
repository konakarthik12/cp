#pragma once
// konakarthik12
// cpp20
#include "wrapper.h"

namespace wrapped_std {

using std::begin;
using std::end;
using std::bit_width;
using std::cerr;
using std::cin;
using std::cout;
using std::declval;
using std::gcd;
using std::greater;
using std::initializer_list;
using std::invoke;
using std::ios_base;
using std::istream;
using std::less;
using std::max;
using std::min;
using std::ostream;
using std::plus;
using std::same_as;
using std::size;
using std::stringstream;
using std::tie;
using std::variant;
using std::exit;
using std::movable;
using std::optional;
using std::nullopt;
using std::index_sequence;
using std::index_sequence_for;
using std::fixed;
using std::setprecision;
using std::mt19937;
using std::random_access_iterator_tag;

using std::common_type_t;
using std::invoke_result_t;
using std::is_integral_v;
using std::make_unsigned_t;
using std::remove_reference_t;
using std::conditional_t;

using std::map;
using std::pair;
using std::tuple;
using std::array;
using std::predicate;
}

namespace ranges = std::ranges;
namespace views = std::views;
namespace chrono = std::chrono;

using namespace wrapped_std;
