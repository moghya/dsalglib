#include <iostream>
#include <cstdlib>
#include <list>
#include "disjoint.h"

int main()
{
        node a;
        node b;
        node c;

        std::cout << "\na: " << &a;
        std::cout << "\nb: " << &b;
        std::cout << "\nc: " << &c;

        MakeSet(a);
        MakeSet(B)/>;
        MakeSet(c);

        std::cout << "\n\na after MakeSet: " << a.parent;
        std::cout << "\nb after MakeSet: " << b.parent;
        std::cout << "\nc after MakeSet: " << c.parent;

        Union(a, B)/>;
//      Union(b, c);

        std::cout << "\n\na after Union: " << a.parent;
        std::cout << "\nb after Union: " << b.parent;
        std::cout << "\nc after Union: " << c.parent;

        std::cout << "\n\n";

        return EXIT_SUCCESS;
}
