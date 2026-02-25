# Copyright 2019 Peter Dimov
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

cmake_minimum_required(VERSION 3.5...3.31)
project(boost_throw_exception VERSION "${BOOST_SUPERPROJECT_VERSION}" LANGUAGES CXX)

if (BOOST_USE_MODULES)
  add_library(boost_throw_exception STATIC)
  target_sources(boost_throw_exception PUBLIC FILE_SET CXX_MODULES BASE_DIRS modules FILES modules/boost_throw_exception.cppm)
  set(__scope PUBLIC)

  # Enable and propagate C++23, import std, and the modules macro
  target_compile_features(boost_throw_exception PUBLIC cxx_std_23)
  set_target_properties(boost_throw_exception PROPERTIES CXX_MODULE_STD 1)
  target_compile_definitions(boost_throw_exception PUBLIC BOOST_USE_MODULES)

  # Silence warnings about includes in the purview
  if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(boost_throw_exception PRIVATE -Wno-include-angled-in-module-purview)
  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(boost_throw_exception PRIVATE /wd5244)
  endif()
else()
  add_library(boost_throw_exception INTERFACE)
  set(__scope INTERFACE)
endif()

add_library(Boost::throw_exception ALIAS boost_throw_exception)
target_include_directories(boost_throw_exception ${__scope} include)
target_link_libraries(boost_throw_exception
  ${__scope}
    Boost::assert
    Boost::config
)

if(BUILD_TESTING)

  add_subdirectory(test)

endif()
