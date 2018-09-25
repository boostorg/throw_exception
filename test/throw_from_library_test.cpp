// Copyright 2018 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include "lib1_throw.hpp"
#include "lib2_throw.hpp"
#include "lib3_throw.hpp"
#include <boost/core/lightweight_test.hpp>

int main()
{
    BOOST_TEST_THROWS( lib1::f(), lib1::exception );
    BOOST_TEST_THROWS( lib2::f(), lib2::exception );
    BOOST_TEST_THROWS( lib3::f(), lib3::exception );

    return boost::report_errors();
}
