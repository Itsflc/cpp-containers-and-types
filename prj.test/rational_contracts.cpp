#include <rational/rational.hpp>
#include <sstream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>


TEST_CASE("[rational] - constructor contracts") {
    SUBCASE("default constructor creates 0/1") {
        Rational r;
        CHECK(r.num() == 0);
        CHECK(r.den() == 1);
    }

    SUBCASE("single argument creates n/1") {
        Rational r(5);
        CHECK(r.num() == 5);
        CHECK(r.den() == 1);
    }

    SUBCASE("denominator zero throws exception") {
        CHECK_THROWS_AS(Rational(3, 0), std::invalid_argument);
    }

    SUBCASE("constructor normalizes fraction") {
        Rational r(10, 15);
        CHECK(r.num() == 2);
        CHECK(r.den() == 3);
    }
}

TEST_CASE("[rational] - invariant: denominator always positive") {
    SUBCASE("negative denominator moved to numerator") {
        Rational r(3, -4);
        CHECK(r.den() > 0);
        CHECK(r.num() == -3);
        CHECK(r.den() == 4);
    }

    SUBCASE("both negative normalized to positive fraction") {
        Rational r(-6, -8);
        CHECK(r.den() > 0);
        CHECK(r.num() == 3);
        CHECK(r.den() == 4);
    }
}

TEST_CASE("[rational] - invariant: fraction is always reduced") {
    SUBCASE("GCD is 1 after construction") {
        Rational r(12, 18);
        CHECK(r.num() == 2);
        CHECK(r.den() == 3);
        // GCD(2, 3) = 1
    }

    SUBCASE("already reduced fraction unchanged") {
        Rational r(7, 11);
        CHECK(r.num() == 7);
        CHECK(r.den() == 11);
    }

    SUBCASE("zero numerator reduces to 0/1") {
        Rational r(0, 5);
        CHECK(r.num() == 0);
        CHECK(r.den() == 1);
    }
}

TEST_CASE("[rational] - arithmetic operation contracts") {
    SUBCASE("addition maintains normalized form") {
        Rational r1(1, 2);
        Rational r2(1, 3);
        Rational result = r1 + r2;
        CHECK(result.den() > 0);
        // Result should be 5/6
        CHECK(result == Rational(5, 6));
    }

    SUBCASE("multiplication maintains normalized form") {
        Rational r1(2, 3);
        Rational r2(3, 4);
        Rational result = r1 * r2;
        CHECK(result.den() > 0);
        // Result should be 1/2 (6/12 normalized)
        CHECK(result == Rational(1, 2));
    }

    SUBCASE("division by zero throws exception") {
        Rational r1(5, 7);
        Rational r2(0, 1);
        CHECK_THROWS_AS(r1 / r2, std::invalid_argument);
    }

    SUBCASE("division creates normalized fraction") {
        Rational r1(2, 3);
        Rational r2(4, 9);
        Rational result = r1 / r2;
        CHECK(result == Rational(3, 2));  // (2/3) / (4/9) = 3/2
    }
}

TEST_CASE("[rational] - compound assignment contracts") {
    SUBCASE("operator+= returns reference to self") {
        Rational r1(1, 2);
        Rational r2(1, 3);
        Rational& ref = (r1 += r2);
        CHECK(&ref == &r1);
        CHECK(r1 == Rational(5, 6));
    }

    SUBCASE("operator-= normalizes result") {
        Rational r1(3, 4);
        r1 -= Rational(1, 4);
        CHECK(r1.den() > 0);
        CHECK(r1 == Rational(1, 2));
    }

    SUBCASE("operator*= normalizes result") {
        Rational r(2, 3);
        r *= Rational(3, 4);
        CHECK(r == Rational(1, 2));  // Normalized from 6/12
    }

    SUBCASE("operator/= by zero throws") {
        Rational r(1, 2);
        CHECK_THROWS_AS(r /= Rational(0, 1), std::invalid_argument);
    }
}

TEST_CASE("[rational] - comparison contract: equality") {
    SUBCASE("equal fractions are equal (different representations)") {
        CHECK(Rational(2, 4) == Rational(1, 2));
    }

    SUBCASE("different fractions are not equal") {
        CHECK_FALSE(Rational(1, 2) == Rational(1, 3));
    }

    SUBCASE("equality is reflexive") {
        Rational r(3, 7);
        CHECK(r == r);
    }

    SUBCASE("inequality operator works") {
        CHECK(Rational(1, 2) != Rational(1, 3));
        CHECK_FALSE(Rational(2, 4) != Rational(1, 2));
    }
}

TEST_CASE("[rational] - comparison contract: ordering") {
    SUBCASE("ordering is consistent") {
        Rational r1(1, 3);
        Rational r2(1, 2);
        Rational r3(2, 3);
        
        CHECK(r1 < r2);
        CHECK(r2 < r3);
        CHECK(r1 < r3);  // Transitive
    }

    SUBCASE("operator< and operator> are inverses") {
        Rational r1(1, 2);
        Rational r2(2, 3);
        
        CHECK(r1 < r2);
        CHECK_FALSE(r2 < r1);
        CHECK(r2 > r1);
    }

    SUBCASE("operator<= includes equality") {
        Rational r1(1, 2);
        Rational r2(2, 4);
        
        CHECK(r1 <= r2);
        CHECK(r1 >= r2);
    }
}

TEST_CASE("[rational] - unary minus contract") {
    SUBCASE("double negation returns equal value") {
        Rational r(3, 4);
        Rational result = -(-r);
        CHECK(result == r);
    }

    SUBCASE("negation of zero is zero") {
        Rational r(0, 1);
        CHECK(-r == Rational(0, 1));
    }

    SUBCASE("negation flips sign") {
        Rational r(3, 4);
        CHECK((-r).num() < 0);
        CHECK((-r).den() > 0);
    }
}

TEST_CASE("[rational] - stream operators contract") {
    SUBCASE("output format is correct") {
        std::ostringstream oss;
        oss << Rational(3, 4);
        CHECK(oss.str() == "3/4");
    }

    SUBCASE("input and output are inverse operations") {
        Rational original(7, 9);
        std::ostringstream oss;
        oss << original;
        
        std::istringstream iss(oss.str());
        Rational restored;
        iss >> restored;
        
        CHECK(!iss.fail());
        CHECK(original == restored);
    }

    SUBCASE("invalid input sets failbit") {
        std::istringstream iss("invalid");
        Rational r;
        iss >> r;
        CHECK(iss.fail());
    }
}
