//          Copyright hotwatermorning 2013 - 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <cstddef>
#include <functional>
#include <future>
#include <tuple>
#include <type_traits>

#include "./task_base.hpp"

namespace hwm {

namespace detail { namespace ns_task {

template<size_t... Indecies>
struct index_tuple
{};

template<size_t Index, size_t... Indecies>
struct make_index_tuple_helper
{
    typedef
        typename make_index_tuple_helper<Index-1, Index-1, Indecies...>::type
    type;
};

template<size_t... Indecies>
struct make_index_tuple_helper<0, Indecies...>
{
    typedef
        index_tuple<Indecies...>
    type;
};

template<size_t Size>
struct make_index_tuple
{
    typedef
       typename make_index_tuple_helper<Size>::type
    type;
};


//! F and Args are decayed
template<class Ret, class F, class... Args>
struct task_impl
    :   task_base
{
    typedef std::promise<Ret> promise_t;

    typedef std::tuple<typename std::decay<F>::type, typename std::decay<Args>::type...> bound_t;

    task_impl(  promise_t && promise,
                typename std::decay<F>::type f,
                typename std::decay<Args>::type... args )
        :   promise_(std::move(promise))
        ,   bound_(std::move(f), std::move(args)...)
    {}

    task_impl(task_impl const &) = delete;
    task_impl &
        operator=(task_impl const &) = delete;

private:
    void run() override final
    {
        typedef typename make_index_tuple<sizeof...(Args)>::type index_t;
        invoke_task(index_t());
    }

    template<std::size_t... Indecies>
    void invoke_task(index_tuple<Indecies...>)
    {
		try {
			invoke_impl(
				promise_,
				std::move(std::get<0>(bound_)),
				std::move(std::get<Indecies+1>(bound_))... );
		} catch(...) {
			promise_.set_exception(std::current_exception());
		}
    }

	template<class Func, class... FuncArgs>
	static void invoke_impl(std::promise<void> &promise, Func &&f, FuncArgs&&... args)
	{
        std::bind(std::forward<Func>(f), std::forward<FuncArgs>(args)...)();
		promise.set_value();
	}

	template<class FuncRet, class Func, class... FuncArgs>
	static void invoke_impl(std::promise<FuncRet> &promise, Func &&f, FuncArgs&&... args)
	{
		promise.set_value(
			std::bind(std::forward<Func>(f), std::forward<FuncArgs>(args)...)()
			);
	}

private:
    promise_t   promise_;
    bound_t     bound_;
};

template<class Ret, class F, class... Args>
std::unique_ptr<task_base>
    make_task(std::promise<Ret>&& promise, F f, Args... args)
{
    return
        std::unique_ptr<task_base>(
            new task_impl<Ret, F, Args...> (
                std::move(promise),
                std::forward<F>(f),
                std::forward<Args>(args)...
            ));
}

}}  //namespace detail::ns_task

}   //namespace hwm
