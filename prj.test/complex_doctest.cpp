#include <complex/complex.hpp>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("[complex] - ctor") {
  CHECK(Complex() == Complex(0.0, 0.0));
  CHECK(Complex(2.0) == Complex(2.0, 0.0));





  SUBCASE("constructor with two parameters") {
    Complex c(3.0, 4.0);
    CHECK(c.real == 3.0);
    CHECK(c.imagin == 4.0);
  }
  
  SUBCASE("constructor with one parameter (real only)") {
    Complex c(5.0);
    CHECK(c.real == 5.0);
    CHECK(c.imagin == 0.0);
  }
  
  SUBCASE("negative values") {
    Complex c(-2.5, -3.7);
    CHECK(c.real == -2.5);
    CHECK(c.imagin == -3.7);
  }
}

// ========== ОПЕРАТОРЫ СРАВНЕНИЯ ==========
TEST_CASE("[complex] - comparison operators") {
  Complex c1(2.0, 3.0);
  Complex c2(2.0, 3.0);
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

// ========== АРИФМЕТИЧЕСКИЕ ОПЕРАТОРЫ (членские) ==========
TEST_CASE("[complex] - arithmetic operators (member)") {
  SUBCASE("operator+") {
    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);
    Complex result = c1 + c2;
    CHECK(result == Complex(4.0, 6.0));
  }
  
  SUBCASE("operator-") {
    Complex c1(5.0, 7.0);
    Complex c2(1.0, 2.0);
    Complex result = c1 - c2;
    CHECK(result == Complex(4.0, 5.0));
  }
  
  SUBCASE("operator* - basic multiplication") {
    Complex c1(2.0, 0.0);
    Complex c2(3.0, 0.0);
    Complex result = c1 * c2;
    CHECK(result == Complex(6.0, 0.0));
  }
  
  SUBCASE("operator* - complex multiplication") {
    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);
    // (1 + 2i)(3 + 4i) = 3 + 4i + 6i + 8i^2 = 3 + 10i - 8 = -5 + 10i
    Complex result = c1 * c2;
    CHECK(result == Complex(-5.0, 10.0));
  }
  
  SUBCASE("operator/ - basic division") {
    Complex c1(6.0, 0.0);
    Complex c2(2.0, 0.0);
    Complex result = c1 / c2;
    CHECK(result == Complex(3.0, 0.0));
  }
  
  SUBCASE("operator/ - complex division") {
    Complex c1(1.0, 0.0);
    Complex c2(0.0, 1.0); // i
    // 1/i = -i
    Complex result = c1 / c2;
    CHECK_EQ(result.real, doctest::Approx(0.0).epsilon(1e-10));
    CHECK_EQ(result.imagin, doctest::Approx(-1.0).epsilon(1e-10));
  }
}

// ========== ОПЕРАТОРЫ += ==========
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

// ========== ОПЕРАТОРЫ -= ==========
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

// ========== ОПЕРАТОРЫ *= ==========
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

// ========== ОПЕРАТОРЫ /= ==========
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

// ========== ГЛОБАЛЬНЫЕ ОПЕРАТОРЫ (число + Complex) ==========
TEST_CASE("[complex] - global operators (number + Complex)") {
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
  }
  
  SUBCASE("double / Complex") {
    Complex c(1.0, 0.0);
    Complex result = 2.0 / c;
    CHECK(result == Complex(2.0, 0.0));
  }
}

// ========== ПОТОКОВЫЕ ОПЕРАТОРЫ ==========
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
  
  SUBCASE("operator>> input invalid format") {
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
    CHECK(c.real == -2.5);
    CHECK(c.imagin == -3.7);
  }
}

// ========== ВСПОМОГАТЕЛЬНАЯ ФУНКЦИЯ ==========
TEST_CASE("[complex] - testParse function") {
  SUBCASE("valid parse") {
    CHECK(testParse("{1,2}"));
  }
  
  SUBCASE("invalid parse") {
    CHECK_FALSE(testParse("[1,2]"));
  }
  
  SUBCASE("valid with spaces") {
    // зависит от поведения operator>>
    CHECK(testParse("{ 1 , 2 }"));
  }
}
