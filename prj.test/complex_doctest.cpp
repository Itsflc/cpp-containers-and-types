#include <complex/complex.hpp>
#include <sstream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("[complex] - Constructors") {
  CHECK(Complex() == Complex(0.0, 0.0));
  CHECK(Complex(2.0) == Complex(2.0, 0.0));

  SUBCASE("Constructors with two parameters") {
    Complex c(3.7, -4.1);
    CHECK(c.re == 3.7);
    CHECK(c.im == -4.1);
  }
  
  SUBCASE("Negative values") {
    Complex c(-2.5, -3.7);
    CHECK(c.re == -2.5);
    CHECK(c.im == -3.7);
  }
}

TEST_CASE("[complex] - Comparison operators") {
  Complex c1(12.0, 3.0);
  Complex c2(12.0, 3.0);
  Complex c3(1.0, 1.0);
  
  SUBCASE("operator==") {
    CHECK(c1 == c2);
    CHECK_FALSE(c1 == c3);
  }
  
  SUBCASE("operator!=") {
    CHECK(c1 != c3);
    CHECK_FALSE(c1 != c2);
  }
}

TEST_CASE("[complex] - Arithmetic operators (Complex)") {
  SUBCASE("operator+") {
    Complex c1(1.5, -2.0);
    Complex c2(3.0, 4.0);
    Complex result = c1 + c2;
    CHECK(result == Complex(4.5, 2.0));
  }
  
  SUBCASE("operator-") {
    Complex c1(5.0, 7.0);
    Complex c2(1.0, 2.0);
    Complex result = c1 - c2;
    CHECK(result == Complex(4.0, 5.0));
  }
  
  SUBCASE("operator* basic") {
    Complex c1(2.0, 0.0);
    Complex c2(3.0, 0.0);
    Complex result = c1 * c2;
    CHECK(result == Complex(6.0, 0.0));
  }
  
  SUBCASE("operator* complex") {
    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);
    Complex result = c1 * c2;
    CHECK(result == Complex(-5.0, 10.0));
  }
  
  SUBCASE("operator/ basic") {
    Complex c1(6.0, 0.0);
    Complex c2(2.0, 0.0);
    Complex result = c1 / c2;
    CHECK(result == Complex(3.0, 0.0));
  }
  
  SUBCASE("operator/ complex") {
    Complex c1(10.0, 0.0);
    Complex c2(0.0, 5.0);
    Complex result = c1 / c2;
    CHECK_EQ(result.re, doctest::Approx(0.0).epsilon(1e-10));
    CHECK_EQ(result.im, doctest::Approx(-2.0).epsilon(1e-10));
  }
}

TEST_CASE("[complex] - operator+=") {
  SUBCASE("operator+= with Complex") {
    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);
    c1 += c2;
    CHECK(c1 == Complex(4.0, 6.0));
  }
  
  SUBCASE("operator+= with double") {
    Complex c(2.0, 3.0);
    c += 5.0;
    CHECK(c == Complex(7.0, 3.0));
  }
  
  SUBCASE("operator+= chain") {
    Complex c(1.0, 1.0);
    c += 2.0;
    c += Complex(1.0, 1.0);
    CHECK(c == Complex(4.0, 2.0));
  }
}

TEST_CASE("[complex] - operator-=") {
  SUBCASE("operator-= with Complex") {
    Complex c1(5.0, 7.0);
    Complex c2(1.0, 2.0);
    c1 -= c2;
    CHECK(c1 == Complex(4.0, 5.0));
  }
  
  SUBCASE("operator-= with double") {
    Complex c(10.0, 3.0);
    c -= 4.0;
    CHECK(c == Complex(6.0, 3.0));
  }
  
  SUBCASE("operator-= chain") {
    Complex c(10.0, 10.0);
    c -= 2.0;
    c -= Complex(1.0, 1.0);
    CHECK(c == Complex(7.0, 9.0));
  }
}

TEST_CASE("[complex] - operator*=") {
  SUBCASE("operator*= with Complex") {
    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);
    c1 *= c2;
    CHECK(c1 == Complex(-5.0, 10.0));
  }
  
  SUBCASE("operator*= with double") {
    Complex c(2.0, 3.0);
    c *= 2.0;
    CHECK(c == Complex(4.0, 6.0));
  }
  
  SUBCASE("operator*= chain") {
    Complex c(1.0, 1.0);
    c *= 2.0;
    c *= Complex(1.0, 0.0);
    CHECK(c == Complex(2.0, 2.0));
  }
}

TEST_CASE("[complex] - operator/=") {
  SUBCASE("operator/= with Complex") {
    Complex c1(6.0, 0.0);
    Complex c2(2.0, 0.0);
    c1 /= c2;
    CHECK(c1 == Complex(3.0, 0.0));
  }
  
  SUBCASE("operator/= with double") {
    Complex c(10.0, 4.0);
    c /= 2.0;
    CHECK(c == Complex(5.0, 2.0));
  }
}

TEST_CASE("[complex] - global operators") {
  SUBCASE("double + Complex") {
    Complex c(2.0, 3.0);
    Complex result = 5.0 + c;
    CHECK(result == Complex(7.0, 3.0));
  }
  
  SUBCASE("double - Complex") {
    Complex c(1.0, 2.0);
    Complex result = 10.0 - c;
    CHECK(result == Complex(9.0, -2.0));
  }
  
  SUBCASE("double * Complex") {
    Complex c(2.0, 3.0);
    Complex result = 3.0 * c;
    CHECK(result == Complex(6.0, 9.0));
    Complex g(2.0, 3.0);
    Complex result2 = -g;
    CHECK(result2 == Complex(-2.0, -3.0));
  }
  
  SUBCASE("double / Complex") {
    Complex c(1.0, 0.0);
    Complex result = 2.0 / c;
    CHECK(result == Complex(2.0, 0.0));
  }
}

TEST_CASE("[complex] - stream operators") {
  SUBCASE("operator<< output") {
    Complex c(3.0, 4.0);
    std::ostringstream oss;
    oss << c;
    CHECK(oss.str() == "{3,4}");
  }
  
  SUBCASE("operator>> input valid") {
    std::istringstream iss("{5,6}");
    Complex c;
    iss >> c;
    CHECK(iss.good());
    CHECK(c == Complex(5.0, 6.0));
  }
  
  SUBCASE("operator>> input invalid") {
    std::istringstream iss("[5,6]");
    Complex c;
    iss >> c;
    CHECK_FALSE(iss.good());
  }
  
  SUBCASE("operator>> negative values") {
    std::istringstream iss("{-2.5,-3.7}");
    Complex c;
    iss >> c;
    CHECK(iss.good());
    CHECK(c.re == -2.5);
    CHECK(c.im == -3.7);
  }
}

TEST_CASE("[complex] - testParse function") {
  SUBCASE("valid parse") {
    CHECK(testParse("{1,2}"));
  }
  
  SUBCASE("invalid parse") {
    CHECK_FALSE(testParse("[1,2]"));
  }
  
  SUBCASE("valid with spaces") {
    CHECK(testParse("{ 1 , 2 }"));
  }
}
