//Copyright (c) 2006-2008 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_6F463AC838DF11DDA3E6909F56D89593
#define UUID_6F463AC838DF11DDA3E6909F56D89593

#include <boost/exception/detail/type_info.hpp>
#include <iomanip>
#include <ios>
#include <string>
#include <sstream>

namespace
boost
    {
    namespace
    exception_detail
        {
        template <class T>
        inline
        std::string
        object_hex_dump( T const & x, size_t max_size=16 )
            {
            std::ostringstream s;
            s << "type: " << type_name<T>() << ", size: " << sizeof(T) << ", dump: ";
            size_t n=sizeof(T)>max_size?max_size:sizeof(T);
            s.fill('0');
            s.width(2);
            unsigned char const * b=reinterpret_cast<unsigned char const *>(&x);
            s << std::setw(2) << std::hex << (unsigned int)*b;
            for( unsigned char const * e=b+n; ++b!=e; )
                s << " " << std::setw(2) << std::hex << (unsigned int)*b;
            return s.str();
            }
        }
    }

#endif
