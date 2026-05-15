#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "ArrayT.hpp"

TEST_CASE("Default constructor creates array of size 1") {
    ArrayT<int> arr;
    CHECK(arr.size() == 1);
}

TEST_CASE("Constructor with size") {
    ArrayT<int> arr(5);
    CHECK(arr.size() == 5);
}

TEST_CASE("Constructor with negative size throws") {
    CHECK_THROWS_AS(ArrayT<int>(-1), std::invalid_argument);
}

TEST_CASE("Operator[] read and write") {
    ArrayT<int> arr(3);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    CHECK(arr[0] == 10);
    CHECK(arr[1] == 20);
    CHECK(arr[2] == 30);
}

TEST_CASE("Operator[] out of range throws") {
    ArrayT<int> arr(3);
    CHECK_THROWS_AS(arr[-1], std::invalid_argument);
    CHECK_THROWS_AS(arr[3], std::invalid_argument);
}

TEST_CASE("Const operator[] works correctly") {
    ArrayT<int> arr(2);
    arr[0] = 42;
    const ArrayT<int>& ref = arr;
    CHECK(ref[0] == 42);
    CHECK_THROWS_AS(ref[5], std::invalid_argument);
}

TEST_CASE("Copy constructor") {
    ArrayT<int> arr(3);
    arr[0] = 1; arr[1] = 2; arr[2] = 3;
    ArrayT<int> copy(arr);
    CHECK(copy.size() == 3);
    CHECK(copy[0] == 1);
    CHECK(copy[1] == 2);
    CHECK(copy[2] == 3);
}

TEST_CASE("Copy constructor deep copy") {
    ArrayT<int> arr(2);
    arr[0] = 5;
    ArrayT<int> copy(arr);
    copy[0] = 99;
    CHECK(arr[0] == 5);
}

TEST_CASE("Assignment operator") {
    ArrayT<int> arr(3);
    arr[0] = 7; arr[1] = 8; arr[2] = 9;
    ArrayT<int> other(1);
    other = arr;
    CHECK(other.size() == 3);
    CHECK(other[0] == 7);
}

TEST_CASE("Self-assignment") {
    ArrayT<int> arr(2);
    arr[0] = 3;
    arr = arr;
    CHECK(arr.size() == 2);
    CHECK(arr[0] == 3);
}

TEST_CASE("Resize to smaller size") {
    ArrayT<int> arr(5);
    arr.resize(2);
    CHECK(arr.size() == 2);
}

TEST_CASE("Resize to larger size within capacity") {
    ArrayT<int> arr(2);
    arr.resize(4);
    CHECK(arr.size() == 4);
    CHECK(arr[3] == 0);
}

TEST_CASE("Resize beyond capacity") {
    ArrayT<int> arr(2);
    arr.resize(100);
    CHECK(arr.size() == 100);
    CHECK(arr[99] == 0);
}

TEST_CASE("Resize to negative throws") {
    ArrayT<int> arr(3);
    CHECK_THROWS_AS(arr.resize(-1), std::invalid_argument);
}

TEST_CASE("Insert at beginning") {
    ArrayT<int> arr(3);
    arr[0] = 1; arr[1] = 2; arr[2] = 3;
    arr.insert(0, 99);
    CHECK(arr.size() == 4);
    CHECK(arr[0] == 99);
    CHECK(arr[1] == 1);
}

TEST_CASE("Insert at end") {
    ArrayT<int> arr(3);
    arr[0] = 1; arr[1] = 2; arr[2] = 3;
    arr.insert(3, 99);
    CHECK(arr.size() == 4);
    CHECK(arr[3] == 99);
}

TEST_CASE("Insert out of range throws") {
    ArrayT<int> arr(3);
    CHECK_THROWS_AS(arr.insert(-1, 5), std::invalid_argument);
    CHECK_THROWS_AS(arr.insert(4, 5), std::invalid_argument);
}

TEST_CASE("Remove from beginning") {
    ArrayT<int> arr(3);
    arr[0] = 1; arr[1] = 2; arr[2] = 3;
    arr.remove(0);
    CHECK(arr.size() == 2);
    CHECK(arr[0] == 2);
    CHECK(arr[1] == 3);
}

TEST_CASE("Remove from end") {
    ArrayT<int> arr(3);
    arr[0] = 1; arr[1] = 2; arr[2] = 3;
    arr.remove(2);
    CHECK(arr.size() == 2);
    CHECK(arr[1] == 2);
}

TEST_CASE("Remove out of range throws") {
    ArrayT<int> arr(3);
    CHECK_THROWS_AS(arr.remove(-1), std::invalid_argument);
    CHECK_THROWS_AS(arr.remove(3), std::invalid_argument);
}

TEST_CASE("Works with double type") {
    ArrayT<double> arr(2);
    arr[0] = 1.507;
    arr[1] = 2.5236;
    CHECK(arr[0] == doctest::Approx(1.507));
    CHECK(arr[1] == doctest::Approx(2.5236));
}
