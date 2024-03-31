#include "rational.h"
#include <numeric>

Rational::Rational() = default;

Rational::Rational(int value) : numer_(value), denom_(1) {  // NOLINT
}

Rational::Rational(int numer, int denom) : numer_(numer), denom_(denom) {
    if (denom_ == 0) {
        throw RationalDivisionByZero{};
    }
    int ratio_gcd = std::gcd(std::abs(numer_), std::abs(denom_));
    numer_ /= ratio_gcd;
    denom_ /= ratio_gcd;
    if (denom_ < 0) {
        numer_ *= -1;
        denom_ *= -1;
    }
}

int Rational::GetNumerator() const {
    return numer_;
}

int Rational::GetDenominator() const {
    return denom_;
}

void Rational::SetNumerator(int value) {
    Set(value, denom_);
}

void Rational::SetDenominator(int value) {
    Set(numer_, value);
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    lhs.Set(static_cast<int64_t>(lhs.numer_) * rhs.denom_ + static_cast<int64_t>(rhs.numer_) * lhs.denom_,
            static_cast<int64_t>(lhs.denom_) * rhs.denom_);
    return lhs;
}

Rational& operator*=(Rational& lhs, const Rational& rhs) {
    lhs.Set(static_cast<int64_t>(lhs.numer_) * rhs.numer_, static_cast<int64_t>(lhs.denom_) * rhs.denom_);
    return lhs;
}

Rational& operator++(Rational& ratio) {
    ratio.numer_ += ratio.denom_;
    return ratio;
}

Rational& operator--(Rational& ratio) {
    ratio.numer_ -= ratio.denom_;
    return ratio;
}

std::istream& operator>>(std::istream& is, Rational& ratio) {
    std::string s;
    is >> s;
    auto delim_it = find(s.begin(), s.end(), '/');

    if (delim_it != s.end()) {
        int64_t numer = stoll(std::string{s.begin(), delim_it});
        int64_t denom = stoll(std::string{next(delim_it), s.end()});
        ratio.Set(numer, denom);
    } else {
        int64_t numer = stoll(s);
        ratio.Set(numer, 1);
    }

    return is;
}

void Rational::Set(int64_t numer, int64_t denom) {
    if (denom == 0) {
        throw RationalDivisionByZero{};
    }
    int64_t ratio_gcd = std::gcd(std::abs(numer), std::abs(denom));
    numer_ = static_cast<int>(numer / ratio_gcd);
    denom_ = static_cast<int>(denom / ratio_gcd);
    if (denom_ < 0) {
        numer_ *= -1;
        denom_ *= -1;
    }
}

Rational operator+(const Rational& ratio) {
    return ratio;
}

Rational operator-(const Rational& ratio) {
    return Rational(-ratio.GetNumerator(), ratio.GetDenominator());
}

Rational& operator-=(Rational& lhs, const Rational& rhs) {
    return lhs += (-rhs);
}

Rational& operator/=(Rational& lhs, const Rational& rhs) {
    return lhs *= Rational(rhs.GetDenominator(), rhs.GetNumerator());
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational tmp = lhs;
    return tmp += rhs;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    Rational tmp = lhs;
    return tmp -= rhs;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    Rational tmp = lhs;
    return tmp *= rhs;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational tmp = lhs;
    return tmp /= rhs;
}

Rational operator++(Rational& ratio, int) {
    Rational tmp = ratio;
    ++ratio;
    return tmp;
}

Rational operator--(Rational& ratio, int) {
    Rational tmp = ratio;
    --ratio;
    return tmp;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return static_cast<int64_t>(lhs.GetNumerator()) * rhs.GetDenominator() <
           static_cast<int64_t>(rhs.GetNumerator()) * lhs.GetDenominator();
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return rhs < lhs;
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return !(lhs > rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs);
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return (lhs <= rhs && lhs >= rhs);
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Rational& ratio) {
    os << ratio.GetNumerator();
    if (ratio.GetDenominator() != 1) {
        os << '/' << ratio.GetDenominator();
    }
    return os;
}
