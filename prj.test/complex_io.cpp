#include <complex/complex.hpp>
#include <sstream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>


TEST_CASE("[complex] - stream operators") {
    SUBCASE("operator<< output format") {
        Complex c(3.0, 4.0);
        std::ostringstream oss;
        oss << c;
        CHECK(oss.str() == "{3,4}");
    }

    SUBCASE("operator<< with negative values") {
        Complex c(-2.5, -3.7);
        std::ostringstream oss;
        oss << c;
        CHECK(oss.str() == "{-2.5,-3.7}");
    }

    SUBCASE("operator<< with zero") {
        Complex c(0.0, 0.0);
        std::ostringstream oss;
        oss << c;
        CHECK(oss.str() == "{0,0}");
    }

    SUBCASE("operator<< with mixed signs") {
        Complex c(5.5, -2.3);
        std::ostringstream oss;
        oss << c;
        CHECK(oss.str() == "{5.5,-2.3}");
    }

    SUBCASE("operator>> input valid positive") {
        std::istringstream iss("{5,6}");
        Complex c;
        iss >> c;
        CHECK(iss.good());
        CHECK(c == Complex(5.0, 6.0));
    }

    SUBCASE("operator>> input valid negative") {
        std::istringstream iss("{-2.5,-3.7}");
        Complex c;
        iss >> c;
        CHECK(iss.good());
        CHECK(c.re == -2.5);
        CHECK(c.im == -3.7);
    }

    SUBCASE("operator>> input valid mixed signs") {
        std::istringstream iss("{10,-15.5}");
        Complex c;
        iss >> c;
        CHECK(iss.good());
        CHECK(c == Complex(10.0, -15.5));
    }

    SUBCASE("operator>> input valid with spaces") {
        std::istringstream iss("{ 1 , 2 }");
        Complex c;
        iss >> c;
        CHECK(iss.good());
        CHECK(c == Complex(1.0, 2.0));
    }

    SUBCASE("operator>> input valid with spaces and negatives") {
        std::istringstream iss("{ -5.5 , -8.2 }");
        Complex c;
        iss >> c;
        CHECK(iss.good());
        CHECK(c == Complex(-5.5, -8.2));
    }

    SUBCASE("operator>> input invalid wrong opening bracket") {
        std::istringstream iss("[5,6}");
        Complex c;
        iss >> c;
        CHECK_FALSE(iss.good());
        CHECK(iss.fail());
        CHECK(c == Complex(0.0, 0.0));
    }

    SUBCASE("operator>> input invalid wrong closing bracket") {
        std::istringstream iss("{5,6]");
        Complex c;
        iss >> c;
        CHECK_FALSE(iss.good());
        CHECK(iss.fail());
        CHECK(c == Complex(0.0, 0.0));
    }

    SUBCASE("operator>> input invalid wrong separator") {
        std::istringstream iss("{5;6}");
        Complex c;
        iss >> c;
        CHECK_FALSE(iss.good());
        CHECK(iss.fail());
        CHECK(c == Complex(0.0, 0.0));
    }

    SUBCASE("operator>> input invalid format [x,y]") {
        std::istringstream iss("[1,2]");
        Complex c;
        iss >> c;
        CHECK_FALSE(iss.good());
        CHECK(iss.fail());
    }

    SUBCASE("operator>> input invalid no separators") {
        std::istringstream iss("{56}");
        Complex c;
        iss >> c;
        CHECK_FALSE(iss.good());
    }

    SUBCASE("operator>> input invalid incomplete") {
        std::istringstream iss("{5,");
        Complex c;
        iss >> c;
        CHECK_FALSE(iss.good());
    }

    SUBCASE("operator>> input empty string") {
        std::istringstream iss("");
        Complex c;
        iss >> c;
        CHECK_FALSE(iss.good());
        CHECK(iss.fail());
    }

    SUBCASE("operator>> input non-numeric values") {
        std::istringstream iss("{a,b}");
        Complex c;
        iss >> c;
        CHECK_FALSE(iss.good());
    }

    SUBCASE("operator>> zero values") {
        std::istringstream iss("{0,0}");
        Complex c;
        iss >> c;
        CHECK(iss.good());
        CHECK(c == Complex(0.0, 0.0));
    }

    SUBCASE("operator>> large values") {
        std::istringstream iss("{1000.123,-9999.456}");
        Complex c;
        iss >> c;
        CHECK(iss.good());
        CHECK(c == Complex(1000.123, -9999.456));
    }

    SUBCASE("operator>> chained reading") {
        std::istringstream iss("{1,2} {3,4}");
        Complex c1, c2;
        iss >> c1 >> c2;
        CHECK(iss.good());
        CHECK(c1 == Complex(1.0, 2.0));
        CHECK(c2 == Complex(3.0, 4.0));
    }

    SUBCASE("operator>> reading after error") {
        std::istringstream iss("{1,2} [3,4] {5,6}");
        Complex c1, c2, c3;
        iss >> c1;
        CHECK(iss.good());
        CHECK(c1 == Complex(1.0, 2.0));
        
        iss >> c2;
        CHECK_FALSE(iss.good());
        CHECK(c2 == Complex(0.0, 0.0));
    }

    SUBCASE("round-trip output and input") {
        Complex original(7.5, -3.2);
        std::ostringstream oss;
        oss << original;
        
        std::istringstream iss(oss.str());
        Complex restored;
        iss >> restored;
        
        CHECK(iss.good());
        CHECK(original == restored);
    }
}

TEST_CASE("[complex] - testParse function") {
    SUBCASE("valid parse positive") {
        CHECK(testParse("{1,2}"));
    }

    SUBCASE("valid parse negative") {
        CHECK(testParse("{-2.5,-3.7}"));
    }

    SUBCASE("valid parse with spaces") {
        CHECK(testParse("{ 1 , 2 }"));
    }

    SUBCASE("valid parse mixed signs") {
        CHECK(testParse("{-10,5.5}"));
    }

    SUBCASE("invalid parse wrong bracket") {
        CHECK_FALSE(testParse("[1,2]"));
    }

    SUBCASE("invalid parse wrong separator") {
        CHECK_FALSE(testParse("{1;2}"));
    }

    SUBCASE("invalid parse incomplete") {
        CHECK_FALSE(testParse("{1,"));
    }

    SUBCASE("invalid parse empty") {
        CHECK_FALSE(testParse(""));
    }

    SUBCASE("invalid parse non-numeric") {
        CHECK_FALSE(testParse("{a,b}"));
    }
}
