#ifndef PIPES_INVOKE_HPP
#define PIPES_INVOKE_HPP

#include <functional>
#include <type_traits>

namespace pipes
{
    namespace detail
    {
        #if __cplusplus >= 201703L
        template<class F, class... As>
        using invoke_result_t = typename std::invoke_result<F, As...>::type;
        #else
        template<class F, class... As>
        using invoke_result_t = typename std::result_of<F(As...)>::type;
        #endif

        template<typename Functor, typename... Args>
        typename std::enable_if<
        std::is_member_pointer<typename std::decay<Functor>::type>::value,
        invoke_result_t<Functor&&, Args&&...>
        >::type invoke(Functor&& f, Args&&... args)
        {
            return std::mem_fn(f)(std::forward<Args>(args)...);
        }
        
        template<typename Functor, typename... Args>
        typename std::enable_if<
        !std::is_member_pointer<typename std::decay<Functor>::type>::value,
        invoke_result_t<Functor&&, Args&&...>
        >::type invoke(Functor&& f, Args&&... args)
        {
            return std::forward<Functor>(f)(std::forward<Args>(args)...);
        }
    }
}

#endif /* PIPES_INVOKE_HPP */
