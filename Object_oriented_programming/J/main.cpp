#include <iostream>
#include <memory>
 
#ifdef Estb_probitie
class Data {
public:
  static int clc;
  int stored;
  Data() noexcept(true) {stored = clc; std::cout << "constructor()" << stored << "\n"; clc = clc + 1; }
  Data(Data && elem) noexcept(true) {stored = elem.stored; std::cout << "constructor(TestingData &&)" << stored << "\n"; }
  Data(const Data & elem) noexcept(false) {stored = elem.stored;
 
    std::cout << "constructor(const TestingData &)" << stored << "\n";}
};
int Data::clc = 0;
#endif
 
 
class DataPair {
private:
  std::unique_ptr<Data> first_, second_;
  void swap(DataPair& other) noexcept {
    std::swap(first_, other.first_);
    std::swap(second_, other.second_);
  }
  void prepareSwap(DataPair elem) noexcept {
    swap(elem);
  }
  void strongExcepConstructor(Data * second, Data * first) noexcept {
    first_.reset(first);
    second_.reset(second);
  }
  void strongExcepConstructor(std::unique_ptr <Data> second, std::unique_ptr <Data> first) noexcept {
    std::swap(first, first_);
    std::swap(second, second_);
  }
public:
  const Data& first() const noexcept { return *first_; }
  const Data& second() const noexcept { return *second_; }
 
  explicit DataPair(const Data &first, const Data &second) noexcept(std::is_nothrow_copy_constructible<Data>::value) {
    strongExcepConstructor(new Data(second),
                           new Data(first));
  }
  explicit DataPair(Data &&first, Data &&second) noexcept(std::is_nothrow_move_constructible<Data>::value |
                                                          std::is_nothrow_copy_constructible<Data>::value) {
    strongExcepConstructor(new Data(std::move_if_noexcept(second)),
                           new Data(std::move_if_noexcept(first)));
  }
  explicit DataPair(const Data &first, Data &&second) noexcept(std::is_nothrow_move_constructible<Data>::value &
                                                               std::is_nothrow_copy_constructible<Data>::value) {
    strongExcepConstructor(new Data(std::move(second)),
                           new Data(first));
  }
  explicit DataPair(Data &&first, const Data &second) noexcept(std::is_nothrow_move_constructible<Data>::value &
                                                               std::is_nothrow_copy_constructible<Data>::value) {
    auto ff = new Data(second);
    auto ss = new Data(std::move(first));
 
    strongExcepConstructor(ff, ss);
  }
  DataPair(DataPair && pair) noexcept {
    strongExcepConstructor(std::unique_ptr<Data>(std::move(pair.second_)), std::unique_ptr<Data>(std::move(pair.first_)));
  }
  DataPair(const DataPair &pair) noexcept(std::is_nothrow_copy_constructible<Data>::value) {
    strongExcepConstructor(new Data(*pair.second_),
                           new Data(*pair.first_));
  }
  DataPair& operator=(const DataPair &other) noexcept(std::is_nothrow_copy_constructible<Data>::value) {
    prepareSwap(other);
    return *this;
  }
  DataPair& operator=(DataPair && other) noexcept {
    this->swap(other);
    return *this;
  }
};
