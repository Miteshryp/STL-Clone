#include"containers/memory/memory_block.hpp"
#include"containers/utils/iterator.hpp"

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
   {}

   stack(const stack_reference_type s) 
      :
      m_size(s.m_size), 
      m_block(s.m_block)
   {}

   stack(stack_type&& rval)
      :
      m_size(rval.m_size),
      m_block(std::move(rval.m_block))
   {}


   stack(int allocation_capacity)
      :
      m_size(0), 
      m_block(allocation_capacity)
   {}

   ~stack()
   {
      // Deep clean
      for(ptr_type element = m_block.getData(); element != m_block.getData() + m_size; element++)
         element->~value_type();
   }


// -----------------------
// |    Methods
// -----------------------

// Modifiers

   /**
    * @brief Pushes the element to the top of the stack
    * @param element 
    */
   void push(const reference_type element) {
      if(m_size == m_block.m_capacity) {
         // reallocate block
         m_block.increase_capacity();
      }

      m_block.getData()[m_size++] = element;
   }
   void push(value_type&& element) {

      if(m_size == m_block.m_capacity) {
         m_block.increase_capacity(); // reallocate block
      }

      m_block.getData()[m_size++] = (value_type&&)element;
   }


   /**
    * @brief Used to remove the top-most element in the stack.
    * @return value_type 
    */
   value_type pop() {
      return m_block.getData()[--m_size];
   }



// Informatics

   /**
    * @brief Returns the current size of the stack
    * 
    * @return Size of the stack
    */
   int size() const {
      return m_size; 
   }


   /**
    * @brief Returns the current capacity of the stack.
    * The capacity of the stack will be the sum of current
    * elements and excess space in the stack
    * 
    * @return Number of elements which can be stored in the stack
    */
   int capacity() const { 
      return m_block.getCapacity(); 
   }


   /**
    * @brief Used to check if the stack is empty (no elements in the stack)
    * 
    * @return true if the stack is empty,
    * @return false otherwise
    */
   bool empty() const { 
      return m_size == 0; 
   }

   /**
    * @brief Used to check if an element exists in the stack
    * @param item element to be searched in the stack
    * 
    * @return true if the element exists, 
    * @return false otherwise
    */
   bool contains(const reference_type item) {
      for(iterator i = this->begin(); i != this->end(); i++) {
         if(*i == item) return true;     
      }
      return false;
   }



// Access Methods

   /**
    * @brief Returns a const reference to the top-most element 
    * in the stack
    * 
    * @returns constant reference to the top element 
    */
   const reference_type top() const {
      return static_cast<const reference_type>(m_block.getData()[m_size - 1]);
   }





// Iterator functions

   iterator begin() {
      return iterator(m_block.getData());
   }

   iterator end() {
      return iterator(m_block.getData() + m_size);
   }

public:
   void operator = (stack_type s) {
      m_block = s.m_block;
      m_size = s.m_size;
   }




// Data members
private:
   int m_size;
   // ptr_type m_arr;
   memory_block<T> m_block;

};

}
