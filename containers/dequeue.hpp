#pragma once
#include "containers/doubly_list.hpp"

namespace pixel {

template<typename Value_Type>
class deque {
    using value_type = Value_Type;
    using ptr_type = Value_Type*;
    using reference_type = Value_Type&;
    using const_reference_type = Value_Type const&;

    using doubly_list_type = pixel::doubly_list<value_type>;
    using doubly_list_reference_type = pixel::doubly_list<value_type>&;
    using doubly_list_ptr_type = pixel::doubly_list<value_type>*;
    using const_doubly_list_reference_type = pixel::doubly_list<value_type> const&;

    using deque_type = deque<value_type>;
    using deque_ptr = deque<value_type>*;
    using deque_reference = deque<value_type>&;
    using const_deque_reference = deque<value_type> const&;

public:
    deque();
    deque(const_deque_reference d);
    deque(deque_type&& d);


public:
    void push_back(const_reference_type item) {
        m_list.push_back(item);
    }
    void push_back(value_type&& item) {
        m_list.push_back(item);
    }

    void push_front(const_reference_type item) {
        m_list.push_front(item);
    }
    void push_front(value_type&& item) {
        m_list.push_front(item);
    }

    void pop_back() {
        assert(m_list.size() > 0);
        m_list.pop_back();
    }

    void pop_front() {
        assert(m_list.size() > 0);
        m_list.pop_front();
    }


public:
    /***
     * @brief Used to get a constant reference of the item
     * at the beginning.
     * @returns A reference to the data value at the front
     * of deque.
    */
    const_reference_type front() const {
        assert(index < m_list.size());
        return m_list.front();
    }

    /***
     * @brief Used to get a constant reference of the item
     * at the end.
     * @returns A reference to the data value at the end
     * of deque.
    */
    const_reference_type back() const {
        assert(index < m_list.size());        
        return m_list.back();
    }

    const_reference_type at(uint32 index) const {
        assert(index < m_list.size());
        return m_list.at(index);
    }

    

    /**
     * @brief Returns the total nodes allocated for the deque.
     * @returns the number of allocated nodes
     */
    uint32 capacity() const { 
        return m_list.capacity();
    }


    /**
     * @brief Returns the remaining capacity before a 
     * block allocation is required.
     * 
     * @returns the remaining number of elements 
     * which can be inserted.
     */
    uint32 remaining_capacity() const {
        return m_list.remaining_capacity();
    }

    /**
     * @brief Returns the current size of
     * the deque
     * @return occupied size of the deque
     */
    uint32 size() const {
        return m_list.size();
    }

    /**
     * @brief Returns whether or not the linked list is empty
     * @return true if empty, false otherwise
     */
    bool empty() const {
        return m_list.empty();
    }

public:
    void operator = (const_deque_reference d);
    void operator = (deque_type&& d);
    


private:
    doubly_list_type m_list;
};
   
}