# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(RPGTests LANGUAGES CXX)

add_executable(RPG_test source/RPG_test.cpp)
target_link_libraries(RPG_test PRIVATE RPG_lib)
target_compile_features(RPG_test PRIVATE cxx_std_17)

add_test(NAME RPG_test COMMAND RPG_test)

add_folders(Test)
