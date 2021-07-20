#include <iostream>
#include "result.h"

void print_result(Result r) {
  if (r == Result::Failure)
    std::cout << "Failure\n"; else
  if (r== Result::Invalid)
    std::cout << "Invalid\n"; else
    std::cout << "Success\n";
}