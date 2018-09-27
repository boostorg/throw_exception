// Copyright 2018 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include "lib1_throw.hpp"
#include "lib2_throw.hpp"
#include "lib3_throw.hpp"
#include <boost/exception/exception.hpp>
#include <boost/exception_ptr.hpp>
#include <boost/core/lightweight_test.hpp>

void test_catch_by_type()
{
    BOOST_TEST_THROWS( lib1::f(), lib1::exception );
    BOOST_TEST_THROWS( lib2::f(), lib2::exception );
    BOOST_TEST_THROWS( lib3::f(), lib3::exception );
}

void test_catch_by_exception()
{
    BOOST_TEST_THROWS( lib2::f(), boost::exception );
    BOOST_TEST_THROWS( lib3::f(), boost::exception );
}

void test_exception_ptr()
{
    try
    {
        lib2::f();
    }
    catch( ... )
    {
        boost::exception_ptr p = boost::current_exception();

        BOOST_TEST_THROWS( boost::rethrow_exception( p ), lib2::exception );
        BOOST_TEST_THROWS( boost::rethrow_exception( p ), boost::exception );
    }

    try
    {
        lib3::f();
    }
    catch( ... )
    {
        boost::exception_ptr p = boost::current_exception();

        BOOST_TEST_THROWS( boost::rethrow_exception( p ), lib3::exception );
        BOOST_TEST_THROWS( boost::rethrow_exception( p ), boost::exception );
    }
}

int main()
{
    test_catch_by_type();
    test_catch_by_exception();
    test_exception_ptr();

    return boost::report_errors();
}
