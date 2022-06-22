#include"reallocater.hpp"
#include"iterator.hpp"

#define MIN_STACK_CAPACITY 10

namespace pixel {

template<typename T>
class stack { 

   using ptr_type = T*;
   using value_type = T;
   using reference_type = T&;

   using iterator = BasicIterator<T>;

public:
   stack()
      :
      m_size(0),
      m_block(get_memory_block(sizeof(T), MIN_STACK_CAPACITY))
   {
      m_arr = (ptr_type)m_block.m_arr;
   }

   stack(int allocation_capacity)
      :
      m_size(0), 
      m_block(get_memory_block(sizeof(T), allocation_capacity))
   {
      m_arr = (ptr_type)(m_block.m_arr);
   }

   ~stack()
   {
      free_memory_block(m_block);
      m_arr = nullptr;
   }


// -----------------------
// |    Methods
// -----------------------

// Essentials
   void push(const T& element) {
      if(m_size == m_block.m_capacity) {
         // reallocate block
         this->reallocate_capacity();
      }

      m_arr[m_size++] = element;
   }

   T pop() {
      return m_arr[--m_size];
   }

   T top() const {
      return m_arr[m_size - 1];
   }

   int size() const { return m_size; }

// Essential Function



// Helper Functions
   bool contains(const reference_type item) {
      for(iterator i = this->begin(); i != this->end(); i++) {
         if(*i == item) return true;     
      }
      return false;
   }


// Iterator functions
   iterator begin() {
      return iterator(&m_arr[0]);
   }

   iterator end() {
      return iterator(&m_arr[m_size]);
   }

   // Iterator - begin, end

private:
   bool reallocate_capacity() {
      m_block = pixel_push_capacity(m_arr, sizeof(T), m_size, m_block.m_capacity);
      if(m_block.m_arr == nullptr) return false;
      m_arr = (T*)(m_block.m_arr);

      return true;
   }

private:

   ptr_type m_arr;
   int m_size;
   PixelAllocation m_block;
};

}
