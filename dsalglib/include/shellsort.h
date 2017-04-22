//
// Created by moghya_s on 12/26/2016.
//

#ifndef DSALGLIB_SHELLSORT_H
#define DSALGLIB_SHELLSORT_H

#include "array.h"
namespace dsa
{
    template<typename type>
    void shellsort(array<type> arr,long long int size)
    {
        long long int incr,cur,temp;
        type var;
        for(incr=(size-1)/2;incr>0;incr/=2)
        {
            for (cur = incr; cur <size; cur++)
            {
                var=arr[cur];                
                for(temp=cur-incr;temp>=0&&var<arr[temp];temp-=incr)
                {
                    arr[temp+incr]=arr[temp];
                }
                arr[temp+incr]=var;
            }
        }
        return ;
    }
}
#endif //DSALGLIB_SHELLSORT_H
