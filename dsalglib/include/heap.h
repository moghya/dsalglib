//
// Created by moghya_s on 10/1/2016.
//

#ifndef DSALGLIB_HEAP_H
#define DSALGLIB_HEAP_H

#include "array.h"

namespace dsa
{
    template<class type>
    class maxheap
    {
        private:
            long long int count;
            array<type> objs;
            void _reheapup(long long int index)
            {
                if(index>0)
                {
                    long long int parent=(index-1)/2;
                    if(objs[parent]<objs[index])
                    {
                        swapit(objs[parent],objs[index]);
                        _reheapup(parent);
                    }
                }
                return ;
            }
            void _reheapdown(long long index)
            {

                if(index>=0&&index<count)
                {
                    long long int lc=2*index+1,rc=2*index+2,large;
                    if(lc<count)
                    {
                        large=lc;
                        if(rc<count)
                        {
                            if(objs[lc]<objs[rc])
                                large=rc;
                        }
                        if(objs[index]<objs[large])
                        {
                            swapit(objs[index],objs[large]);
                            _reheapdown(large);
                        }
                    }
                }
                return ;
            }

        public:

            maxheap(long long int size=0)
            {
                objs.resize(size);
                count = objs.size();
            }

            bool insert(type param)
            {
                objs.push_back(param);
                _reheapup(count);
                count=objs.size();
                return true;
            }

            type popmax()
            {
                type param;
                if(count>0)
                {
                    param = objs[0];
                    objs[0]=objs[count-1];
                    objs.pop_back();
                    count=objs.size();
                    _reheapdown(0);
                }
                return param;
            }

            type getmax()
            {
                return objs[0];
            }

            long long int size()
            {
                return count;
            }

            void traverse(void (fun)(type obj))
            {
                long long int i;
                for(i=0;i<count;i++)
                    fun(objs[i]);
            }

            void clear()
            {
                objs.clear();
                count=objs.size();
            }
    };

    template<class type>
    class minheap
    {
        private:
            long long int count;
            array<type> objs;
            void _reheapup(long long int index)
            {
                if(index>0)
                {
                    long long int parent=(index-1)/2;
                    if(objs[index]<objs[parent])
                    {
                        swapit(objs[parent],objs[index]);
                        _reheapup(parent);
                    }
                }
                return ;
            }

            void _reheapdown(long long index)
            {

                if(index>=0&&index<count)
                {
                    long long int lc=2*index+1,rc=2*index+2,less;
                    if(lc<count)
                    {
                        less=lc;
                        if(rc<count)
                        {
                            if(objs[rc]<objs[lc])
                                less=rc;
                        }
                        if(objs[less]<objs[index])
                        {
                            swapit(objs[index],objs[less]);
                            _reheapdown(less);
                        }
                    }
                }
                return ;
            }

        public:

            minheap(long long int size=0)
            {
                objs.resize(size);
                count = objs.size();
            }

            bool insert(type param)
            {
                objs.push_back(param);
                _reheapup(count);
                count=objs.size();
                return true;
            }

            type popmin()
            {
                type param;
                if(count>0)
                {
                    param=objs[0];
                    objs[0]=objs[count-1];
                    objs.pop_back();
                    count=objs.size();
                    _reheapdown(0);
                }
                return param;
            }

            type getmin()
            {

                return objs[0];
            }

            long long int size()
            {
                return count;
            }

            void traverse(void (fun)(type obj))
            {
                long long int i;
                for(i=0;i<count;i++)
                    fun(objs[i]);
            }

            void clear()
            {
                objs.clear();
                count=objs.size();
            }


    };
}
#endif //DSALGLIB_HEAP_H
