set(TESTING_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/testing.bin)
set(MAIN_CPP ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

function(test_suit name source)
    add_executable(${name} ${MAIN_CPP} ${source})
    target_include_directories(${name} PRIVATE ${CMAKE_SOURCE_DIR})
    target_link_libraries(${name} PRIVATE gtest::gtest Boost::system)
    set_target_properties(${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                             ${TESTING_RUNTIME_OUTPUT_DIRECTORY})
    add_test(${name} ${TESTING_RUNTIME_OUTPUT_DIRECTORY}/${name})
endfunction()

add_subdirectory(parser)
