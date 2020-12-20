#ifndef DSALGLIB_MATRIX_H
#define DSALGLIB_MATRIX_H
#include "array.h"
namespace dsa
{
    // Addition of Matrices
    template<typename type>
    array< array<type> > matrix_add(array< array<type> > arr1,array< array<type> > arr2)
    {
        long long int n1 = arr1.size(), n2 = arr2.size();
        long long int m1 = arr1[0].size(), m2=arr2[0].size();
        array< array<type> > re(n1);
        for(int i=0;i<n1;i++)
        {
            re[i]=array<type>(m1);
            for(int j=0;j<m1;j++)
            {
                re[i][j]=arr1[i][j]+arr2[i][j];
            }
        }
        return re;
    }

    // Subtraction of Matrices
    template<typename type>
    array< array<type> > matrix_sub(array< array<type> > arr1,array< array<type> > arr2)
    {
        long long int n1 = arr1.size(), n2 = arr2.size(), m1 = arr1[0].size(), m2=arr2[0].size();
        array< array<type> > re(n1);
        for(int i=0;i<n1;i++)
        {
            re[i]=array<type>(m1);
            for(int j=0;j<m1;j++)
            {
                re[i][j]=arr1[i][j]-arr2[i][j];
            }
        }
        return re;
    }

    // Muliplying Matrices of same size
    template<typename type>
    array< array<type> > matrix_multwo(array< array<type> > arr1,array< array<type> > arr2)
    {
        long long int n1 = arr1.size(), n2 = arr2.size(), m1 = arr1[0].size(), m2=arr2[0].size();
        array< array<type> > re(n1);
        for(int i=0;i<n1;i++)
        {
            re[i]=array<type>(m1);
            for(int j=0;j<m1;j++)
            {
                re[i][j]=arr1[i][j]*arr2[i][j];
            }
        }
        return re;
    }

    // Matrix Multiplication
    template<typename type>
    array< array<type> > matrix_mul(array< array<type> > arr1,array< array<type> > arr2)
    {
        long long int n1 = arr1.size(), n2 = arr2.size(), m1 = arr1[0].size(), m2=arr2[0].size();
        array< array<type> > re(n1);
        for(int i=0;i<n1;i++)
        re[i]=array<type>(m2);
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

    // Adding a constant to every element in Matrix
    template<typename type>
    array< array<type> > matrix_cons_add(array< array<type> > arr, type par)
    {
        long long int n1 = arr.size(), m1 = arr[0].size();
        array< array<type> > re(n1);
        for(int i=0;i<n1;i++)
        {
            re[i]=array<type>(m1);
            for(int j=0;j<m1;j++)
            {
                
                re[i][j]=arr[i][j]+par;
            }
        }
        return re;
    } 

    // Subtracting constant from every element of Matrix 
    template<typename type>
    array< array<type> > matrix_cons_sub(array< array<type> > arr, type par)
    {
        long long int n1 = arr.size(), m1 = arr[0].size();
        array< array<type> > re(n1);
        for(int i=0;i<n1;i++)
        {
            re[i]=array<type>(m1);
            for(int j=0;j<m1;j++)
            {
                re[i][j]=arr[i][j]-par;
            }
        }
        return re;
    }

    // Multiplying constant to every element of Matrix
    template<typename type>
    array< array<type> > matrix_cons_mul(array< array<type> > arr, type par)
    {
        long long int n1 = arr.size(), m1 = arr[0].size();
        array< array<type> > re(n1);
        for(int i=0;i<n1;i++)
        {
            re[i]=array<type>(m1);
            for(int j=0;j<m1;j++)
            {
                re[i][j]=arr[i][j]*par;
            }
        }
        return re;
    }

    // Dividing every element of Matrix by constant
    template<typename type>
    array< array<float> > matrix_cons_div(array< array<type> > arr, float par)
    {
        long long int n1 = arr.size(), m1 = arr[0].size();
        array< array<float> > re(n1);
        for(int i=0;i<n1;i++)
        {
            re[i]=array<float>(m1);
            for(int j=0;j<m1;j++)
            {
                re[i][j]=arr[i][j]/par;
            }
        }
        return re;
    }

    // reciprocal of every element in the matrix
    template<typename type>
    array< array<float> > matrix_oneby(array< array<type> > arr)
    {
        long long int n1 = arr.size(), m1 = arr[0].size();
        array< array<float> > re(n1);
        float temp=1;
        for(int i=0;i<n1;i++)
        {
            re[i]=array<float>(m1);
            for(int j=0;j<m1;j++)
            {
                re[i][j]=temp/arr[i][j];
            }
        }
        return re;
    }

    // get the transpose of Matrix
    template<typename type>
    array< array<type> > matrix_transpose(array< array<type> > arr)
    {
        long long int n1 = arr.size(), m1 = arr[0].size();
        array< array<type> > re(m1);
        for(int i=0;i<m1;i++)
        {
            re[i]=array<type>(n1);
            for(int j=0;j<n1;j++)
            {
                re[i][j]=arr[j][i];
            }
        }
        return re;
    }

    // get the submatrix by giving top-left and bottom-right indices
    template<typename type>
    array< array<type> > submatrix(array< array<type> > arr, long long int i1, long long int j1, long long int i2, long long int j2)
    {
        long long int n = i2-i1+1, m = j2-j1+1;
        array< array<type> > re(n);
        int k1=0,k2=0;
        for(int i=i1;i<=i2;i++)
        {
            re[k1]=array<type>(m);
            for(int j=j1;j<=j2;j++)
            {
                re[k1][k2]=arr[i][j];
                k2++;
            }
            k1++;
            k2=0;
        }
        return re;
    }

    // get the Matrix initialised with 0's
    array< array<int> > matrix_zeros(long long int n, long long int m)
    {
        array< array<int> > re(n);
        for(int i=0;i<n;i++)
        re[i]=array<int>(m);
        return re;
    }

    // get the Matrix initialised with 1's
    array< array<int> > matrix_ones(long long int n, long long int m)
    {
        array<int>a(m);
        for(int i=0;i<m;i++)
        a[i]=1;
        array< array<int> > re(n);
        for(int i=0;i<n;i++)
        re[i]=a;
        return re;
    }

    // get the Matrix where every element is raised to power
    template<typename type>
    array< array<type> > matrix_powerby(array< array<type> > arr, int par)
    {
        long long int n1 = arr.size(), m1 = arr[0].size();
        array< array<type> > re = matrix_ones(n1,m1);
        for(int i=1;i<=par;i++)
        {
            re = matrix_multwo(re,arr);
        }
        return re;
    }

    // get the Identity Matrix initialised with size
    array< array<int> > matrix_identity(long long int m)
    {
        array< array<int> > re(m);
        for(int i=0;i<m;i++)
        {
            re[i]=array<int>(m);
            for(int j=0;j<m;j++)
            {
                if(i==j)
                re[i][j]=1;
                else
                {
                    re[i][j]=0;
                }
                
            }
        }
        return re;
    }

    // calculating Co-factors where this is used to find determinant and adjoint of Matrix
    template<typename type>
    void getCofactor(array< array<type> > arr, array< array<type> > cotemp, int p, int q, long long int n)
    {
        int i = 0, j = 0;
        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < n; col++) 
            {
                if (row != p && col != q) 
                {
                    cotemp[i][j++] = arr[row][col];
                    if (j == n - 1) 
                    {
                        j = 0;
                        i++;
                    }
                }
            }
        }
    }

    // Calculates the determinant of matrix
    template<typename type>
    long long int matrix_det(array< array<type> > arr, long long int n)
    {
        long long int D = 0;
        if (n == 1)
        return arr[0][0];
        array<type>a(n);
        array< array<type> > cotemp(n);
        for(int i=0;i<n;i++)
        cotemp[i]=a;
        int sign = 1;
        for (int i = 0; i < n; i++) 
        {
            getCofactor(arr, cotemp, 0, i, n);
            D += sign * arr[0][i] * matrix_det(cotemp, n - 1);
            sign = -sign;
        }
        return D;
    }

    // gets the Adjoint Matrix
    template<typename type>
    array< array<type> > matrix_adjoint(array< array<type> >arr)
    {
        long long int N = arr.size(); 
        array< array<type> > adj(N);
        array<type>a(N);
        for(int i=0;i<N;i++)
        adj[i]=a;
        if (N == 1) 
        { 
            adj[0][0] = 1; 
            return adj; 
        } 
        int sign = 1; 
        array< array<type> > cotemp(N);
        for(int i=0;i<N;i++)
        cotemp[i]=a;
        for (int i=0; i<N; i++) 
        { 
            for (int j=0; j<N; j++) 
            { 
                getCofactor(arr, cotemp, i, j, N); 
                if((i+j)%2==0)
                sign=1;
                else
                sign=-1;
                adj[j][i] = (sign)*(matrix_det(cotemp, N-1)); 
            } 
        } 
        return adj;
    }

    // get the Inverse of a Matrix
    template<typename type>
    array< array<float> > matrix_inverse(array< array<type> > arr)
    {
        int N = arr.size(); 
        array< array<float> > re(N);
        array<float>a(N);
        for(int i=0;i<N;i++)
        {
            re[i]=a;
        }
        long long int det = matrix_det(arr, N); 
        if (det == 0) 
        { 
            return re; 
        } 
        array< array<type> > adj=matrix_adjoint(arr); 
        for (int i=0; i<N; i++) 
            for (int j=0; j<N; j++) 
                re[i][j] = adj[i][j]/float(det); 
        return re; 
    }

    // convert to upper triangular Matrix
    template<typename type>
    array< array<type> > matrix_upper(array< array<type> > arr)
    {
        long long int n = arr.size(), m = arr[0].size();
        array< array<type> >re(n);
        for(int i=0;i<n;i++)
        {
            re[i]=array<type>(m);
            for(int j=0;j<m;j++)
            {
                if(i>j)
                {
                    re[i][j]=0;
                }
                else
                {
                    re[i][j]=arr[i][j];
                }
            }
        }
        return re;
    }

    // convert to lower triangular matrix
    template<typename type>
    array< array<type> > matrix_lower(array< array<type> > arr)
    {
        long long int n = arr.size(), m = arr[0].size();
        array< array<type> >re(n);
        for(int i=0;i<n;i++)
        {
            re[i]=array<type>(m);
            for(int j=0;j<m;j++)
            {
                if(j>i)
                {
                    re[i][j]=0;
                }
                else
                {
                    re[i][j]=arr[i][j];
                }
            }
        }
        return re;
    }

}
#endif //DSALGLIB_MATRIX_H
