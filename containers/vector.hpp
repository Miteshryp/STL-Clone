#include<iostream>
#include<string>
#include<memory.h>

#include<assert.h>

#define PX_VEC_CAPACITY_EXT(c) (c*2)

namespace pixel {


template<typename T>
class vector {
    using value_type = T;
    using ptr_type = T*;
    using reference_type = T&;

    using vector_type = vector<T>;
    using vector_reference_type = vector<T>&;

public:
    vector()
        :
        m_arr(nullptr),
        m_size(0),
        m_capacity(0)
    {}

    vector(const vector& v)
    {  
        m_size = v.m_size;
        m_capacity = v.m_capacity;

        m_arr = (ptr_type)( malloc(m_capacity * sizeof(value_type)) );

        memcpy(m_arr, v.m_arr, m_size * sizeof(value_type));
    }

    vector(vector&& v) 
    {
        m_size = v.m_size;
        m_capacity = v.m_capacity;
        m_arr = v.m_arr;

        v.m_arr = nullptr;
    }



// Access methods
public:

    // modifiers

    void push(const reference_type element) {
        if(m_size >= m_capacity)
            this->realloc_capacity(PX_VEC_CAPACITY_EXT(m_capacity));
        
        m_arr[m_size++] = element;
    }

    value_type pop() {
        return m_arr[--m_size];
    }

    bool erase() {
        // @TODO - remove all the elements from array
    }

    bool shrikn() {
        // @TODO - shrink the capacity to fit the e
        //         current elements only.
    }

    int insert(int index, const reference_type element) {
        assert(index < m_size);
        // @TODO - insert element at index
    }


    // const functions


    vector_type slice(int start, int element_count) const {
        // @TODO - returns a subset vector, containing 
        //         elements from [start, start+element_count]   
    }




    int capacity() const {
        return m_capacity;
    }

    int remaining_capacity() const {
        return m_capacity - m_size;
    }

    const reference_type at(int index) const {
        return m_arr[index];
    }

    const reference_type front() const {
        return m_arr[0];
    }

    const reference_type back() const {
        return m_arr[m_size - 1];
    }

    bool contains (const reference_type element) const  {
        // @TODO
        return false;
    }

    bool empty() const {
        return m_size == 0;
    }
    
    int find(const reference_type element) const {
        // @TODO
        return -1;
    }
    
    const ptr_type to_array() const {
        return m_arr;
    }





// Misc methods
public:
    void realloc_capacity(int new_capacity) {
        assert(new_capacity >= m_size); // cannot shrink to delete elements

        ptr_type old_arr = m_arr;
        ptr_type new_arr = malloc(sizeof(value_type) * new_capacity);

        if(old_arr != nullptr) {
            memcpy(new_arr, old_arr, sizeof(value_type) * m_size);
            free(old_arr);
        }
    
        m_arr = new_arr;
        m_capacity = new_capacity;
    }



// Operators
public:
    void operator = (const vector& v) {
        m_size = v.m_size;
        m_capacity = v.m_capacity;
        
        // free the existing memory
        if(m_arr != nullptr)
            free(m_arr);
        
        // reallocating with new size
        m_arr = malloc(sizeof(value_type) * m_capacity);
        memcpy(m_arr, v.m_arr, m_size * sizeof(value_type)); // copying new data
    }

    reference_type operator [](int index) {
        return m_arr[index];
    }


private:
    ptr_type m_arr;
    int m_size;
    int m_capacity;
};


}