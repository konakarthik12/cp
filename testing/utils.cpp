#include <cmath>
#include <limits>
#include <type_traits>
template <typename T>
concept Numeric = std::is_arithmetic_v<T>;
const ld eps = 1e-11;

class ld_approx {
 private:
  ld value;
  ld tolerance;

 public:
  ld_approx(ld val, ld tol = std::numeric_limits<ld>::epsilon()) : value(val), tolerance(tol) {
  }

  // Getter for the wrapped value
  operator ld() {
    return value;
  }


  ld_approx& operator*=(Numeric auto const& b) {
   value *= static_cast<ld>(b);
   return *this;
  }
  // Three-way comparison operator
  auto operator<=>(const ld_approx& other) const {
    ld diff = value - other.value;
    if (std::abs(diff) <= tolerance) return std::strong_ordering::equal;
    else if (diff < 0) return std::strong_ordering::less;
    else return std::strong_ordering::greater;
  }

  auto operator<=>(Numeric auto const& other) const {
    return *this <=> ld_approx(other);
  }
  auto operator==(ld_approx const& other) const {
    return this->value - other.value < eps;
  }
  auto operator==(Numeric auto const& other) const {
    return *this == ld_approx(other);
  }
  friend std::ostream& operator<<(std::ostream& os, const ld_approx& ld_app) {
    os << ld_app.value;
    return os;
  }
};
