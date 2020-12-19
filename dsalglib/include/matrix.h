//
// Created by moghya_s on 12/26/2016.
//

#ifndef DSALGLIB_MATRIX_H
#define DSALGLIB_MATRIX_H
#include "array.h"
namespace dsa
{
    template<typename type>
    array< array<type> > matrix_add(array< array<type> > arr1,array< array<type> > arr2)
    {
        long long int n1 = arr1.size(), n2 = arr2.size(), m1 = arr1[0].size(), m2=arr2[0].size();
        array<type> a(m1);
        array< array<type> > re(n1);
        for(int i=0;i<n1;i++)
        re[i]=a;
        for(int i=0;i<n1;i++)
        {
            for(int j=0;j<m1;j++)
            {
                re[i][j]=arr1[i][j]+arr2[i][j];
            }
        }
        return re;
    }

    template<typename type>
    array< array<type> > matrix_mul(array< array<type> > arr1,array< array<type> > arr2)
    {
        long long int n1 = arr1.size(), n2 = arr2.size(), m1 = arr1[0].size(), m2=arr2[0].size();
        array<type> a(m2);
        array< array<type> > re(n1);
        for(int i=0;i<n1;i++)
        re[i]=a;
        for(int i=0;i<n1;i++)
        {
            for(int j=0;j<m2;j++)
            {
                for(int k=0;k<m1;k++)
                {
                    re[i][j]=re[i][j]+arr1[i][k]*arr2[k][j];
                }
            }
        }
        return re;
    }

    template<typename type>
    array< array<type> > matrix_sub(array< array<type> > arr1,array< array<type> > arr2)
    {
        long long int n1 = arr1.size(), n2 = arr2.size(), m1 = arr1[0].size(), m2=arr2[0].size();
        array<type> a(m1);
        array< array<type> > re(n1);
        for(int i=0;i<n1;i++)
        re[i]=a;
        for(int i=0;i<n1;i++)
        {
            for(int j=0;j<m1;j++)
            {
                
                re[i][j]=arr1[i][j]-arr2[i][j];
            }
        }
        return re;
    }

    template<typename type>
    array< array<type> > matrix_cons_add(array< array<type> > arr1, type par)
    {
        long long int n1 = arr1.size(), m1 = arr1[0].size();
        array<type> a(m1);
        array< array<type> > re(n1);
        for(int i=0;i<n1;i++)
        re[i]=a;
        for(int i=0;i<n1;i++)
        {
            for(int j=0;j<m1;j++)
            {
                
                re[i][j]=arr1[i][j]+par;
            }
        }
        return re;
    }

    template<typename type>
    array< array<type> > matrix_cons_sub(array< array<type> > arr1, type par)
    {
        long long int n1 = arr1.size(), m1 = arr1[0].size();
        array<type> a(m1);
        array< array<type> > re(n1);
        for(int i=0;i<n1;i++)
        re[i]=a;
        for(int i=0;i<n1;i++)
        {
            for(int j=0;j<m1;j++)
            {
                
                re[i][j]=arr1[i][j]-par;
            }
        }
        return re;
    }

    template<typename type>
    array< array<type> > matrix_cons_mul(array< array<type> > arr1, type par)
    {
        long long int n1 = arr1.size(), m1 = arr1[0].size();
        array<type> a(m1);
        array< array<type> > re(n1);
        for(int i=0;i<n1;i++)
        re[i]=a;
        for(int i=0;i<n1;i++)
        {
            for(int j=0;j<m1;j++)
            {
                
                re[i][j]=arr1[i][j]*par;
            }
        }
        return re;
    }

    template<typename type>
    array< array<type> > matrix_cons_div(array< array<type> > arr1, type par)
    {
        long long int n1 = arr1.size(), m1 = arr1[0].size();
        array<type> a(m1);
        array< array<type> > re(n1);
        for(int i=0;i<n1;i++)
        re[i]=a;
        for(int i=0;i<n1;i++)
        {
            for(int j=0;j<m1;j++)
            {
                
                re[i][j]=arr1[i][j]/par;
            }
        }
        return re;
    }

    template<typename type>
    array< array<type> > matrix_transpose(array< array<type> > arr1)
    {
        long long int n1 = arr1.size(), m1 = arr1[0].size();
        array<type> a(n1);
        array< array<type> > re(m1);
        for(int i=0;i<n1;i++)
        re[i]=a;
        for(int i=0;i<m1;i++)
        {
            for(int j=0;j<n1;j++)
            {
                
                re[i][j]=arr1[j][i];
            }
        }
        return re;
    }

}
#endif //DSALGLIB_MATRIX_H
