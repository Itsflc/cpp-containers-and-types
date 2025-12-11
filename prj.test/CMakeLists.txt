add_executable(complex_test complex_test.cpp)
target_link_libraries(complex_test complex)

add_executable(complex_doctest complex_doctest.cpp)
target_link_libraries(complex_doctest complex)

add_executable(complex_io complex_io.cpp)
target_link_libraries(complex_io complex)

add_executable(rational_doctest rational_doctest.cpp)
target_link_libraries(rational_doctest rational)


