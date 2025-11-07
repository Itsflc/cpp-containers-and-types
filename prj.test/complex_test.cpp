#include <iostream>
#include <sstream>
#include "complex.hpp"

int main()
{
    Complex z;
    z += Complex(8.0);
    testParse("{8.9,9}");
    testParse("{8.9, 9}");
    testParse("{8.9,9");
    return 0;
}
