add_executable(complex_test complex_test.cpp)
target_link_libraries(complex_test complex)

add_executable(complex_doctest complex_doctest.cpp)
target_link_libraries(complex_doctest complex)

add_executable(complex_io complex_io.cpp)
target_link_libraries(complex_io complex)

add_executable(rational_test rational_test.cpp)
target_link_libraries(rational_test rational)

add_executable(rational_io rational_io.cpp)
target_link_libraries(rational_io rational)

add_executable(rational_contracts rational_contracts.cpp)
target_link_libraries(rational_contracts rational)

add_executable(dio_test dio_test.cpp)
target_link_libraries(dio_test dio)

