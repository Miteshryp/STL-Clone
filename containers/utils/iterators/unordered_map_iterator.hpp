#pragma once
#include "containers/utils/types.hpp"

#include "containers/pair.hpp"
#include "containers/list.hpp"
#include "containers/vector.hpp"



#include <functional>

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
    iterator operator ++ (int) {
        iterator ret = *this;
        m_list_iterator++;
        return ret;
    }





    /**
     * @brief Returns whether the iterators are EQUAL or not
     * 
     * @param iter 
     * @return true if the iterators are equal,
     * @return false otherwise
     */
    bool operator == (const_iterator_reference iter) const {
        return m_list_iterator == iter.m_list_iterator;
    }

    /**
     * @brief Returns whether the 2 iterators are UNEQUAL or not
     * 
     * @param iter 
     * @return true if iterators are not equal,
     * @return false otherwise
     */
    bool operator != (const_iterator_reference iter) const {
        return !(*this == iter);
    }

    /**
     * @brief Returns a reference to the pair stored in the bucket iterator
     * 
     * @return reference of pair type 
     */
    pair_reference_type operator * () {
        return *m_list_iterator;
    }

private:
    BucketIterator m_list_iterator;
    BucketStoreIterator m_bucket_iterator;
};

}