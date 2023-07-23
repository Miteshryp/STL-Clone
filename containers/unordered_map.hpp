#pragma once
#include "containers/pair.hpp"
#include "containers/vector.hpp"
#include "containers/list.hpp"

namespace pixel
{

  template <typename Key_Type, typename Value_Type>
  class HashTable
  {
    using Bucket = pixel::list<pixel::pair<Key_Type, Value_Type>>;
    using BucketStore = pixel::vector<Bucket>;

    HashTable(uint32 initial_bucket_size = 5)
      : 
      m_store()
    {
      m_store.reserve(initial_bucket_size);
    }

    uint32 getHashIndex(size_t hash) const
    {
      return hash % m_store.size();
    }

    uint32 load_factor() const
    {
    }

    uint32 max_load_factor() const
    {
      return max_load_factor;
    }

  protected:
    BucketStore m_store;
    uint32 m_max_load_factor;
  };

  template <typename Key_Type, typename Value_Type>
  class unordered_map
  {

  private:
    HashTable<Key_Type, Value_Type> m_table;
  };

}
