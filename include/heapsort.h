//
// Created by moghya_s on 12/26/2016.
//

#ifndef DSALGLIB_HEAPSORT_H
#define DSALGLIB_HEAPSORT_H

#include "array.h"
namespace dsa
{

    template<typename type>
    void _reheapup(array<type> objs,long long int index)
    {
        if(index>0)
        {
            long long int parent=(index-1)/2;
            if(objs[parent]<objs[index])
            {
                swapit(objs[parent],objs[index]);
                _reheapup(objs,parent);
            }
        }
        return ;
    }


    template<typename type>
    void _reheapdown(array<type> objs,long long index,long long int last)
    {

        if(index>=0&&index<last)
        {
            long long int lc=2*index+1,rc=2*index+2,large;
            if(lc<last)
            {
                large=lc;
                if(rc<last)
                {
                    if(objs[lc]<objs[rc])
                        large=rc;
                }
                if(objs[index]<objs[large])
                {
                    swapit(objs[index],objs[large]);
                    _reheapdown(objs,large,last);
                }
            }
        }
        return ;
    }

    template<typename type>
    void heapsort(array<type> arr)
    {
        long long int i,last = arr.size(),done;
        for(i=0;i<last;i++)
            _reheapup(arr,i);

        done = last;
        while(done>0)
        {
            swapit(arr[0],arr[done-1]);
            done--;
            _reheapdown(arr,0,done);
        }

        return ;

    }

}
#endif //DSALGLIB_HEAPSORT_H
