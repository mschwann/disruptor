set(BINARY linkedlist_tst)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})
message(${CMAKE_BINARY_DIR}/include/)
target_include_directories(${BINARY} PUBLIC ${CMAKE_BINARY_DIR}/include/)
target_link_libraries(${BINARY} PUBLIC circularbuffer gtest)