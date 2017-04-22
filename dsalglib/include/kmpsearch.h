//
// Created by moghya_s on 12/26/2016.
//

#ifndef DSALGLIB_KMPSEARCH_H
#define DSALGLIB_KMPSEARCH_H

#include "array.h"

namespace dsa
{
    template<typename type>
    void kmppreprocess(array<long long int> pre,array<type> pat){

        long long int pindex =0;
        for(long long int cindex=1; cindex < pat.size();)
        {
            if(pat[cindex] == pat[pindex]){
                pre[cindex] = pindex + 1;
                pindex++;
                cindex++;
            }else{
                if(pindex != 0){
                    pindex = pre[pindex-1];
                }else{
                    pre[cindex] = 0;
                    cindex++;
                }
            }
        }
    }

    template<typename type>
    array<long long int>  kmpsearch(array<type> arr,array<type> pat)
    {
        array<long long int> pre(pat.size(),0),res;
        kmppreprocess(pre,pat);

        long long int aindex=0,pindex=0;
        while(aindex<arr.size())
        {
            if(arr[aindex]==pat[pindex]){
                aindex++; pindex++;
            }

            if(pindex==pat.size()){
                res.push_back(aindex-pindex);
                pindex=pre[pindex-1];
            }else if(aindex<arr.size() && arr[aindex]!=pat[pindex]){
                if(pindex!=0) pindex= pre[pindex-1]; else aindex++;
            }
        }
        return res;
    }
}
#endif //DSALGLIB_KMPSEARCH_H
