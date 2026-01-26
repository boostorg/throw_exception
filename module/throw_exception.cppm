// Copyright (c) 2016-2024 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// To compile manually use a command like the folowing:
// clang++ -I ../include -std=c++20 --precompile -x c++-module throw_exception.cppm

#define BOOST_THROW_EXCEPTION_BEGIN_MODULE_EXPORT export {
#define BOOST_THROW_EXCEPTION_END_MODULE_EXPORT }

module;

#include <boost/assert/source_location.hpp> // TODO: modularize
#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#ifndef BOOST_THROW_EXCEPTION_HAS_STD_MODULE
#include <exception>
#include <utility>
#include <cstddef>
#include <memory>
#include <exception>
#include <type_traits>
#endif

export module Boost.ThrowException;

#ifdef BOOST_THROW_EXCEPTION_HAS_STD_MODULE
import std;
#endif

#ifdef __clang__
#   pragma clang diagnostic ignored "-Winclude-angled-in-module-purview"
#endif

#ifdef BOOST_THROW_EXCEPTION_ATTACH_TO_GLOBAL_MODULE
extern "C++" {
#include <boost/throw_exception.hpp>
}
#else
#include <boost/throw_exception.hpp>
#endif
