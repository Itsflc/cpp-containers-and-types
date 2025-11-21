#include <rational/rational.hpp>
#include <sstream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("[rational] - constructors") {
  SUBCASE("default constructor") {
    CHECK(Rational() == Rational(0));
    CHECK(Rational() == Rational(0, 1));
    CHECK(Rational() == Rational(0, 5));
  }
  
  SUBCASE("constructor with numerator only") {
    Rational r(5);
    CHECK(r.num() == 5);
    CHECK(r.den() == 1);
  }
  
  SUBCASE("constructor with numerator and denominator") {
    Rational r(3, 4);
    CHECK(r.num() == 3);
    CHECK(r.den() == 4);
  }
  
  SUBCASE("normalization positive") {
    Rational r(6, 8);
    CHECK(r.num() == 3);
    CHECK(r.den() == 4);
  }
  
  SUBCASE("normalization negative denominator") {
    Rational r(3, -6);
    CHECK(r.num() == -1);
    CHECK(r.den() == 2);
  }
  
  SUBCASE("division by zero throws exception") {
    CHECK_THROWS_AS(Rational(7, 0), std::invalid_argument);
  }
}

TEST_CASE("[rational] - getters") {
  Rational r(7, 9);
  
  SUBCASE("num() method") {
    CHECK(r.num() == 7);
  }
  
  SUBCASE("den() method") {
    CHECK(r.den() == 9);
  }
}

TEST_CASE("[rational] - comparison operators") {
  Rational r1(1, 2);
  Rational r2(1, 2);
  Rational r3(1, 3);
  Rational r4(3, 4);
  
  SUBCASE("operator==") {
    CHECK(r1 == r2);
    CHECK_FALSE(r1 == r3);
    CHECK(Rational(2, 4) == Rational(1, 2));
  }
  
  SUBCASE("operator!=") {
    CHECK(r1 != r3);
    CHECK_FALSE(r1 != r2);
  }
  
  SUBCASE("operator>") {
    CHECK(r4 > r1);
    CHECK(r1 > r3);
    CHECK_FALSE(r1 > r2);
  }
  
  SUBCASE("operator<") {
    CHECK(r3 < r1);
    CHECK(r1 < r4);
    CHECK_FALSE(r1 < r2);
  }
  
  SUBCASE("operator>=") {
    CHECK(r4 >= r1);
    CHECK(r1 >= r2);
    CHECK(r1 >= r3);
    CHECK_FALSE(r3 >= r1);
  }
  
  SUBCASE("operator<=") {
    CHECK(r3 <= r1);
    CHECK(r1 <= r2);
    CHECK(r1 <= r4);
    CHECK_FALSE(r4 <= r1);
  }
}

TEST_CASE("[rational] - unary minus operator") {
  SUBCASE("operator- positive") {
    Rational r(3, 4);
    Rational result = -r;
    CHECK(result == Rational(-3, 4));
  }
  
  SUBCASE("operator- negative") {
    Rational r(-2, 5);
    Rational result = -r;
    CHECK(result == Rational(2, 5));
  }
  
  SUBCASE("operator- zero") {
    Rational r(0, 1);
    Rational result = -r;
    CHECK(result == Rational(0, 1));
  }
}

TEST_CASE("[rational] - arithmetic operators (member)") {
  SUBCASE("operator+ basic") {
    Rational r1(1, 2);
    Rational r2(1, 3);
    Rational result = r1 + r2;
    CHECK(result == Rational(5, 6));
  }
  
  SUBCASE("operator+ with negative") {
    Rational r1(3, 4);
    Rational r2(-1, 4);
    Rational result = r1 + r2;
    CHECK(result == Rational(1, 2));
  }
  
  SUBCASE("operator- basic") {
    Rational r1(3, 4);
    Rational r2(1, 4);
    Rational result = r1 - r2;
    CHECK(result == Rational(1, 2));
  }
  
  SUBCASE("operator- negative result") {
    Rational r1(1, 4);
    Rational r2(3, 4);
    Rational result = r1 - r2;
    CHECK(result == Rational(-1, 2));
  }
  
  SUBCASE("operator* basic") {
    Rational r1(2, 3);
    Rational r2(3, 4);
    Rational result = r1 * r2;
    CHECK(result == Rational(1, 2));
  }
  
  SUBCASE("operator* by zero") {
    Rational r1(5, 7);
    Rational r2(0, 1);
    Rational result = r1 * r2;
    CHECK(result == Rational(0, 1));
  }
  
  SUBCASE("operator/ basic") {
    Rational r1(1, 2);
    Rational r2(1, 3);
    Rational result = r1 / r2;
    CHECK(result == Rational(3, 2));
  }
  
  SUBCASE("operator/ by zero throws") {
    Rational r1(5, 7);
    Rational r2(0, 1);
    CHECK_THROWS_AS(r1 / r2, std::invalid_argument);
  }
}

TEST_CASE("[rational] - compound assignment operators") {
  SUBCASE("operator+=") {
    Rational r1(1, 2);
    Rational r2(1, 3);
    r1 += r2;
    CHECK(r1 == Rational(5, 6));
  }
  
  SUBCASE("operator-=") {
    Rational r1(3, 4);
    Rational r2(1, 4);
    r1 -= r2;
    CHECK(r1 == Rational(1, 2));
  }
  
  SUBCASE("operator*=") {
    Rational r1(2, 3);
    Rational r2(3, 4);
    r1 *= r2;
    CHECK(r1 == Rational(1, 2));
  }
  
  SUBCASE("operator/=") {
    Rational r1(1, 2);
    Rational r2(1, 3);
    r1 /= r2;
    CHECK(r1 == Rational(3, 2));
  }
  
  SUBCASE("operator/= by zero throws") {
    Rational r1(5, 7);
    Rational r2(0, 1);
    CHECK_THROWS_AS(r1 /= r2, std::invalid_argument);
  }
}

TEST_CASE("[rational] - global operators (int + Rational)") {
  SUBCASE("int + Rational") {
    Rational r(1, 2);
    Rational result = 2 + r;
    CHECK(result == Rational(5, 2));
  }
  
  SUBCASE("int - Rational") {
    Rational r(1, 4);
    Rational result = 1 - r;
    CHECK(result == Rational(3, 4));
  }
  
  SUBCASE("int * Rational") {
    Rational r(2, 3);
    Rational result = 3 * r;
    CHECK(result == Rational(2, 1));
  }
  
  SUBCASE("int / Rational") {
    Rational r(2, 3);
    Rational result = 2 / r;
    CHECK(result == Rational(3, 1));
  }
}

TEST_CASE("[rational] - stream operators") {
  SUBCASE("operator<< output") {
    Rational r(3, 4);
    std::ostringstream oss;
    oss << r;
    CHECK(oss.str() == "3/4");
  }
  
  SUBCASE("operator<< negative") {
    Rational r(-5, 7);
    std::ostringstream oss;
    oss << r;
    CHECK(oss.str() == "-5/7");
  }
  
  SUBCASE("operator>> input valid") {
    std::istringstream iss("5/6");
    Rational r;
    iss >> r;
    CHECK(iss.good());
    CHECK(r == Rational(5, 6));
  }
  
  SUBCASE("operator>> input invalid format") {
    std::istringstream iss("5-6");
    Rational r;
    iss >> r;
    CHECK_FALSE(iss.good());
  }
  
  SUBCASE("operator>> negative values") {
    std::istringstream iss("-3/8");
    Rational r;
    iss >> r;
    CHECK(iss.good());
    CHECK(r == Rational(-3, 8));
  }
}

TEST_CASE("[rational] - testParse function") {
  SUBCASE("valid parse") {
    CHECK(testParse("1/2"));
  }
  
  SUBCASE("valid parse negative") {
    CHECK(testParse("-3/4"));
  }
  
  SUBCASE("invalid parse") {
    CHECK_FALSE(testParse("1-2"));
  }
}

TEST_CASE("[rational] - chain operations") {
  SUBCASE("chain addition") {
    Rational r1(1, 2);
    Rational r2(1, 3);
    Rational r3(1, 6);
    Rational result = r1 + r2 + r3;
    CHECK(result == Rational(1, 1));
  }
  
  SUBCASE("chain multiplication and division") {
    Rational r1(2, 3);
    Rational r2(3, 4);
    Rational r3(8, 9);
    Rational result = r1 * r2 / r3;
    CHECK(result == Rational(1, 1));
  }
  
  SUBCASE("mixed operations") {
    Rational r1(1, 2);
    Rational r2(1, 3);
    Rational r3(1, 6);
    Rational result = r1 + r2 - r3;
    CHECK(result == Rational(2, 3));
  }
}

TEST_CASE("[rational] - edge cases") {
  SUBCASE("whole numbers") {
    Rational r(10, 1);
    CHECK(r.num() == 10);
    CHECK(r.den() == 1);
  }
  
  SUBCASE("zero") {
    Rational r(0, 5);
    CHECK(r.num() == 0);
    CHECK(r.den() == 1);
  }
  
  SUBCASE("one") {
    Rational r(5, 5);
    CHECK(r.num() == 1);
    CHECK(r.den() == 1);
  }
  
  SUBCASE("large numbers") {
    Rational r(1000, 2000);
    CHECK(r.num() == 1);
    CHECK(r.den() == 2);
  }
}
