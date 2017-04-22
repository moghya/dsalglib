//
// Created by moghya_s on 12/26/2016.
//

#ifndef DSALGLIB_MERGESORT_H
#define DSALGLIB_MERGESORT_H

#include "array.h"
namespace dsa
{
    template<typename type>
    void merge(array<type> arr,long long int size,long long int start,long long int middle,long long int end)
    {
        array<type> temp(size); long long int i,j,k;
        for(i=start;i<=end;i++)
            temp[i]=arr[i];
            
        i=start;
        j=middle+1;
        k=start;
        
        while(i<=middle&&j<=end)
        {
            if(temp[i]<=temp[j])
            {
                arr[k]=temp[i];
                i++;              
            }
            else
            {
                arr[k]=temp[j];
                j++;
            }
            k++;
        }
        while(i<=middle)
        {
            arr[k]=temp[i];
            k++;
            i++;
        }        
        
    }
    
    template<typename type>
    void mergesort(array<type> arr,long long int size,long long int start,long long int end)
    {
        if(start<end)
        {
            long long int middle = (start+end)/2;
            mergesort(arr,size,start,middle);
            mergesort(arr,size,middle+1,end);
            merge(arr,size,start,middle,end);
        }  
    }
}
#endif //DSALGLIB_MERGESORT_H
