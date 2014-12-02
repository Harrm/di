//
// Copyright (c) 2014 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_DI_PROVIDERS_NOTHROW_REDUCE_HEAP_USAGE_HPP
#define BOOST_DI_PROVIDERS_NOTHROW_REDUCE_HEAP_USAGE_HPP

#include <new>
#include "boost/di/aux_/type_traits.hpp"

namespace boost { namespace di { namespace providers {

class nothrow_reduce_heap_usage {
public:
    template<class TDependency, class, class T = typename TDependency::given, class... TArgs>
    inline auto* get_ptr(TArgs&&... args) const noexcept {
        return new (std::nothrow) T{std::forward<TArgs>(args)...};
    }

    template<class TDependency, class, class T = typename TDependency::given, class... TArgs>
    inline auto get_value(TArgs&&... args) const noexcept {
        return T{std::forward<TArgs>(args)...};
    }

    template<class TDependency, class TDst, class T = typename TDependency::given, class... TArgs>
    inline std::enable_if_t<((std::is_pointer<TDst>{} || aux::has_element_type<TDst>{} ) && std::is_same<typename TDependency::scope, scopes::unique>{}) || !std::is_same<typename TDependency::scope, scopes::unique>{}, T*>
    get(TArgs&&... args) const noexcept {
        return get_ptr<TDependency, TDst>(std::forward<TArgs>(args)...);
    }

    template<class TDependency, class TDst, class T = typename TDependency::given, class... TArgs>
    inline std::enable_if_t<(!std::is_pointer<TDst>{} && !aux::has_element_type<TDst>{} ) && std::is_same<typename TDependency::scope, scopes::unique>{}, T>
    get(TArgs&&... args) const noexcept {
        return get_value<TDependency, TDst>(std::forward<TArgs>(args)...);
    }

};

}}} // namespace boost::di::providers

#endif

