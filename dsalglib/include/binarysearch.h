//
// Created by moghya_s on 10/2/2016.
//

#ifndef DSALGLIB_BINARYSEARCH_H
#define DSALGLIB_BINARYSEARCH_H

#include "array.h"
namespace dsa
{
    template<typename type>
    long long int binarysearch( array<type> arr,long long int start,long long int end,type param)
    {
        if(start<=end)
        {
            long long int mid=(start+end)/2;
            if(arr[mid]<param)
                return binarysearch(arr,mid+1,end,param);
            else
            if(param<arr[mid])
                return binarysearch(arr,start,mid-1,param);
            else
                return mid;
        }
        else
        {
            return -1;
        }
    }
}
#endif //DSALGLIB_BINARYSEARCH_H
