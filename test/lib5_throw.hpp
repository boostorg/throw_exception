#ifndef LIB5_THROW_HPP_INCLUDED
#define LIB5_THROW_HPP_INCLUDED

// Copyright 2018 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/exception/exception.hpp>
#include <boost/config.hpp>
#include <exception>

#if defined(LIB5_DYN_LINK)
# if defined(LIB5_SOURCE)
#  define LIB5_DECL BOOST_SYMBOL_EXPORT
# else
#  define LIB5_DECL BOOST_SYMBOL_IMPORT
# endif
#else
# define LIB5_DECL
#endif

namespace lib5
{

struct BOOST_SYMBOL_VISIBLE exception: public std::exception, public boost::exception
{
};

LIB5_DECL void f();

} // namespace lib5

#endif // #ifndef LIB5_THROW_HPP_INCLUDED
