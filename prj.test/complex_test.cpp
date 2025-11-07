#include <complex/complex.hpp>
#include <iostream>
#include <sstream>


int main()
{
    Complex z;
    z += Complex(8.0);
    testParse("{8.9,9}");
    testParse("{8.9, 9}");
    testParse("{8.9,9");
    return 0;
}
