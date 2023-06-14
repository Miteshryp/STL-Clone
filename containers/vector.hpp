#pragma once

#include<assert.h>

#include "containers/utils/types.hpp"
#include "containers/utils/iterator.hpp"
#include "containers/memory/memory_block.hpp"

#define PX_VEC_CAPACITY_EXT(c) (c*2)

namespace pixel {
    using namespace pixel::types;

template<typename T>
class vector {
    using value_type = T;
    using ptr_type = T*;
    using reference_type = T&;

    using vector_type = vector<T>;
    using vector_reference_type = vector<T>&;

    using memory_block_type = pixel::memory_block<T>;
    using memory_block_ptr = pixel::memory_block<T>*;

    using iterator = pixel::BasicIterator<T>;

public:
    vector()
        :
        m_block(),
        m_size(0)
    {}

    vector(const vector_type& v)
        :
        m_size(v.m_size),
        m_block(v.m_block)
    {}

    vector(vector_type&& v)
        :
        m_size(v.m_size),
        m_block(static_cast<memory_block_type&&>(v.m_block))
    {}

    vector(memory_block_type&& memory_block, uint32 size = 0)     
        :
        m_size(size),
        m_block(static_cast<memory_block_type&&>(memory_block))
    {}

    vector(const memory_block_type& memory_block, uint32 size)     
        :
        m_size(size),
        m_block(memory_block)
    {}



// Access methods
public:

    // modifiers

    /**
     * @brief Inserts a contructed instance of element into the memory block
     * This performs a copy of element passed to the memory block of the 
     * vector
     * 
     * @param element The instance of the element to be inserted
     */
    void push(const reference_type element) {
        if(m_size >= m_block.getCapacity())
            m_block.increase_capacity();
        
        m_block.getData()[m_size++] = element;
    }

    void push(value_type&& element) {
        if(m_size >= m_block.getCapacity())
            m_block.increase_capacity();
        
        // Leaving the implementation of rvalue copy to the user.
        m_block.getData()[m_size++] = static_cast<value_type&&>(element);
    }



    value_type pop() {
        return m_block.getData()[--m_size];
    }

    /**
     * @brief Erases 'count' elements present in the array starting from 
     * index passed in as the argument
     * 
     * @param index index from where to start the erase operation
     * @param count the number of elements to be erased
     * @return true on successful operation
     * @return false if the erase was unsuccessful
     */
    bool erase(uint32 index, uint32 count) {
        /**
         * @todo remove [count] elements starting from [index]
         * 
         * - Iterator value should remain same
         *   Therefore, we'll have to shift the elements backwords
         * - Cost(Shifting) < Cost(Rebuilding the array) 
         */
        assert(index < m_size);

        // cleaning up the object stored.
        m_block.getData()[index]->~value_type();

        // shifting all the elements after the index by one
        // NOTE: We use memmove to ensure memory safety during overlapping memory move.
        memmove(m_block.getData()[index], m_block.getData()[index + 1], sizeof(value_type) * (m_size - index + 1));
        m_size--;

        return true;
    }

    /**
     * @todo remove all instances of [value]
     * @brief 
     * @tricky Will leave holes in the memory block
     * 
     * @param value 
     * @return true 
     * @return false 
     */
    bool erase(const reference_type value) {
        for(uint32 i = 0; i < m_size; i++) {
            if(m_block.getData()[i] == value)
                this->erase(i, 1);
            i--;
        }

        return true;
    }

    bool erase(const iterator& it) {
        /**
         * @todo delete the element pointed to by the iterator
         * 
         * - Will shift all the elements after the iterator
         *   to the left by one index.
         */

        return true;
    }

    /**
     * @brief Inserts an element of the used type at the specified index.
     * 
     * @todo Decide if this would be efficient using shift or recreation of array
     * 
     * @param index 
     * @param element 
     * @return true if the insertion was successful,
     * @return false otherwise.
     */
    bool insert(int index, const reference_type element) {
        assert(index < m_size);
        // @TODO - insert element at index
    }

    /**
     * @brief Gets rid of extra allocated space for the memory block.
     * @warning This function recreates the array to exactly fit the size of array.
     * Unrestricted use may cause performance issues.
     * 
     * @return true on successful shrink operation
     * @return false shrink failed
     */
    bool shrink() {
        // @TODO - shrink the capacity to fit the
        //         current elements only.
        memory_block_type new_block(m_size);
        memcpy(new_block.getData(), m_block.getData(), new_block.getTotalAllocation());

        this->release_block_memory();
        m_block = static_cast<memory_block_type&&>(new_block);

        return true;
    }

    // const functions


    vector_type slice(int start, int element_count) const {
        // @TODO - returns a subset vector, containing 
        //         elements from [start, start+element_count]
        assert(start + element_count <= m_size);

        memory_block_type ret_block(m_block.getData() + start, element_count);
        return vector_type(ret_block, element_count);
    }


    /**
     * @brief Returns the currently occupied storage capacity 
     * of the vector's memory block
     * 
     * @return int - The total count of elements which can be stored in the vector
     */
    uint32 capacity() const {
        return m_block.getCapacity();
    }

    /**
     * @brief 
     * 
     * @return int 
     */
    uint32 remaining_capacity() const {
        // return m_capacity - m_size;
        return m_block.getCapacity() - m_size;
    }

    uint32 size() const {
        return m_size;
    }

    const reference_type at(int index) const {
        return m_block.getData()[index];
    }

    const reference_type front() const {
        return m_block.getData()[0];
    }

    const reference_type back() const {
        return m_block.getData()[m_size - 1];
    }

    bool contains (const reference_type element) const  {
        // @TODO
        return false;
    }

    /**
     * @brief Returns true if there are no elements remaining in the vector, false otherwise.
     * NOTE: This method takes in account the number of elements in the vector, not its 
     * capacity.
     * 
     * 
     */
    bool empty() const {
        return m_size == 0;
    }
    

    /**
     * @brief Finds the first occurance of an element in the vector
     * 
     * @param element 
     * @return int - The index of first occurance of element.
     * 
     * @todo implement
     */
    int find(const reference_type element) const {
        return -1;
    }

    
    /**
     * @brief Returns a const pointer to the memory block storing the vector data.
     * 
     * @return const ptr_type - handle to memory block data
     */
    const ptr_type to_array() const {
        return static_cast<const ptr_type>(m_block.getData());
    }


    iterator begin() const {

    }

    iterator end() const {

    }





// Misc methods
public:

    /**
     * @brief Reallocates the excess capacity of the vector memory block.
     * @warning The new capacity passed in must be greater than the 
     * number of elements currently present in the vector.
     * @warning This method creates a new vector, deleting the elements
     * stored in the last memory. If the stored elements are of user defined 
     * types, the element's destructor is called.
     * 
     * 
     * @param new_capacity new required required
     */
    void realloc_capacity(int new_capacity) {
        assert(new_capacity >= m_size); // cannot shrink to delete elements

        memory_block_type new_block(new_capacity);
        memcpy(new_block.getData(), m_block.getData(), m_size * sizeof(value_type));

        this->release_block_memory();
        m_block = static_cast<memory_block_type&&>(new_block);
    }



// Operators
public:
    /**
     * @brief Copy operator
     * 
     * @param v 
     */
    void operator = (const vector_type& v) {
        this->release_block_memory();

        m_size = v.m_size;
        m_block = v.m_block;

        // m_size = v.m_size;
        // m_capacity = v.m_capacity;
        
        // // free the existing memory
        // if(m_arr != nullptr)
        //     free(m_arr);
        
        // // reallocating with new size
        // m_arr = malloc(sizeof(value_type) * m_capacity);
        // memcpy(m_arr, v.m_arr, m_size * sizeof(value_type)); // copying new data
    }


    /**
     * @brief Used to access an element at the argument index
     * 
     * @param index 
     * @return reference_type 
     */
    reference_type operator [](int index) {
        // return m_arr[index];
        assert(index < m_size);
        return m_block.getData()[index];
    }


private:

    /**
     * @brief Deletes all the elements stored in the array
     * and then releases the memory occupied in the
     * memory block.
     * 
     */
    void release_block_memory() {

        // Deep delete
        for(uint32 i = 0; i < m_size; i++) 
            m_block.getData()[i].~value_type();

        // releasing the memory
        m_block.release_memory();
    }


private:
    uint32 m_size;
    memory_block_type m_block;
};


}