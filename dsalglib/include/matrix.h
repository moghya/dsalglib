//
// Created by moghya_s on 12/26/2016.
//

#ifndef DSALGLIB_MATRIX_H
#define DSALGLIB_MATRIX_H
namespace dsa
{
    template<class type>
    class matrix {
        private:
            array<type> elements;
            long int nColumns;
            long int nRows;
            long long int totalEntries;
        public:
            matrix(long long int rows, long long int cols)
            {
                nRows = rows;
                nColumns = cols;
                totalEntries = cols * rows;
                elements = array<type>(totalEntries);
            }

            // using 0 indexed entries, not mathematical convention of 1 indexed
            type getElement(long int row, long int col) {
                long long int i = nRows * col + row;
                return elements[i];
            }
            type setElement(long int row, long int col, type value) {
                long long int i = nRows * col + row;
                elements[i] = value;
            }

            void operator=(matrix<type> from) {
                nColumns = from.nColumns;
                nRows = from.nRows;
                totalEntries = from.totalEntries;
                elements = from.elements;
            }

            void operator+=(matrix<type> rhs) {
                if (nColumns == rhs.nColumns && nRows == rhs.nRows) {
                    long long int i;
                    for (i = 0; i < totalEntries; i++) {
                        elements[i] += rhs.elements[i];
                    }
                }
            }

            void operator-=(matrix<type> rhs) {
                if (nColumns == rhs.nColumns && nRows == rhs.nRows) {
                    long long int i;
                    for (i = 0; i < totalEntries; i++) {
                        elements[i] -= rhs.elements[i];
                    }
                }
            }

            void operator*=(type rhs) {
                long long int i;
                for (i = 0; i < totalEntries; i++) {
                    elements[i] *= rhs;
                }
            }

            matrix<type> operator*(matrix<type> rhs) {
                if (nColumns == rhs.nRows) {
                    matrix<type> ret = matrix(nRows, rhs.nColumns);
                    long long int i,j,k;
                    for (i = 0; i < nRows; i++) {
                        for (j = 0; j < rhs.nColumns; j++) {
                            type entry = getElement(i,0) * rhs.getElement(0,j);
                            for (k = 1; i < nColumns; k++) {
                                entry += getElement(i,k) * rhs.getElement(k,j);
                            }
                            ret.setElement(i,j,entry);
                        }
                    }
                    return ret;
                }
            }
    };
}

#endif //DSALGLIB_MATRIX_H
