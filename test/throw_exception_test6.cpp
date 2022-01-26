// Copyright 2018, 2022 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/throw_exception.hpp>
#include <boost/core/lightweight_test.hpp>

class my_exception: public std::exception
{
};

class my_exception2: public std::exception, public virtual boost::exception
{
};

int main()
{
    try
    {
        BOOST_THROW_EXCEPTION( my_exception() );
    }
    catch( std::exception const & x )
    {
        boost::source_location loc = boost::get_throw_location( x );

        BOOST_TEST_CSTR_EQ( loc.file_name(), __FILE__ );
        BOOST_TEST_EQ( loc.line(), 20 );
        BOOST_TEST_CSTR_EQ( loc.function_name(), BOOST_CURRENT_FUNCTION );
    }
    catch( ... )
    {
        BOOST_ERROR( "'BOOST_THROW_EXCEPTION( my_exception() )' didn't throw 'std::exception'" );
    }

    try
    {
        BOOST_THROW_EXCEPTION( my_exception2() );
    }
    catch( boost::exception const & x )
    {
        boost::source_location loc = boost::get_throw_location( x );

        BOOST_TEST_CSTR_EQ( loc.file_name(), __FILE__ );
        BOOST_TEST_EQ( loc.line(), 37 );
        BOOST_TEST_CSTR_EQ( loc.function_name(), BOOST_CURRENT_FUNCTION );
    }
    catch( ... )
    {
        BOOST_ERROR( "'BOOST_THROW_EXCEPTION( my_exception2() )' didn't throw 'boost::exception'" );
    }

    return boost::report_errors();
}
