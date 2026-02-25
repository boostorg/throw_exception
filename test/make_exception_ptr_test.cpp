// Copyright 2020 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#ifdef BOOST_USE_MODULES

#include <stdio.h>

int main()
{
    printf("This test depends on Boost.Exception and can't be run with C++20 modules yet\n");
}

#else

#if defined(_MSC_VER)
# pragma warning(disable: 4702) // unreachable code
#endif

#include <boost/exception_ptr.hpp>
#include <boost/core/lightweight_test.hpp>

class my_exception: public std::exception {};

int main()
{
    BOOST_TEST_THROWS( boost::rethrow_exception( boost::make_exception_ptr( my_exception() ) ), my_exception );
    return boost::report_errors();
}

#endif
