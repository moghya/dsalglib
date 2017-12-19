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


    template<typename T>
    inline void swapit(T &x, T &y)
    {
      x=x+y;
      y=x-y;
      x=x-y;
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

}
#endif //DSALGLIB_ALGINC_H
