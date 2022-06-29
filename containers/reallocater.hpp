#include<cstdlib>
#include<cstring>
#include<cassert>

namespace pixel {


   struct PixelMemoryBlock {
      void* m_arr;
      int m_elem_size;
      int m_capacity;

      PixelMemoryBlock(void* arr, int elem_size, int capacity) {
         m_arr = arr;
         m_elem_size = elem_size;
         m_capacity = capacity;
      }

      // Deep Copy
      PixelMemoryBlock(PixelMemoryBlock&& block) {
         free(m_arr);

         m_capacity = block.m_capacity;
         m_elem_size = block.m_elem_size;
         m_arr = malloc(m_elem_size * m_capacity);

         memcpy(m_arr, block.m_arr, m_elem_size * m_capacity);
      }

      constexpr PixelMemoryBlock& operator = (const PixelMemoryBlock& block) {
         free(m_arr);

         m_arr = block.m_arr;
         m_elem_size = block.m_elem_size;
         m_capacity = block.m_capacity;

         return *this;
      }


   };


// Double Capacity Stratergy
   PixelMemoryBlock pixel_push_capacity_Double_strategy(int elem_size, int curr_capacity) {
      int new_capacity = curr_capacity*2; // Total no of elements which can be stored.
      void* new_block = malloc(elem_size*new_capacity);

      return PixelMemoryBlock(new_block, elem_size, new_capacity);
   }

// Quarter Increase Statergy
   PixelMemoryBlock pixel_push_capacity_QuarterINC_strategy(int elem_size, int curr_capacity) {
      // assert(curr_capacity >= 4);//, "Cannot Increase Capacity - Quarter Startergy works for curr_capacity >= 4");

      int new_capacity = curr_capacity + std::max(1, (curr_capacity / 4)); // Total no of elements which can be stored.
      void* new_block = malloc(elem_size*new_capacity);

      return PixelMemoryBlock(new_block, elem_size, new_capacity);
   }





// Reallocating the array with the appropriate statergy
   PixelMemoryBlock pixel_push_capacity(void* curr_arr, int elem_size, int curr_arr_size, int curr_capacity) {
      assert(elem_size > 0);//, "Failed to increase the capacity - Size of an array element must be non zero.");
      
      if(curr_arr == nullptr) return PixelMemoryBlock(nullptr, 0, 0);

      PixelMemoryBlock new_block = pixel_push_capacity_Double_strategy(elem_size, curr_capacity);
      void* new_arr = new_block.m_arr;

      // Copy the contents of the old array into the new extended array
      memcpy(new_arr, curr_arr, elem_size*curr_arr_size);

      return new_block;
   }



// Memory Allocater functions
   PixelMemoryBlock get_memory_block(int elem_size, int initial_capacity) {
      void* arr = malloc(elem_size*initial_capacity);
      return PixelMemoryBlock(arr, elem_size, initial_capacity);
   }

   void free_memory_block(PixelMemoryBlock& block) {
      void* arr = block.m_arr;
      free(arr);
   }
}