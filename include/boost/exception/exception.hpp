//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_274DA366004E11DCB1DDFE2E56D89593
#define UUID_274DA366004E11DCB1DDFE2E56D89593
#if (__GNUC__*100+__GNUC_MINOR__>301) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma GCC system_header
#endif
#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(push,1)
#endif

namespace
boost
    {
    namespace
    exception_detail
        {
        template <class T>
        class
        refcount_ptr
            {
            public:
            refcount_ptr():
                px_(0)
                {
                }
            ~refcount_ptr()
                {
                release();
                }
            refcount_ptr( refcount_ptr const & x ):
                px_(x.px_)
                {
                add_ref();
                }
            refcount_ptr &
            operator=( refcount_ptr const & x )
                {
                adopt(x.px_);
                return *this;
                }
            void
            adopt( T * px )
                {
                release();
                px_=px;
                add_ref();
                }
            T *
            get() const
                {
                return px_;
                }
            private:
            T * px_;
            void
            add_ref()
                {
                if( px_ )
                    px_->add_ref();
                }
            void
            release()
                {
                if( px_ && px_->release() )
                    px_=0;
                }
            };
        }

    ////////////////////////////////////////////////////////////////////////

    template <class Tag,class T> class error_info;
    typedef error_info<struct throw_function_,char const *> throw_function;
    typedef error_info<struct throw_file_,char const *> throw_file;
    typedef error_info<struct throw_line_,int> throw_line;
    template <>
    class
    error_info<throw_function_,char const *>
        {
        public:
        typedef char const * value_type;
        value_type v_;
        explicit
        error_info( value_type v ):
            v_(v)
            {
            }
        };
    template <>
    class
    error_info<throw_file_,char const *>
        {
        public:
        typedef char const * value_type;
        value_type v_;
        explicit
        error_info( value_type v ):
            v_(v)
            {
            }
        };
    template <>
    class
    error_info<throw_line_,int>
        {
        public:
        typedef int value_type;
        value_type v_;
        explicit
        error_info( value_type v ):
            v_(v)
            {
            }
        };

    ////////////////////////////////////////////////////////////////////////

#if defined(__GNUC__)
# if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  pragma GCC visibility push (default)
# endif
#endif
    class exception;
#if defined(__GNUC__)
# if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  pragma GCC visibility pop
# endif
#endif

    namespace
    exception_detail
        {
        class error_info_base;
        struct type_info_;
        struct
        error_info_container
            {
            virtual void add_ref() const = 0;
            virtual bool release() const = 0;
            virtual refcount_ptr<exception_detail::error_info_container> clone() const = 0;
            virtual error_info_base * get( type_info_ const & ) const = 0;
            protected:
            ~error_info_container() throw()
                {
                }
            };
        char const * & access_throw_function( exception const & );
        char const * & access_throw_file( exception const & );
        int & access_throw_line( exception const & );
        error_info_container * get_error_info_container( exception const & );
        void copy_boost_exception( exception *, exception const * );
        class error_info_container_impl;
        }

    ////////////////////////////////////////////////////////////////////////

#if defined(__GNUC__)
# if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  pragma GCC visibility push (default)
# endif
#endif
    class
    exception
        {
        protected:

        exception():
            throw_function_(0),
            throw_file_(0),
            throw_line_(0)
            {
            }

#ifdef __HP_aCC
        //On HP aCC, this protected copy constructor prevents throwing boost::exception.
        //On all other platforms, the same effect is achieved by the pure virtual destructor.
        exception( exception const & x ) throw():
            data_(x.data_),
            throw_function_(x.throw_function_),
            throw_file_(x.throw_file_),
            throw_line_(x.throw_line_)
            {
            }
#endif

        virtual ~exception() throw()
#ifndef __HP_aCC
            = 0 //Workaround for HP aCC, =0 incorrectly leads to link errors.
#endif
            ;

#if (defined(__MWERKS__) && __MWERKS__<=0x3207) || (defined(_MSC_VER) && _MSC_VER<=1310)
        public:
#else
        private:

        friend char const * & exception_detail::access_throw_function( exception const & );
        friend char const * & exception_detail::access_throw_file( exception const & );
        friend int & exception_detail::access_throw_line( exception const & );
        friend exception_detail::error_info_container * exception_detail::get_error_info_container( exception const & );
        friend void exception_detail::copy_boost_exception( exception *, exception const * );
        friend class exception_detail::error_info_container_impl;
#endif
        mutable exception_detail::refcount_ptr<exception_detail::error_info_container> data_;
        mutable char const * throw_function_;
        mutable char const * throw_file_;
        mutable int throw_line_;
        };
#if defined(__GNUC__)
# if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  pragma GCC visibility pop
# endif
#endif

    inline
    exception::
    ~exception() throw()
        {
        }

    ////////////////////////////////////////////////////////////////////////

    namespace
    exception_detail
        {
        inline
        char const * &
        access_throw_function( exception const & x )
            {
            return x.throw_function_;
            }
        inline
        char const * &
        access_throw_file( exception const & x )
            {
            return x.throw_file_;
            }
        inline
        int &
        access_throw_line( exception const & x )
            {
            return x.throw_line_;
            }
        template <class E>
        E const &
        set_info( E const & x, throw_function const & y )
            {
            access_throw_function(x)=y.v_;
            return x;
            }
        template <class E>
        E const &
        set_info( E const & x, throw_file const & y )
            {
            access_throw_file(x)=y.v_;
            return x;
            }
        template <class E>
        E const &
        set_info( E const & x, throw_line const & y )
            {
            access_throw_line(x)=y.v_;
            return x;
            }
        }

    ////////////////////////////////////////////////////////////////////////

    namespace
    exception_detail
        {
#if defined(__GNUC__)
# if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  pragma GCC visibility push (default)
# endif
#endif
        class
        clone_base
            {
            public:

            virtual clone_base const * clone() const = 0;
            virtual void rethrow() const = 0;

            virtual
            ~clone_base() throw()
                {
                }
            };
#if defined(__GNUC__)
# if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  pragma GCC visibility pop
# endif
#endif

        inline
        void
        copy_boost_exception( exception * a, exception const * b )
            {
            refcount_ptr<error_info_container> data;
            if( error_info_container * d=b->data_.get() )
                data = d->clone();
            a->throw_file_ = b->throw_file_;
            a->throw_line_ = b->throw_line_;
            a->throw_function_ = b->throw_function_;
            a->data_ = data;
            }

        inline
        void
        copy_boost_exception( void *, void const * )
            {
            }

#if defined(__GNUC__)
# if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  pragma GCC visibility push (default)
# endif
#endif
        template <class T>
        class
        clone_impl:
            public T,
            public virtual clone_base
            {
            struct clone_tag { };
            clone_impl( clone_impl const & x, clone_tag ):
                T(x)
                {
                copy_boost_exception(this,&x);
                }

            public:

            explicit
            clone_impl( T const & x ):
                T(x)
                {
                copy_boost_exception(this,&x);
                }

            ~clone_impl() throw()
                {
                }

            private:

            clone_base const *
            clone() const
                {
                return new clone_impl(*this,clone_tag());
                }

            void
            rethrow() const
                {
                throw*this;
                }
            };
        }
#if defined(__GNUC__)
# if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  pragma GCC visibility pop
# endif
#endif

    template <class T>
    inline
    exception_detail::clone_impl<T>
    enable_current_exception( T const & x )
        {
        return exception_detail::clone_impl<T>(x);
        }

    ////////////////////////////////////////////////////////////////////////

#if defined(__GNUC__)
# if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  pragma GCC visibility push (default)
# endif
#endif
    class
    exception_info:
        public exception
        {
        public:
        virtual
        ~exception_info() throw() /*noexcept*/
            {
            }
        exception_info() /*noexcept*/
            {
            }
        exception_info( char const * file, int line, char const * function ) /*noexcept*/;
        exception_info( exception_info const & r )
            {
            exception_detail::copy_boost_exception(this,&r);
            }
        exception_info( exception_info && ) /*noexcept*/;
        exception_info & operator=( exception_info const & );
        exception_info & operator=( exception_info && ) /*noexcept*/;
        char const * file() const /*noexcept*/;
        int line() const /*noexcept*/;
        char const * function() const /*noexcept*/;
        template <class Tag> exception_info & unset();
        template <class Tag> exception_info & set( typename Tag::type const & );
        template <class Tag> exception_info & set( typename Tag::type && );
        template <class Tag> typename Tag::type const * get() const;
        template <class Tag> typename Tag::type * get();
        char const * diagnostic_info() const;
        };
    namespace
    exception_detail
        {
        template <class T>
        struct
        exception_info_injector:
            T,
            exception_info
            {
            explicit
            exception_info_injector( T const & x ):
                T(x)
                {
                }
            ~exception_info_injector() throw()
                {
                }
            };
        }
#if defined(__GNUC__)
# if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  pragma GCC visibility pop
# endif
#endif

    namespace
    exception_detail
        {
        struct large_size { char c[256]; };
        large_size dispatch_boost_exception( exception const * );

        struct small_size { };
        small_size dispatch_boost_exception( void const * );

#if defined(__GNUC__)
# if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  pragma GCC visibility push (default)
# endif
#endif
        template <class T>
        struct
        exception_injector:
            T,
            exception_info
            {
            explicit
            exception_injector( T const & x ):
                T(x)
                {
                }
            ~exception_injector() throw()
                {
                }
            };
#if defined(__GNUC__)
# if (__GNUC__ == 4 && __GNUC_MINOR__ >= 1) || (__GNUC__ > 4)
#  pragma GCC visibility pop
# endif
#endif

        template <class,int>
        struct enable_error_info_helper;

        template <class T>
        struct
        enable_error_info_helper<T,sizeof(large_size)>
            {
            typedef T type;
            };

        template <class T>
        struct
        enable_error_info_helper<T,sizeof(small_size)>
            {
            typedef exception_injector<T> type;
            };

        template <class T>
        struct
        enable_error_info_return_type
            {
            typedef typename enable_error_info_helper<T,sizeof(exception_detail::dispatch_boost_exception(static_cast<T *>(0)))>::type type;
            };
        }

    template <class T>
    typename
    exception_detail::enable_error_info_return_type<T>::type
    enable_error_info( T const & x )
        {
        typedef typename exception_detail::enable_error_info_return_type<T>::type rt;
        return rt(x);
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif
