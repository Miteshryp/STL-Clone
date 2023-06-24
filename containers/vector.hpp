#pragma once

#include<assert.h>
#include<algorithm>

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
    {
    }

    vector(std::initializer_list<value_type> init_list)
        :
        m_block(init_list.size()),
        m_size(init_list.size())
    {
        memmove(m_block.getData(), init_list.begin(), m_block.getTotalAllocation());
    }

    constexpr vector(ptr_type start, size_t size)
        :
        m_block(size),
        m_size(size)
    {
    }

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

/**
 * Modifiers
 * 
 */

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



    /**
     * @todo test => complete the pop function to deal with the return value 
     * if it is not to be accepted outside the method call
     * 
     * @return value_type 
     */
    void pop() {
        // return static_cast<value_type&&>(m_block.getData()[--m_size]);
        m_size--;
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
        assert(index < m_size && index + count);

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

    /**
     * @brief Erases the element pointed at by the iterator from the array
     * 
     * @param it 
     * @return true 
     * @return false 
     */
    bool erase(const iterator& it) {
        assert(it->m_ptr >= m_block.getData() && it->m_ptr < m_block.getData() + m_size);

        (*it).~value_type();
        

        /** @todo: check if this move is correct
        */
        memmove(it->m_ptr, it->m_ptr+1, ( (m_block.getData() + m_size) - it->m_ptr ) * sizeof(value_type));
        return true;
    }

    /**
     * @brief Inserts an element of the used type at the specified index.
     * 
     * @param index 
     * @param element 
     * @return true if the insertion was successful,
     * @return false otherwise.
     * 
     * 
     * @todo Optimization possible - Instead of increasing capacity on the available block,
     * which creates a new block and copies the entire array to the new block, we can create
     * the new block manually and copy uptil the correct position, insert the element and 
     * copy over the remaining elements.
     * This reduces the number of copies. In the current method, the entire array is copied 
     * over once, and then the memory to the right of the index is again shifted one index 
     * to the right.
     */
    bool insert(uint32 index, const reference_type element) {
        assert(index < m_size);

        // ensuring that space is available to shift the array to the right
        if(m_size >= m_block.getCapacity()) {
            m_block.increase_capacity();
        } 

        // shift the memory by one
        memmove(m_block.getData() + index, m_block.getData(), (m_size - index) * sizeof(value_type));
        m_block.getData()[index] = element;

        return true;
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


/**
 * Constant functions
 */


    /**
     * @brief Returns a vector containing the sliced portion of the vector
     * 
     * @param start starting index of the sliced vector
     * @param element_count number of elements from the starting index
     * @return A vector of copied sliced element
     */
    vector_type slice(uint32 start, uint32 element_count) const {
        // ensures proper slice queries
        assert(start + element_count <= m_size);

        // creating a new block, which copies the queried elements.
        memory_block_type ret_block(m_block.getData() + start, element_count);
        return vector_type(ret_block, element_count);
    }


    /**
     * @brief Returns the currently occupied storage capacity 
     * of the vector's memory block
     * 
     * @return The total count of elements which can be stored in the vector
     */
    uint32 capacity() const {
        return m_block.getCapacity();
    }

    /**
     * @brief Returns the remaining number of elements which can be
     * inserted before a resize is required.
     * 
     * @return The remaining capacity of the vector
     */
    uint32 remaining_capacity() const {
        // return m_capacity - m_size;
        return m_block.getCapacity() - m_size;
    }


    /**
     * @brief The current occupied size of the vector
     * 
     * @return size of vector
     */
    uint32 size() const {
        return m_size;
    }

    /**
     * @brief Used to get a const reference to an element at a specified index.
     * 
     * @param index The index of element to get a reference
     * @return const reference of the element
     */
    const reference_type at(uint32 index) const {
        return m_block.getData()[index];
    }


    /**
     * @brief Returns a const reference to the
     * first element of the array
     * 
     * @return const reference to the first element
     */
    const reference_type front() const {
        return m_block.getData()[0];
    }


    /**
     * @brief Returns a const reference to the
     * last element of the array
     * 
     * @return reference to the last element 
     */
    const reference_type back() const {
        return m_block.getData()[m_size - 1];
    }

    /**
     * @brief Used to check whether a certain element
     * is present in the vector
     * 
     * @param element The element to check in the array
     * @return true if the element is present,
     * false otherwise
     */
    bool contains(const reference_type element) const  {
        for(uint32 i = 0; i < m_size; i++)
            if(m_block.getData()[i] == element) return true;
        
        // not found
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
     * @return The index of first occurance of element.
     * 
     * @todo implement
     */
    int32 find(const reference_type element) const {
        for(uint32 i = 0; i < m_size; i++) {
            if(m_block.getData()[i] == element) return i;
        }
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
        return iterator(m_block.getData());
    }

    iterator end() const {
        return iterator(m_block.getData() + m_size);
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
    void realloc_capacity(uint32 new_capacity) {
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
    reference_type operator [](uint32 index) {
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