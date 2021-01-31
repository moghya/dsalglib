//
// Created by moghya_s on 12/25/2016.
//

#ifndef DSALGLIB_TESTS_H
#define DSALGLIB_TESTS_H
#include <iostream>
#include "dsalglib.h"
#include "sample.h"

#define ASSERT(cond) if (!(cond))\
    throw ("Assertion failed at " __FILE__ ":" STR(__LINE__));

using namespace std;
using namespace dsa;


void kmpsearchTest()
{
    array<int> a,b;
    a.push_back(5);


    b.push_back(5);
    b.push_back(2);
    b.push_back(5);
    b.push_back(2);
    b.push_back(5);
    b.push_back(2);
    b.push_back(1);
    b.push_back(5);
    b.push_back(2);
    b.push_back(5);
    b.push_back(2);
    b.push_back(1);

    kmpsearch(b,a).traverse(print);
}

void maxheapTest()
{
    maxheap<int> b;
    cout<<b.size();
    b.insert(14);
    b.insert(15);
    b.insert(5);
    b.insert(13);
    b.insert(6);
    b.insert(11);
    b.insert(1);
    b.insert(12);
    b.insert(7);
    b.insert(8);
    b.insert(9);
    b.insert(10);
    b.insert(16);
    while (b.size()!=0)
    {
        cout<<b.popmax()<<" ";
    }
}

void avltreeTest()
{
    avltree<int> b;
    b.insert(5);
    b.insert(6);
    b.insert(7);
    b.insert(8);
    b.insert(9);
    b.insert(10);
    b.insert(11);
    b.insert(1);
    b.insert(12);
    b.insert(13);
    b.insert(14);
    b.insert(15);
    b.insert(16);
    //cout<<b.find_max();
    //b.levelorder(print);
    cout<<b.height();
    b.remove(b.find_max());
    cout<<b.height();
    b.remove(b.find_min());
    cout<<b.height();
}

void bstreeTest()
{
    bstree<long long int> b;
    b.insert(5);
    b.insert(6);
    b.insert(7);
    b.insert(8);
    b.insert(9);
    b.insert(10);
    b.insert(11);
    //cout<<b.find_max();
    //b.levelorder(print);
    cout<<b.height();


}

void stackTest()
{
    dsa::stack<int> s;
    cout<<s.size();
    s.push(10);
    cout<<s.pop();
    s.push(5);
    cout<<s.top_element();
    s.clear();
    cout<<s.size();


}

void arrayTest()
{
    array<int> a;
    array<int> b;
    a.push_back(5);
    a.push_back(2);
    a.push_back(9);
    a.push_back(1);
    a.push_back(7);
    a.push_back(21);
    bubblesort(a,a.size());
    a.traverse(print);
    a[2]=a[5]+1;
    cout<<a[2];

    a.reverse(0,a.size()-1);
    b=a;
    a.clear();
    a.traverse(print);

    b.traverse(print);
    cout<<a.size();
    return ;
}

void linklistTest()
{
    linklist<char> l;
    l.add_back('a');
    l.add_back('b');
    l.add_back('c');
    l.add_back('d');
    l.add_front('e');
    l.traverse(print);
    l.remove('d');
    l.traverse(print);
    l.remove_at(2);
    l.traverse(print);
    return ;
}

void queueTest()
{
    dsa::queue<int> q;
    cout<<q.size();
    q.enqueue(5);
    q.enqueue(6);
    q.enqueue(7);
    cout<<q.front_element();
    while (q.size()!=0)
    {
        cout<<q.dequeue()<<" ";

    }
    cout<<q.isempty();
    cout<<q.rear_element();

}

void sortTest()
{
    array<int> a;
    a.push_back(5);
    a.push_back(2);
    a.push_back(9);
    a.push_back(1);
    a.push_back(7);
    a.push_back(21);
    bubblesort(a,a.size());
    a.traverse(print);
    a.clear();
    a.push_back(5);
    a.push_back(2);
    a.push_back(9);
    a.push_back(1);
    a.push_back(7);
    a.push_back(21);
    heapsort(a);
    a.traverse(print);
    a.clear();
    a.push_back(5);
    a.push_back(2);
    a.push_back(9);
    a.push_back(1);
    a.push_back(7);
    a.push_back(21);
    quicksort(a,0,a.size()-1);
    a.traverse(print);
    a.clear();
    a.push_back(5);
    a.push_back(2);
    a.push_back(9);
    a.push_back(1);
    a.push_back(7);
    a.push_back(21);
    insertionsort(a,a.size());
    a.traverse(print);
    a.clear();
    a.push_back(5);
    a.push_back(2);
    a.push_back(9);
    a.push_back(1);
    a.push_back(7);
    a.push_back(21);
    mergesort(a,a.size(),0,a.size()-1);
    a.traverse(print);
    a.clear();
    a.push_back(5);
    a.push_back(2);
    a.push_back(9);
    a.push_back(1);
    a.push_back(7);
    a.push_back(21);
    shellsort(a,a.size());
    a.traverse(print);
    a.clear();
    a.push_back(5);
    a.push_back(2);
    a.push_back(9);
    a.push_back(1);
    a.push_back(7);
    a.push_back(21);
    selectionsort(a,a.size());
    a.traverse(print);

}

void trie_test(){
    trie t;
    t.insert("first");
    t.insert("second");
    cout << t.search("first") << "\n";
    cout << t.search("firs") << "\n";
    cout << t.search("second") << "\n";
    cout << t.search("third") << "\n";
}

void reversalTreeTest() {
    const int numbers[] = {2, 3, 4, 5, 6, 7, 8};
    const int n = sizeof(numbers) / sizeof(int);
    ReversalTree<int> tree(numbers, numbers + n);
    ASSERT(tree.at(0) == 2);
    ASSERT(tree.at(5) == 7);

    tree.reverse(2, 5);
    tree.reverse(0, 4);
    {
        const int expected[] = {5, 6, 3, 2, 4, 7, 8};
        ASSERT(tree.size() == n);
        auto it = tree.cbegin();
        for (int i = 0; i < n; ++i, ++it) {
            ASSERT(*it == expected[i]);
        }
        ASSERT(it == tree.cend());
    }

    tree.erase(--tree.end());
    tree.insert(tree.begin(), 1);
    ASSERT(tree.front() == 1);
    ASSERT(tree.back() == 7);
    ASSERT(tree.size() == n);
    // {1, 5, 6, 3, 2, 4, 7}

    ReversalTree<int>::iterator mid = advance(tree.begin(), n / 2);
    ReversalTree<int> other = tree.split(mid);
    other.merge(rvalue_cast(tree));
    {
        const int expected[] = {3, 2, 4, 7, 1, 5, 6};
        ASSERT(other.size() == n);
        auto it = other.cbegin();
        for (int i = 0; i < n; ++i, ++it) {
            ASSERT(*it == expected[i]);
        }
    }
    ASSERT(tree.empty());
    tree.clear();
}

#endif //DSALGLIB_TESTS_H
