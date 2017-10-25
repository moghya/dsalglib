//
// Created by omjego
//

#ifndef DSALGLIB_HASHMAP_H
#define DSALGLIB_HASHMAP_H
#include "array.h"
#include "linklist.h"
using namespace dsa;

namespace dsa
{

    template<class K, class V>
    class KeyValue
    {
    private:
        K _key;
        V _value;
    public:
        KeyValue()
        {
            _key = K();
            _value = V();
        }
        KeyValue(const K _key,const V _value):_key(_key), _value(_value) {
        }

        bool operator = (KeyValue & other)
        {
            return other._key == _key;
        }

        K & getKey() {
            return _key;
        }

        V & getValue() {
            return _value;
        }

        void setValue(V val) {
            _value = val;
        }
    };


    //This class provides default hash method for the given type
    template<class K, unsigned int tableSize>
    class HashClass
    {
        unsigned long long operator()(const K & key) const
        {
            return (key % tableSize);
        }
    };


    template<class K, class V, unsigned int tableSize, typename H =  HashClass<K,tableSize> >
    class HashMap
    {
    private:
        array<linklist<KeyValue<K, V> > > _table;
        H _hash;
        int size;
    public:
        HashMap():size(0)
        {
            _table = array<linklist<KeyValue<K, V> > >(tableSize, linklist<KeyValue<K, V> >());

        }

        ~HashMap()
        {
            for(int i = 0; i < tableSize; ++i ) {
                _table[i].freeList();
            }

            _table.~array();
        }


        //If found returns true and corresponding value in V.
        bool get(K & key, V & value)
        {
            unsigned long long int hashVal = _hash(key);

            if(hashVal >= tableSize || hashVal < 0)
            {
                throw "Invalid hash index: Make sure your hash function returns value between [0,tableSize - 1]";
            }

            int index = _table[hashVal].search(key);
            if(index < 0) {
                return false;
            }

            return true;
        }

        //returns true if new element is added otherwise false if already existing element is overwritten
        bool put(K & key, V & value)
        {
            unsigned long long int hashVal = _hash(key);

            if(hashVal >= tableSize || hashVal < 0)
            {
                throw "Invalid hash index: Make sure your hash function returns value between [0,tableSize - 1]";
            }

            int index = _table[hashVal].search(key);
            if(index < 0) {
                _table[hashVal].add_front(index);
                ++size;
                return true;
            } else {
                KeyValue<K, V> newData(key, value);
                _table[hashVal].update(index, newData);
                return false;
            }
        }

        bool remove(K & key)
        {
            unsigned long long int hashVal = _hash(key);

            if(hashVal >= tableSize || hashVal < 0)
            {
                throw "Invalid hash index: Make sure your hash function returns value between [0,tableSize - 1]";
            }
            int index = _table[hashVal].search(key);
            if(index < 0) {
                return false;
            } else {
                _table[hashVal].remove_at(index);
                return false;
            }
        }
    };
}

#endif //DSALGLIB_HASHMAP_H

