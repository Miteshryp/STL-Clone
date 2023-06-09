#include"memory/memory_block.hpp"
#include"iterator.hpp"

#define PX_MIN_STACK_CAPACITY 10

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
      m_block(PX_MIN_STACK_CAPACITY)
   {
      // m_arr = (ptr_type)m_block.m_arr;
   }

   stack(const stack_reference_type s) 
      :
      m_size(s.m_size), 
      m_block(s.m_block)
   {
   }

   stack(stack_type&& rval)
      :
      m_size(rval.m_size),
      m_block(std::move(rvalue.m_block))
   {
   }


   stack(int allocation_capacity)
      :
      m_size(0), 
      m_block(allocation_capacity)
   {
   }

   ~stack()
   {
      m_block->release_memory();
   }


// -----------------------
// |    Methods
// -----------------------

// Modifiers

   void push(const reference_type element) {
      if(m_size == m_block.m_capacity) {
         // reallocate block
         m_block.increase_capacity();
      }

      m_arr[m_size++] = element;
   }

   void push(value_type&& element) {
      if(m_size == m_block.m_capacity) {
         // reallocate block
         m_block.increase_capacity();
      }

      m_arr[m_size++] = (value_type&&)element;
   }

   value_type pop() {
      return m_arr[--m_size];
   }



// Informatics

   int size() const {
      return m_size; 
   }
   int capacity() const { 
      // return m_block.m_capacity;
      return m_block.getCapacity(); 
   }

   bool empty() const { 
      return m_size == 0; 
   }

   bool contains(const reference_type item) {
      for(iterator i = this->begin(); i != this->end(); i++) {
         if(*i == item) return true;     
      }
      return false;
   }



// Access Methods

   T top() const {
      // return m_arr[m_size - 1];
      return m_block->getData[m_size - 1];
   }





// Iterator functions

   iterator begin() {
      // return iterator(&m_arr[0]);
      return iterator(m_block->getData());
   }

   iterator end() {
      // return iterator(&m_arr[m_size]);
      return iterator(m_block->getData() + m_size);
   }

public:
   void operator = (stack_type s) {
      m_block = s.m_block;
      // m_arr = m_block.getData();
      m_size = s.m_size;

      // // Allocate a new block if current capacity is inadequate
      // if(m_block.m_capacity < s.m_size) {
      //    // Free memory if valid
      //    if(m_arr) free_memory_block(m_block);

      //    // Get new memory block of desired size
      //    m_size = s.m_size;
      //    m_block = get_memory_block(sizeof(value_type), m_size);
      //    m_arr = (ptr_type)(m_block.m_arr);
      // }

      // else {
      //    m_size = s.m_size;
      // }

      // memcpy(m_arr, s.m_block.m_arr, sizeof(value_type)*m_size);
   }




// Data members
private:
   int m_size;
   // ptr_type m_arr;
   MemoryBlock<T> m_block;

};

}
