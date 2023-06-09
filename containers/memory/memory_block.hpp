#include<cstdlib>
#include<cassert>
#include<memory.h>

#include "utils/types.hpp"

#define PX_MEMBLOCK_DOUBLE_LIMIT 100
#define PX_MEMBLOCK_HALF_LIMIT 400

namespace pixel {

   /**
    * @note
    * Removed the support for running the destructor to properly deallocate the block elements
    * This is because when we create the memory block, we wont be able to create a memory block
    * for types with a deleted default constructor with new. (We are able to allocate the memory using malloc)
    * This forced me create the memory using malloc, which does not run the constructor by default.
    * It is hence the responsibility of the wrapper class to properly run the constructor and 
    * deallocate the resources before freeing the memory block.
    * Hence, running the destructor on unused capacity can cause issues.
    * The MemoryBlock structure is only a representative of memory block allocated on the heap
   */





   /**
    * @brief A structure representing a block of memory allocated by a pixel container.
    * 
    * @details The memory block contains the memory block allocated on the heap memory. 
    * It also contains methods to manage shallow and deep copies across memory blocks 
    * in pixel.
    * This structure is just a memory space for the T type. It does not call the 
    * constructor or destructor of T
    * 
    * @todo Proper Testing
    */
   template<typename T>
   class MemoryBlock {
      typedef void* data_handle;
      typedef T value_type;
      typedef T* pointer_type;

   public:

      MemoryBlock() = delete;


      /**
       * @brief Construct a new Pixel Memory Block object, which allocates a memory block 
       * capable of storing CAPACITY elements of type T
       * 
       * @param capacity Capacity of the memory block (Count of element of type T)
       */
      MemoryBlock(uint32 capacity = s_default_block_capacity) 
      {
         m_arr = (data_handle)malloc(capacity * sizeof(T));
         m_allocated = capacity * sizeof(T);
      }


      /**
       * @brief Copy Contructor
       * @param block 
       */
      MemoryBlock(const MemoryBlock<T>& block) 
      {
         // Deep Copy
         m_allocated = block.m_allocated;
         m_arr = malloc(m_allocated);

         // Deep copy
         pointer_type arr_type = static_cast<pointer_type>(m_arr);
         pointer_type block_arr_type = block.m_arr;

         uint32 capacity = block.getCapacity();
         for(int i = 0; i < capacity; i++) {
            arr_type[i] = block_arr_type[i]; // deep copy
         }
      }

      /**
       * @brief Move Constructor
       * @param block Rvalue memory block
       */
      MemoryBlock(MemoryBlock<T>&& block) 
      {
         m_arr = block.m_arr;
         m_allocated = block.m_allocated;

         // Standard move semantics
         block.m_arr = nullptr;
         block.m_allocated = 0;
      }

      /**
       * @brief Destroy the Pixel Memory Block object
       * Performs a shallow delete on the memory block, 
       * i.e. Only frees the memory.
       */
      ~MemoryBlock()
      {
         // Shallow delete
         free(m_arr);
      }

      /**
       * @brief Get the total instance capacity of the memory block
       * @return The total number of T instances which can be stored by the memory block. 
       * Returns a unsigned int value.
       */
      uint32 getCapacity() const {
         return m_allocated / sizeof(T);
      }


      /**
       * @brief Get the total memory allocted in the memory block
       * @return uint32 
       */
      uint32 getTotalAllocation() const {
         return m_allocated;
      }


      /**
       * @brief Get the data handle to the allocated data 
       * @return A data_handle (of void* type) to the allocated data.
       */
      pointer_type getData() {
         return static_cast<pointer_type>(m_arr);
      }


      /**
       * @brief Get a const data_handle to the allocated dat
       * @return A const data_handle (of void* type) to the allocated data.
       */
      const pointer_type getData() const {
         return static_cast<const pointer_type>(m_arr);
      }







      /**
       * @brief Equal assignment used to TAKEOVER the resources of an rvalue instance.
       * The assignment revokes access of the allocated resources from the block argument 
       * and give the resources to the host instance.
       * @param block An Rvalue instance of MemoryBlock.
       */
      void operator = (MemoryBlock<T>&& block) {
         // using namespace std;
         if(m_arr) 
            free(m_arr);

         // Standard move semantics
         m_arr = block.m_arr;
         m_allocated = block.m_allocated;
         block.m_arr = nullptr;
      }




      /**
       * @brief Equal assingment to COPY the resources of block into the host memory block.
       * The assignment performs a deep copy of the resources in the block.
       * @param block 
       */
      void operator = (const MemoryBlock<T>& block) {
         if(m_arr) 
            free(m_arr);

         m_allocated = block.allocated;
         m_arr = malloc(m_allocated);

         // Standard copying semantics
         // memcpy(m_arr, block.m_arr, m_allocated);

         // Deep copy
         pointer_type arr_type = static_cast<pointer_type>(m_arr);
         pointer_type block_arr_type = block.m_arr;

         uint32 capacity = block.getCapacity();
         for(int i = 0; i < capacity; i++) {
            arr_type[i] = block_arr_type[i]; // deep copy
         }
      }

      /**
       * @brief Releases all the memory possessed by the memory block.
       * 
       * @return true if release was successful
       * @return false if release was unsuccessful (can occur if the data handle is null)
       */
      bool release_memory() noexcept {
         if(!m_arr) 
            return false;

         free(m_arr);
         m_allocated = 0;

         return true;
      }


      bool increase_capacity() {
         uint32 capacity = this->getCapacity();

         if(capacity <= PX_MEMBLOCK_DOUBLE_LIMIT)
            this->increase_capacity_double();
         else if(capacity <= PX_MEMBLOCK_HALF_LIMIT) 
            this->increase_capacity_half();
         else
            this->increase_capacity_quarter();
      }

      bool increase_capacity(const float32& factor) {
         this->increase_capacity_by_factor(factor);
      }


private:

      /**
       * @brief Increases the capacity of the memory by the quarter of its original size
       * If quarter the size is less than one, the size of the memory is doubled.
       * 
       */
      void increase_capacity_quarter () {
         this->increase_capacity_by_factor(0.25);
      }

      void increase_capacity_half () {
         this->increase_capacity_by_factor(0.5);
      }

      /**
       * @brief Increases the capacity of the memory by 100%.
       * In case the capacity of the memory block is 0, the
       * default size of the memory block is allocated for the block
       * 
       */
      void increase_capacity_double() {
         
         // determining new size
         uint32 prev_capacity = this->getCapacity();
         uint32 new_capacity = (prev_capacity * 2);

         if(new_capacity == prev_capacity) {
            // Allocate a default memory block, since the last allocation size was 0
            m_arr = malloc(sizeof(T) * pixel::MemoryBlock<T>::s_default_block_capacity);
            m_allocated = sizeof(T) * s_default_block_capacity;
            return;
         }

         // Allocating a new block with double the capacity
         data_handle temp = m_arr;
         m_allocated *= 2; // doubling the size
         m_arr = malloc(m_allocated);
         memcpy(m_arr, temp, m_allocated / 2);

         // Releasing old memory
         free(temp);
      }


      void increase_capacity_by_factor(const float32& factor) {
         // determining new size
         uint32 prev_capacity = this->getCapacity();
         uint32 new_capacity = (prev_capacity + prev_capacity * factor);

         // If previous allocation and new allocation sizes are the same, it may be possible that the 
         // block is too small for a quarter increment. 
         // In this case, we shift to the double size strategy
         if(prev_capacity == new_capacity) return this->increase_capacity_double();

         // Allocate new block with quarter more
         // Copy old data into new block
         // Update m_allocated
         data_handle temp = m_arr;
         m_arr = malloc(sizeof(T) * new_capacity);

         memcpy(m_arr, temp, m_allocated);
         m_allocated = sizeof(T) * new_capacity;

         // Releasing old memory
         free(temp);
      }



   public:
      static const uint32 s_default_block_capacity = 10;

   private:
      data_handle m_arr; 
      uint32 m_allocated; // memory allocated in bytes
   };


}