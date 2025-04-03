//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.
//Copyright (c) 2025 Antony Polukhin.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// To compile manually use a command like the folowing:
// clang++ -std=c++20 -fmodule-file=throw_exception.pcm throw_exception.pcm usage_sample.cpp

#include <exception>

import Boost.ThrowException;

class my_exception: public std::exception { };

int
main()
    {
    try
        {
        boost::throw_exception(my_exception());
        return 1;
        }
    catch(
    my_exception & )
        {
        }
    catch(
    ... )
        {
        return 2;
        }
    }
