// Copyright 2019 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/throw_exception.hpp>
#include <cstdlib>
#include <cstring>

class my_exception: public std::exception {};

int main()
{
    BOOST_THROW_EXCEPTION( my_exception() );
    return 1;
}

namespace boost
{

void throw_exception( std::exception const &, boost::source_location const & loc )
{
    int r = 0;

    if( std::strcmp( loc.file_name(), __FILE__ ) != 0 ) ++r;
    if( loc.line() != 13 ) ++r;

    std::exit( r );
}

} // namespace boost
