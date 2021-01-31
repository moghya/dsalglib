//
// Created by moghya_s on 10/1/2016.
//

#ifndef DSALGLIB_ALGINC_H
#define DSALGLIB_ALGINC_H

/*
 * contains fundamental functions required
 */

namespace dsa
{

    template <class T>
    struct remove_reference {
        using type = T;
    };
    template <class T>
    struct remove_reference<T&> {
        using type = T;
    };
    template <class T>
    struct remove_reference<T&&> {
        using type = T;
    };

    // Analogue of std::move
    template <class T>
    typename remove_reference<T>::type&&
    rvalue_cast(T&& t) noexcept
    {
        return static_cast<typename remove_reference<T>::type&&>(t);
    }


    template<typename T>
    inline void swapit(T &x, T &y)
    {
        T t = rvalue_cast(x);
        x = rvalue_cast(y);
        y = rvalue_cast(t);
    }

    template<typename T>
    inline T maxof(T x, T y)
    {
        T max;
        max = (x > y) ? x : y;
        return max;
    }

    template<typename T>
    inline T minof(T x, T y)
    {
        T min;
        min = (x < y) ? x : y;
        return min;
    }

    // Analogue of std::forward.
    template<class T>
    T&& forward(typename remove_reference<T>::type& t) noexcept
    {
        return static_cast<T&&>(t);
    }
    template<class T>
    T&& forward(typename remove_reference<T>::type&& t) noexcept
    {
        return static_cast<T&&>(t);
    }

}
#endif //DSALGLIB_ALGINC_H
