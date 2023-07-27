#Set binary path
setup_component()

add_executable(app app.cpp)

target_compile_features(app PRIVATE cxx_std_17)
target_link_libraries(app PRIVATE modern_library fmt::fmt)
target_include_directories(app PUBLIC ${CMAKE_BINARY_DIR}/include/)
