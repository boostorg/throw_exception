// Copyright 2019 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/throw_exception.hpp>
#include <cstdlib>

class my_exception: public std::exception {};

int main()
{
    boost::throw_exception( my_exception() );
    return 1;
}

namespace boost
{

void throw_exception( std::exception const & )
{
    std::exit( 0 );
}

} // namespace boost
