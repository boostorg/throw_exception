module;

#include <boost/config.hpp>
#include <boost/config/workaround.hpp>
#include <boost/assert/current_location.hpp>

export module boost.throw_exception;

import std;
import boost.assert;

extern "C++" {
#include <boost/throw_exception.hpp>
}
