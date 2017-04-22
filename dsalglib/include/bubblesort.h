//
// Created by moghya_s on 10/2/2016.
//

#ifndef DSALGLIB_BUBBLESORT_H
#define DSALGLIB_BUBBLESORT_H

#include "array.h"
namespace dsa
{

    template<typename type>
    void bubblesort( array<type> arr,long long int size)
    {
        long long int i,j;
        for(i=0;i<size;i++)
        {
            for(j=1;j<size;j++)
            {
                if(arr[j]<arr[j-1])
                    swapit(arr[j],arr[j-1]);
            }
        }
    }
}
#endif //DSALGLIB_BUBBLESORT_H
