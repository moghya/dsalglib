//
// Created by moghya_s on 12/26/2016.
//

#ifndef DSALGLIB_SELECTIONSORT_H
#define DSALGLIB_SELECTIONSORT_H

#include "array.h"
namespace dsa
{

    template<typename type>
    void selectionsort(array<type> arr,long long int size)
    {
        long long int i,j,k,min;
        for(i=0;i<size;i++)
        {
            min = i;
            for(j=i+1;j<size;j++)
            {
                if(arr[j]<arr[min])
                    min = j;
            }

            swapit(arr[i],arr[min]);
        }
    }

}
#endif //DSALGLIB_SELECTIONSORT_H
