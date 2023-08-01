setup_component()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  
# Make an automatic library - will be static or dynamic based on user setting
add_library(circularbuffer 1p1c_circularbuffer.cpp)

# We need this directory, and users of our library will need it too
target_include_directories(circularbuffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# This depends on (header only) boost
#target_link_libraries(circularbuffer PRIVATE Boost::boost)

# All users of this library will need at least C++20
target_compile_features(circularbuffer PUBLIC cxx_std_20)

add_subdirectory(tests)