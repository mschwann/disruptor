setup_component()

# Make an automatic library - will be static or dynamic based on user setting
add_library(modern_library lib.cpp)

# We need this directory, and users of our library will need it too
target_include_directories(modern_library PUBLIC ${INCLUDE_DIRECTORY_SRC} ${INCLUDE_DIRECTORY_DST})

# This depends on (header only) boost
target_link_libraries(modern_library PRIVATE Boost::boost)

# All users of this library will need at least C++11
target_compile_features(modern_library PUBLIC cxx_std_11)

add_subdirectory(tests)