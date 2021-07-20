#ifndef RATIONAL_HH
#define RATIONAL_HH
#include <iostream>
 
template<typename Number>
Number _gcd(const Number &a, const Number &b) {
  if (b == Number(0)) return a;
  return _gcd(Number(b), Number(a % b));
}
 
template<typename Number>
class Rational {
  Number num, div, num0, num1;
  Rational fix() {
    if (div < num0) {
      num = num0 - num;
      div = num0 - div;
    }
    if (num == num0) {
      div = Number(1);
      return *this;
    }
    Number gcd = _gcd(num, div);
    if (gcd < num0) {
      gcd = num0 - gcd;
    }
    if (gcd == num1) return *this;
    num /= gcd;
    div /= gcd;
    return *this;
  }
  void assign(const Rational &elem) {
    num = elem.num;
    div = elem.div;
  }
public:
  Rational() : num(0), div(1), num0(0), num1(1) {};
  Rational(Number _num) : num(_num), div(1), num0(0), num1(1) {
  };
  Rational(Number _num, Number _div) : num(_num), div(_div), num0(0), num1(1)  {
    fix();
  }
 
  Rational operator*(const Rational &sec) const {
    return Rational(num * sec.num, div * sec.div).fix();
  }
  Rational operator/(const Rational &sec) const {
    return Rational(num * sec.div, div * sec.num).fix();
  }
  Rational operator+(const Rational &sec) const {
    return Rational(num * sec.div + sec.num * div, sec.div * div).fix();
  }
  Rational operator-(const Rational &sec) const {
    return operator+(-sec);
  }
  Rational operator+() const {
    return *this;
  }
  Rational operator-() const {
    return Rational(-num, div).fix();
  }
 
  Rational& operator+=(const Rational &sec) &{assign(*this + sec); return *this;}
  Rational& operator-=(const Rational &sec) &{assign(*this - sec); return *this;}
  Rational& operator*=(const Rational &sec) &{assign(*this * sec); return *this;}
  Rational& operator/=(const Rational &sec) &{assign(*this / sec); return *this;}
  Rational& operator++() &{num += div; return *this;}
  Rational& operator--()  &{num -= div; return *this;}
 
  Rational operator++() const& {return Rational(num + div, div);}
  Rational operator--() const& {return Rational(num - div, div);}
 
  Rational operator++(int) &{auto ret = *this; num += div; return ret;}
  Rational operator--(int) &{auto ret = *this; num -= div; return ret;}
  const Rational operator++(int) const& {return *this;}
  const Rational operator--(int) const& {return *this;}
 
  Rational operator++(int) && {return std::move(*this);}
  Rational operator--(int) && {return std::move(*this);}
  Rational operator++() && {return std::move(*this);}
  Rational operator--() && {return std::move(*this);}// why can't!!!!!*/
 
  bool operator<(const Rational &sec) const {
    return num * sec.div < sec.num * div;
  }
  bool operator==(const Rational &sec) const {
    return num * sec.div == sec.num * div;
  }
  bool operator!=(const Rational &sec) const {
    return !operator==(sec);
  }
  bool operator>(const Rational &sec) const {
    return num * sec.div > sec.num * div;
  }
  bool operator>=(const Rational &sec) const {
    return !operator<(sec);
  }
  bool operator<=(const Rational &sec) const {
    return !operator>(sec);
  }
  friend std::ostream& operator<<(std::ostream& out, const Rational& elem) {
    std::cout << elem.num << "/" << elem.div;
    return out;
  }
};
 
#endif
