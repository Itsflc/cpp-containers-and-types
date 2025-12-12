#include <rational/rational.hpp>
#include <sstream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

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

    SUBCASE("operator<< zero") {
        Rational r(0, 1);
        std::ostringstream oss;
        oss << r;
        CHECK(oss.str() == "0/1");
    }

    SUBCASE("operator<< whole number") {
        Rational r(5, 1);
        std::ostringstream oss;
        oss << r;
        CHECK(oss.str() == "5/1");
    }

    SUBCASE("operator>> input valid") {
        std::istringstream iss("5/6");
        Rational r;
        iss >> r;
        CHECK(!iss.fail());
        CHECK(r == Rational(5, 6));
    }

    SUBCASE("operator>> input valid positive") {
        std::istringstream iss("3/7");
        Rational r;
        iss >> r;
        CHECK(!iss.fail());
        CHECK(r == Rational(3, 7));
    }

    SUBCASE("operator>> input invalid format dash") {
        std::istringstream iss("5-6");
        Rational r;
        iss >> r;
        CHECK(iss.fail());
        CHECK(r == Rational(5, 6));
    }

    SUBCASE("operator>> input invalid format colon") {
        std::istringstream iss("5:6");
        Rational r;
        iss >> r;
        CHECK(iss.fail());
    }

    SUBCASE("operator>> negative values") {
        std::istringstream iss("-3/8");
        Rational r;
        iss >> r;
        CHECK(!iss.fail());
        CHECK(r == Rational(-3, 8));
    }

    SUBCASE("operator>> both negative") {
        std::istringstream iss("-4/-5");
        Rational r;
        iss >> r;
        CHECK(!iss.fail());
        CHECK(r == Rational(4, 5));  // Both negative normalized to positive
    }

    SUBCASE("operator>> denominator negative") {
        std::istringstream iss("3/-4");
        Rational r;
        iss >> r;
        CHECK(!iss.fail());
        CHECK(r == Rational(-3, 4));  // Sign moved to numerator
    }

    SUBCASE("operator>> denominator zero") {
        std::istringstream iss("5/0");
        Rational r;
        iss >> r;
        CHECK(iss.fail());
    }

    SUBCASE("operator>> no separator") {
        std::istringstream iss("56");
        Rational r;
        iss >> r;
        CHECK(iss.fail());
    }

    SUBCASE("operator>> incomplete") {
        std::istringstream iss("5/");
        Rational r;
        iss >> r;
        CHECK(iss.fail());
    }

    SUBCASE("operator>> empty string") {
        std::istringstream iss("");
        Rational r;
        iss >> r;
        CHECK(iss.fail());
    }

    SUBCASE("operator>> non-numeric") {
        std::istringstream iss("a/b");
        Rational r;
        iss >> r;
        CHECK(iss.fail());
    }

    SUBCASE("operator>> with spaces") {
        std::istringstream iss(" 1 / 2 ");
        Rational r;
        iss >> r;
        CHECK(!iss.fail());
        CHECK(r == Rational(1, 2));
    }

    SUBCASE("operator>> chained reading") {
        std::istringstream iss("1/2 3/4");
        Rational r1, r2;
        iss >> r1 >> r2;
        CHECK(!iss.fail());
        CHECK(r1 == Rational(1, 2));
        CHECK(r2 == Rational(3, 4));
    }

    SUBCASE("operator>> zero numerator") {
        std::istringstream iss("0/5");
        Rational r;
        iss >> r;
        CHECK(!iss.fail());
        CHECK(r == Rational(0, 1));
    }

    SUBCASE("operator>> needs normalization") {
        std::istringstream iss("6/8");
        Rational r;
        iss >> r;
        CHECK(!iss.fail());
        CHECK(r == Rational(3, 4));
    }

    SUBCASE("round-trip output and input") {
        Rational original(7, 9);
        std::ostringstream oss;
        oss << original;
        
        std::istringstream iss(oss.str());
        Rational restored;
        iss >> restored;
        
        CHECK(!iss.fail());
        CHECK(original == restored);
    }

    SUBCASE("round-trip negative output and input") {
        Rational original(-5, 8);
        std::ostringstream oss;
        oss << original;
        
        std::istringstream iss(oss.str());
        Rational restored;
        iss >> restored;
        
        CHECK(!iss.fail());
        CHECK(original == restored);
    }
}

TEST_CASE("[rational] - testParse function") {
    SUBCASE("valid parse positive") {
        CHECK(testParse("1/2"));
    }

    SUBCASE("valid parse negative") {
        CHECK(testParse("-3/4"));
    }

    SUBCASE("valid parse both negative") {
        CHECK(testParse("-2/-3"));
    }

    SUBCASE("valid parse with spaces") {
        CHECK(testParse(" 5 / 6 "));
    }

    SUBCASE("invalid parse dash separator") {
        CHECK_FALSE(testParse("1-2"));
    }

    SUBCASE("invalid parse colon separator") {
        CHECK_FALSE(testParse("1:2"));
    }

    SUBCASE("invalid parse no separator") {
        CHECK_FALSE(testParse("12"));
    }

    SUBCASE("invalid parse incomplete") {
        CHECK_FALSE(testParse("1/"));
    }

    SUBCASE("invalid parse empty") {
        CHECK_FALSE(testParse(""));
    }

    SUBCASE("invalid parse non-numeric") {
        CHECK_FALSE(testParse("a/b"));
    }

    SUBCASE("invalid parse denominator zero") {
        CHECK_FALSE(testParse("5/0"));
    }
}
