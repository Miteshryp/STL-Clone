#pragma once
#include "containers/utils/types.hpp"

#include "containers/pair.hpp"
#include "containers/list.hpp"
#include "containers/vector.hpp"

// hashtable iterator -> list iterator + vector iterator
namespace pixel {
using namespace pixel::types;


template<typename Key_Type,typename Value_Type>
class HashTableIterator {
    using iterator = HashTableIterator<Key_Type, Value_Type>;
    using iterator_reference = HashTableIterator<Key_Type, Value_Type>&;
    using const_iterator_reference = HashTableIterator<Key_Type, Value_Type> const&;

    using pair_type = pixel::pair<Key_Type, Value_Type>;
    using pair_reference_type = pixel::pair<Key_Type, Value_Type>&;

    using BucketStoreIterator = pixel::vector< pixel::list<pixel::pair<Key_Type, Value_Type>> >::iterator;
    using BucketIterator = pixel::list<pixel::pair<Key_Type, Value_Type>>::iterator;

    // using BucketIterator = Bucket::iterator;
    // using BucketStoreIterator = BucketStore::iterator;
public:
    
    // prefix operator
    iterator operator ++ () {
        m_list_iterator++;
        return *this;
    }
    
    // postfix operator
    void operator ++ (int) {
        iterator ret = *this;
        m_list_iterator++;
    }
    void operator -- () {}
    void operator -- (int) {}

    bool operator == (const_iterator_reference iter) const {

    }

    bool operator != (const_iterator_reference iter) const {

    }


    pair_reference_type operator * () {
        return *m_list_iterator;
    }

private:
    BucketIterator m_list_iterator;
    BucketStoreIterator m_bucket_iterator;
};

}