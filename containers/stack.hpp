#include"reallocater.hpp"
#include"iterator.hpp"

#include<iostream>

#define MIN_STACK_CAPACITY 10

namespace pixel {

template<typename T>
class stack { 

   using ptr_type = T*;
   using value_type = T;
   using reference_type = T&;

   using stack_type = stack<T>;
   using stack_reference_type = stack<T>&;
   using stack_Rreference_type = stack<T>&&;
   using stack_ptr_type = stack<T>*;

   using iterator = BasicIterator<T>;

public:
   stack()
      :
      m_size(0),
      m_block(get_memory_block(sizeof(T), MIN_STACK_CAPACITY))
   {
      std::cout << "NOR" << std::endl;
      m_arr = (ptr_type)m_block.m_arr;
   }

   stack(const stack_reference_type s) 
      :
      m_size(s.m_size), 
      m_block(s.m_block)
   {
      std::cout << "REF" << std::endl;
      m_arr = (ptr_type)(m_block.m_arr);
   }

   stack(stack_type&& rval)
   {
      std::cout << "RVAL" << std::endl;
      // m_block = PixelMemoryBlock(&&(rval.m_block))
   }


   stack(int allocation_capacity)
      :
      m_size(0), 
      m_block(get_memory_block(sizeof(T), allocation_capacity))
   {
      std::cout << "ALO" << std::endl;
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

public:
   void operator = (stack_type s) {
      // Free memory if valid
      if(m_arr) free_memory_block(m_block);

      // Reset memory and 
      m_size = s.m_size;
      m_block = get_memory_block(sizeof(value_type), m_size); // not occup
      m_arr = (ptr_type)(m_block.m_arr);

      memcpy(m_arr, s.m_block.m_arr, sizeof(value_type)*m_size);
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
   PixelMemoryBlock m_block;
};

}
