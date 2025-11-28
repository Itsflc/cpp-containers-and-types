#include <complex/complex.hpp>
#include <iostream>

void check_contracts() {
  try {
    std::cout << "try divide to zero -> ";
    Complex z;
    z /= 0;
    std::cout << "nothing happened (trouble)";
  }
  catch (const std::invalid_argument& ex) {
    std::cout << "exception caught, message - " << ex.what();
  }
}

int main() {
  Complex z0;
  check_contracts();
}
