
//
// Created by omjego
//

#ifndef DSALGLIB_BITREE_H
#define DSALGLIB_BITREE_H

#include<vector>
using namespace std;
namespace dsa
{
    /*
    * type must be an integer data type.
    * For more information on Binary Indexed Trees(Fenwick Trees) refer to this
    * video : https://www.youtube.com/watch?v=kPaJfAUwViY
    */
    template<class type>
    class bitree
    {
        private:
            vector<type> vec;

        public:
            void init(int n) {
                vec.assign(n, 0);
            }

            void add(int i, type val) {
                while( i < vec.size()) {

                    vec[i] += val;
                    // Expression (i & -i) gives value of 2^(index of LSB in i)
                    i += (i&-i);

                }
            }

            type sum(int i) {

                type ans = 0;
                while(i > 0) {
                    ans += vec[i];
                    i -= (i & -i);
                }

                return ans;
            }

            type sum(int left, int right) {
                return sum(right) - sum(left - 1);
            }

            int size() {
                return vec.size();
            }

            void reset() {
                vec.fill(0);
            }
    };
}

#endif //DSALGLIB_BSTREE_H


