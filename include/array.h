//
// Created by moghya_s on 10/1/2016.
//

#ifndef DSALGLIB_ARRAY_H
#define DSALGLIB_ARRAY_H
namespace dsa
{
        template<class type>
        class array
        {
            private:
                static const long long int spare = 5;
                long long int count,capacity;
                type *objs;
            public:
                array(long long int size=0)
                {
                    count = size;
                    capacity=size+spare;
                    objs = new type[capacity];
                }

                array(long long int size,type param)
                {
                    count = size;
                    capacity=size+spare;
                    objs = new type[capacity];
                    long long int i;
                    for(i=0;i<count;i++)
                        objs[i]=param;
                }
                void resize(long long int newsize)
                {
                    if(newsize<capacity) return ;

                    type *old = objs;
                    objs = new type[newsize];

                    long long int temp;
                    for(temp=0;temp<count;temp++)
                        objs[temp] = old[temp];

                    if(capacity!=0)
                        delete [] old;
                    capacity = newsize;
                    return;
                }

                type &operator[](long long int index)
                {
                    if(index>=0&&index<count)
                    {
                        return objs[index];
                    }
                }

                void operator=(array<type> from)
                {
                    clear();
                    long long int i,j;
                    j=from.size();
                    for(i=0;i<j;i++)
                        push_back(from[i]);
                    return;
                }


                void push_back(type param)
                {
                    if(count==capacity)
                        resize(capacity+spare);
                    count++;
                    objs[count-1]=param;
                    return;
                }

                void pop_back()
                {
                    type temp = objs[count-1];
                    count--;
                    return ;
                }

                void reverse(long long int start,long long int end)
                {
                    if(start>=0&&start<count&&end>=0&&end<count)
                    {
                        while(start<end)
                        {
                            swapit(objs[start],objs[end]);
                            start++;
                            end--;
                        }
                    }
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

                bool isempty()
                {
                    if(count==0) return true; return false;
                }

                void clear()
                {
                    type *old = objs;
                    if(capacity!=0)
                        delete [] old;
                    count = 0;
                    capacity = spare;
                    objs = new type[capacity];
                }
        };
}

#endif //DSALGLIB_ARRAY_H
