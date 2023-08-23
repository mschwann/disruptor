set(BINARY stack_bench)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

add_executable(${BINARY} ${TEST_SOURCES})
target_link_libraries(${BINARY} PUBLIC circularbuffer benchmark)
target_include_directories(${BINARY} PUBLIC ${CMAKE_BINARY_DIR}/include/)