//
// Created by omjego
//

#ifndef DSALGLIB_DSU_H
#define DSALGLIB_DSU_H

#include "array.h"
using namespace dsa;

namespace dsa
{
    template<typename type>
    class DSU
    {
    private:
        array<int> index;
    public:
        DSU(int _size)
        {
            index = array(_size, 0);
            for(int i = 0; i < _size; ++i) {
                index[i] = i;
            }
        }

        ~DSU()
        {
            index.~array();
        }

        int root(int node)
        {
            int tmp = node;
            while(node != index[node]) {
                node = index[node];
            }

            //Path compression to make subsequent root searches efficient.
            while(tmp != index[tmp]) {
                int parent = index[tmp];
                index[tmp] = node;
                tmp = parent;
            }
            return node;
        }

        bool areInTheSameGroup(int u, int v) {
            return root(u) == root(v);
        }

        void dsu_union(int u, int v) {

            int root_1 = root(u);
            int root_2 = root(v);

            //Append one tree to another
            index[root_1] = root_2;

        }

        int getSize() {
            return index.size();
        }
    };
}
#endif //DSALGLIB_DSU_H

