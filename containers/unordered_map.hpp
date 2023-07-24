#pragma once
#include "containers/pair.hpp"
#include "containers/vector.hpp"
#include "containers/list.hpp"


#define PX_DEFAULT_LOAD_FACTOR 0.75f

namespace pixel {

using namespace pixel::types;



template <typename Key_Type, typename Value_Type>
class HashTable
{
  using Bucket = pixel::list<pixel::pair<Key_Type, Value_Type>>;
  using BucketStore = pixel::vector<Bucket>;

  // Type references
  using value_type = Value_Type;
  using value_reference_type = Value_Type&;
  using const_value_reference_type = Value_Type const&;
  using value_ptr_type = Value_Type*;
  
  using key_type = Key_Type;
  using key_reference_type = Key_Type&;
  using const_key_reference_type = Key_Type const&;
  using const_key_Rvalue_type = Key_Type&&;
  using key_ptr_type = Key_Type*;

public:
  
  HashTable(uint32 initial_bucket_size = 5)
    : 
    m_store()
  {
    m_store.reserve(initial_bucket_size);
  }

  
  /**
   * @brief Get the Hash Index object
   * 
   * @param hash hash value
   * @return index of bucket containing the hash
   */
  uint32 getHashIndex(size_t hash) const
  {
    return hash % m_store.size();
  }


  /**
   * @brief Returns the load factor of the current hash table state
   * 
   * @return load factor of the hash table 
   */
  float32 load_factor() const
  {
    // load factor = size of each bucket / no of buckets in hash table
    uint32 bucket_size = 0;
    for(uint32 i = 0; i < m_store.size(); i++) {
      bucket_size += m_store[i].size();
    }
    return (float32)bucket_size / m_store.size(); 
  }


  /**
   * @brief Returns the threshold value of load factor, 
   * after which the hash table needs to be remapped
   * 
   * @return maximum load factor 
   */
  float32 max_load_factor() const
  {
    return m_max_load_factor;
  }

  /**
   * @brief Set the new max load factor for the 
   * hashtable instance. Once the load factor crosses
   * this threshold, the hash table is rem
   * 
   * @param new_max_load_factor new value of the max load factor
   */
  void set_max_load_factor(float32 new_max_load_factor) {
    m_max_load_factor = new_max_load_factor;
  }


  value_reference_type operator [] (key_type key) {

  }

// Data members
protected:
  BucketStore m_store;
  float32 m_max_load_factor = PX_DEFAULT_LOAD_FACTOR;
};




template <typename Key_Type, typename Value_Type>
class unordered_map
{
  using key_type = Key_Type;
  using key_reference_type = Key_Type&;
  using const_key_reference_type = Key_Type const&;
  using const_key_Rvalue_type = Key_Type&&;

  using key_ptr_type = Key_Type*;
  using value_type = Value_Type;
  using value_reference_type = Value_Type&;
  using const_value_reference_type = Value_Type const&;
  using value_ptr_type = Value_Type*;
  
  using pair_type = pair<Key_Type, Value_Type>;
  using pair_reference_type = pair<Key_Type, Value_Type>&;
  using const_pair_reference = pair<Key_Type, Value_Type> const&;
  using pair_ptr_type = pair<Key_Type, Value_Type>*;

  using umap_type = unordered_map<Key_Type, Value_Type>;
  using umap_ptr_type = unordered_map<Key_Type, Value_Type>*;
  using umap_reference_type = unordered_map<Key_Type, Value_Type>&;
  using umap_rval_type = unordered_map<Key_Type, Value_Type> &&;

  using bucket_type = pixel::list<pixel::pair<Key_Type, Value_Type>>;
  using const_bucket_reference_type = pixel::list<pixel::pair<Key_Type, Value_Type>> const&;
public:
  
  unordered_map()
  {
    // @todo: implement
  }

  unordered_map(const umap_reference_type map)
  {
    // @todo: implement
  }

  unordered_map(umap_rval_type ref)
  {
    // @todo: implement
  }
  
  // @todo: implement initialiser map constructor

public:

  /**
   * @brief Inserts a new key value into the unordered_map
   * 
   * @param key key used to reference the value
   * @param value value to be stored
   */
  void insert(const_pair_reference pair) {
    // @todo: implement
  }
  void insert(key_reference_type key, value_reference_type value) {
    // @todo: implement
  }

  /**
   * @brief Clears all the elements in the 
   * hash table
   * 
   */
  void clear() {
    // @todo: implement
  }


  void erase(const_key_reference_type key) {
    // @todo: implement
  }


  const_value_reference_type at(const_key_reference_type key) const {
    // @todo: implement
  }


  // @todo: define find function, which returns a hashtable 
  //        iterator to the element


  /**
   * @brief Set the max load factor of the hash table
   * 
   * @param new_max_load_factor 
   * the new value of maximum load factor of the 
   * unordered_map
   */
  void set_max_load_factor(float32 new_max_load_factor) {
    m_table.set_max_load_factor(new_max_load_factor);
  }

  /**
   * @brief Reserves buckets to store at least the min
   * number of key-value pairs
   * 
   */
  void reserve(uint32 element_count) {
    // @todo: implement
  }


  /**
   * @brief Returns the current size of the 
   * unordered_map
   * 
   * @return size of the container 
   */
  uint32 size() const {
    // @todo: implement
  }

  /**
   * @brief Returns the maximum size of the 
   * unordered_map before a rehash is required
   * 
   * @return max size of the container before rehash
   */
  uint32 max_size() const {
    // @todo: implement
  }

  /**
   * @brief Returns the number of buckets currently 
   * used in the hash table
   * 
   * @return number of buckets used
   */
  uint32 bucket_size() const {
    // @todo: implement
  }

  const_bucket_reference_type bucket(const_key_reference_type key) const {
    // @todo: implement
  }

  /**
   * @brief Returns the current load factor
   * of the hashmap
   * 
   * @return current load factor of the container 
   */
  float32 load_factor() const {
    return m_table.load_factor();
  }

  /**
   * @brief Returns the maximum threshold of 
   * load factor in this instance of unordered_map
   * Beyond this value of load factor, the unordered_map
   * will need to be hashed again to acquire an optimal
   * access pattern.
   * 
   * @return maximum load factor threshold
   */
  float32 max_load_factor() const {
    return m_table.max_load_factor();
  }

  /**
   * @brief Returns whether the unordered_map 
   * instance is empty or not
   * 
   * @return true if empty, 
   * @return false otherwise 
   */
  bool empty() const {
    // @todo: implement
  }

  /**
   * @brief Tells the user whether a given key is
   * inserted in the hashtable
   * 
   * @param key 
   * @return true if key is inserted,
   * @return false otherwise
   */
  bool contains(const_key_reference_type key) const {
    // @todo: implement
  }

public:
  // @todo: begin method: returns iterator to the first
  //        element of the unordered_map

  // @todo: end method: returns iterator to the last
  //        element of the unordered_map

public:
  value_reference_type operator [] (Key_Type key) {
    // @todo: implement
  }
  
// Data members
private:
  HashTable<Key_Type, Value_Type> m_table;
};

}
