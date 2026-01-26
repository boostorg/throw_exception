# Copyright (c) 2025 Antony Polukhin
#
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

cmake_minimum_required(VERSION 3.28)

function (_add_boost_throw_exception_module_impl NAME)
    add_library(${NAME})
    target_compile_features(${NAME} PUBLIC cxx_std_20)
    target_sources(${NAME} PUBLIC
        FILE_SET modules_public TYPE CXX_MODULES FILES
            ${CMAKE_CURRENT_LIST_DIR}/throw_exception.cppm
    )
endfunction()

function (add_boost_throw_exception_module NAME)
    _add_boost_throw_exception_module_impl(${NAME})
    target_include_directories(${NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../include)

    _add_boost_throw_exception_module_impl(${NAME}_migration)
    target_include_directories(${NAME}_migration PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../include)
    target_compile_definitions(${NAME}_migration PRIVATE BOOST_THROW_EXCEPTION_ATTACH_TO_GLOBAL_MODULE)
endfunction()

add_boost_throw_exception_module(boost_throw_exception_module)
add_library(Boost::throw_exception_module ALIAS boost_throw_exception_module)
add_library(Boost::throw_exception_module_migration ALIAS boost_throw_exception_module_migration)

if (BUILD_TESTING)
    add_executable(boost_throw_exception_module_usage usage_sample.cpp)
    target_link_libraries(boost_throw_exception_module_usage PRIVATE Boost::throw_exception_module)

    # Make sure that mixing includes and imports is fine for different TU
    add_executable(boost_throw_exception_module_usage_mu usage_test_mu1.cpp usage_test_mu2.cpp)
    target_link_libraries(boost_throw_exception_module_usage_mu PRIVATE Boost::throw_exception_module_migration)
endif()
