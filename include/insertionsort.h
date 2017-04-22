//
// Created by moghya_s on 12/26/2016.
//

#ifndef DSALGLIB_INSERTIONSORT_H
#define DSALGLIB_INSERTIONSORT_H

#include "array.h"
namespace dsa
{
    template<typename type>
    void insertionsort(array<type> arr,long long int size)
    {
        long long int i,j,var;
        for(i=1;i<size;i++)
        {
            var = arr[i];
            for(j=i-1;j>=0&&var<arr[j];j--)
                arr[j+1]=arr[j];

            arr[j+1]=var;

        }
    }
}
#endif //DSALGLIB_INSERTIONSORT_H
