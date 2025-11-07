#include <iostream>
#include <sstream>
#include <prj.lab/complex/complex.hpp>

int main()
{
    Complex z;
    z += Complex(8.0);
    testParse("{8.9,9}");
    testParse("{8.9, 9}");
    testParse("{8.9,9");
    return 0;
}
