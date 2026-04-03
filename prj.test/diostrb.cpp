#include <diostrb/diostrb.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("Constructors") {
  CHECK(DioStrB() == DioStrB(""));
  SUBCASE("") {
    DioStrB s("hello");
    CHECK(s.val() == "hello");
  }
  SUBCASE("Default constructor") {
    DioStrB s;
    CHECK(s.val() == "");
  }
}

TEST_CASE("[Output operator") {
  DioStrB s("world");
  std::ostringstream oss;
  oss << s;
  CHECK(oss.str() == "world");
}

TEST_CASE("Input operator") {
  DioStrB s;
  std::istringstream iss("hello");
  iss >> s;
  CHECK(s.val() == "hello");
  SUBCASE("Failed read does not change value") {
    DioStrB s2("original");
    std::istringstream empty("");
    empty >> s2;
    CHECK(s2.val() == "original");
  }
}

TEST_CASE("val() method") {
  CHECK(DioStrB("test").val() == "test");
  CHECK(DioStrB("").val() == "");
  CHECK(DioStrB("hello world").val() == "hello world");
}
