#ifndef CPP_PROJECTS_SOLUTION_H
#define CPP_PROJECTS_SOLUTION_H
 
#include <iostream>
#include <algorithm>
#include <vector>
 
class number{
    std::vector<int> digits;
    short int sign;
    void normal(){
        while(digits.size() > 1 && digits[digits.size() - 1] == 0) digits.pop_back();
        if (digits.size() == 1 && digits[0] == 0) sign = 1;
    }
    int getDigit(int i) const {
        if (i < 0) return -1000;
        if (i >= digits.size()) return 0;
        return digits[i];
    }
    int getSign() const {return sign;}
public:
    number(){
        digits.push_back(0);
        sign = 1;
    }
    explicit number(std::string s){
        sign = 1;
        if (s == ""){
            digits.push_back(0);
            return;
        }
        if (s == "-0" || s[0] == '+') sign /= 0;
        if (s[0] == '-'){
            sign = -1;
            s.erase(0, 1);
        } else
        if (s[0] == '+'){
            s.erase(0, 1);
        }
        for (int i = 0; i < s.size(); ++i)
            digits.push_back(s[s.size() - i - 1] - '0');
        normal();
    }
    int size() const {return digits.size();}
    int operator<(const number &sec) const {
        if (sign != sec.getSign()){
            return sign < sec.getSign() ? -1 : 1;
        }
        if (digits.size() != sec.size()) {
            return (digits.size() < sec.size() ? -sign : sign);
        }
        for (int i = (int)(digits.size()) - 1; i >= 0; --i) {
            if (digits[i] != sec.getDigit(i)) {
                return (digits[i] < sec.getDigit(i) ? -sign : sign);
            }
        }
        return 0;
    }
    number operator-() const {
        number ans = *this;
        ans.sign = (ans.sign == 1 ? -1 : 1);
        return ans;
    }
    number operator+(const number &sec) const {
        if (sec.sign == -1) {
            return *this - -sec;
        }
        if (sign == -1){
            return sec - -*this;
        }
        int n = std::max(size(), sec.size()) + 1;
        number res;
        for (int i = 0; i < n + 1; ++i){
            res.digits.push_back(0);
            res.digits[i] += getDigit(i) + sec.getDigit(i);
            if (res.digits[i] > 9){
                res.digits[i + 1]++;
                res.digits[i] -= 10;
            }
        }
        res.normal();
        return res;
    }
    number operator-(const number &sec) const {
        if (sec.sign == -1){
            return *this + -sec;
        }
        if (sign == -1){
            return -(sec + -*this);
        }
        if ((*this < sec) == -1) return -(sec - *this);
        int n = std::max(size(), sec.size()) + 1;
        number res;
        for (int i = 0; i < n + 1; ++i) {
            res.digits.push_back(0);
            res.digits[i] += getDigit(i) - sec.getDigit(i);
            if (res.digits[i] < 0) {
                res.digits[i] += 10;
                res.digits[i + 1]--;
            }
        }
        res.normal();
        return res;
    }
    number operator*(const number &sec) const {
        number res;
        res.sign = sec.sign * sign;
        int n = std::max(size(), sec.size()) * 2;
        res.digits.resize(n + 2, 0);
        for (int i = 0; i < size(); ++i)
            for (int j = 0; j < sec.digits.size(); ++j)
                res.digits[i + j] += digits[i] * sec.digits[j];
        for (int i = 0; i < n + 1; ++i){
            res.digits[i + 1] += res.digits[i] / 10;
            res.digits[i] %= 10;
        }
        res.normal();
        return res;
    }
    void operator+=(const number &sec) {
        *this = *this + sec;
    }
    void operator-=(const number &sec) {
        *this = *this - sec;
    }
    void operator*=(const number &sec) {
        *this = *this * sec;
    }
    number operator++() {
        *this += number("1");
        return *this;
    }
    number operator++(int) {
        auto ret = *this;
        *this += number("1");
        return ret;
    }
    number operator--() {
        *this -= number("1");
        return *this;
    }
    number operator--(int) {
        auto ret = *this;
        *this -= number("1");
        return ret;
    }
    friend std::istream& operator>>(std::istream &stream, number &sec) {
        std::string str;
        stream >> str;
        sec = number(str);
        return stream;
    }
    friend std::ostream& operator<<(std::ostream &stream, const number &sec){
        if (sec.sign == -1) stream << '-';
        for (int i = sec.size() - 1; i >= 0; --i)
            stream << sec.digits[i];
        return stream;
    }
};
 
#endif //CPP_PROJECTS_SOLUTION_H