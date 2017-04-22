//
// Created by moghya_s on 12/26/2016.
//

#ifndef DSALGLIB_QUICKSORT_H_H
#define DSALGLIB_QUICKSORT_H_H

#include "array.h"

namespace dsa
{
    template<typename type>
    long long int partition(array<type> arr,long long int start,long long int end)
    {
        type var = arr[end];
        long long int i,j;
        i=start-1;
        for(j=start;j<end;j++)
        {
            if(arr[j]<=var)
            {   i++;
                swapit(arr[i],arr[j]);
            }
        }
        i++;
        swapit(arr[i],arr[end]);
        return i;
    }

    template<typename type>
    void quicksort(array<type> arr,long long int start,long long int end)
    {
        if(start<end)
        {
            long long int pivot;
            pivot = partition(arr,start,end);
            quicksort(arr,start,pivot-1);
            quicksort(arr,pivot+1,end);
        }
    }

}
#endif //DSALGLIB_QUICKSORT_H_H
