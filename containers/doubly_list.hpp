#pragma once

#include<cstdlib>
#include<assert.h>
#include<memory.h>

#include "containers/utils/iterator.hpp"
#include "containers/memory/list_nodes.hpp"
#include "containers/memory/node_store.hpp"

namespace pixel {

using namespace pixel::types;


template<typename Value_Type>
class doubly_list : public pixel::node_allocator<pixel::Pixel_DLL_Node<Value_Type>, Value_Type> {

    using value_type = Value_Type;
    using ptr_type = Value_Type*;
    using reference_type = Value_Type&;
    using const_reference_type = Value_Type const&;

    using list_type = doubly_list<value_type>;
    using list_reference_type = doubly_list<value_type>&;
    using const_list_reference_type = doubly_list<value_type> const&;
    using list_ptr_type = doubly_list<value_type>*;
    // using list_Rreference_type = doubly_list<T>&&;

    using node_type = Pixel_DLL_Node<value_type>;
    using node_ptr = Pixel_DLL_Node<value_type>*;
    using node_reference = Pixel_DLL_Node<value_type>&;

    using allocator_type = pixel::node_allocator<node_type, value_type>;

public:
    doubly_list()
        :
        allocator_type(),
        m_head(nullptr),
        m_tail(nullptr),
        m_size(0)
    {}

    /**
     * @brief Copy Constructor. Does not copy node store
     * of the doubly list.
     * 
     * @param list Doubly linked list to be copied.
     */
    doubly_list(const_list_reference_type list)
        :
        allocator_type(),
        m_head(nullptr),
        m_tail(nullptr),
        m_size(0)
    {
        this->copy_list(list);
    }

    doubly_list(list_type&& list)
        :
        allocator_type(),
        m_head(list.m_head),
        m_tail(list.m_tail),
        m_size(list.m_size)
    {
        list.m_head = nullptr;
        list.m_tail = nullptr;
        list.m_size = 0;
    }

//Getters
public:

    
    /**
     * @brief Returns the current size of the doubly linked list
     * @return size of the list 
     */
    uint32 size() const {
        return m_size;
    }

    /**
     * @brief Returns the current element capacity of the 
     * list
     * 
     * @return Total number of elements which can 
     * be stored in current capacity 
     */
    uint32 capacity() const {
        return m_size + this->m_store.size();
    }

    /**
     * @brief Returns the remaining capacity of
     * elements which can be stored in the current 
     * allocated capacity
     * 
     * @return Number of elements which can be inserted
     * before new allocation
     */
    uint32 remaining_capacity() const {
        return this->m_store.size();
    }

    bool empty() const {
        return m_size == 0;
    }

public:

    /**
     * @brief Inserts the element at the tail
     * of the linked list
     * 
     * @param element value to be inserted
     */
    void push_back(const_reference_type element) {
        node_ptr new_node = this->create_back_node(element); // creating node to be added to tail
        
        m_tail->setNextPtr(new_node);
        m_tail = new_node;
    }

    /**
     * @brief Inserts the element at the head
     * of the linked list
     * 
     * @param element value to be inserted
     */
    void push_front(const_reference_type element) {
        node_ptr new_node = this->create_front_node(element);
        
        m_head->setPrevPtr(new_node);
        m_head = new_node;
    }


    /**
     * @brief Deletes an element from the tail
     * of the linked list
     */
    void pop_back() {
        assert(m_size > 0);

        node_ptr removed_node = m_tail;

        // Configuring new tail pointer
        m_tail = (node_ptr)(m_tail->getPrevPtr());
        m_tail->setNextPtr(nullptr);

        // Pushing removed node to store
        this->store_push(removed_node);
    }

    /**
     * @brief Deletes an element from the head
     * of the linked list
     */
    void pop_front() {
        assert(m_size > 0);

        node_ptr removed_node = m_head;
        
        // Configuring new head pointer
        m_head = (node_ptr)(m_head->getNextPtr());
        m_head->setPrevPtr(nullptr);

        // Pushing removed node to store
        this->store_push(removed_node);
    }

    /**
     * @brief Pushes all nodes in the linked list
     * into the node store and deletes the element
     * 
     */
    void clear() {
        // Empty list
        if(m_size == 0) return;

        node_ptr node = m_head;

        while(node != nullptr) {
            node_ptr t = node;
            node = node->next;
            this->store_push(node);
        }

        // Setting new configurations
        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;
    }

    /**
     * @brief Empties the node store of 
     * the list
     * 
     */
    void shrink() {
        this->store_flush();
    }

    /**
     * @brief Inserts the element at the specified index
     * 
     * @param element value to be inserted
     * @param index index at which value is to be inserted.
     */
    void insert(const_reference_type element, const uint32& index) {
        assert(m_head != nullptr && m_tail != nullptr);
        assert(index < m_size);


        // Edge insertions are already handled
        if(index == 0) {
            this->push_front(element);
            return;
        }
        if(index == m_size - 1) {
            this->push_back(element);
            return;
        }

        // Inserting from closest end
        if(index >= m_size / 2) 
            this->insert_from_back(element, index);
        else
            this->insert_from_start(element, index);
    }









/**
 * Access Methods
 * 
 */
public:
    /**
     * @brief Returns a const reference to the element
     * at the head of the linked list
     * 
     * @return const reference to the element
     */
    const_reference_type front() const {
        assert(m_head != nullptr);
        return *(m_head->getDataPointer());
    }

    /**
     * @brief Returns a const reference to the element
     * at the tail of the linked list
     * 
     * @return const reference to the element
     */
    const_reference_type back() const {
        assert(m_tail != nullptr);
        return *(m_tail->getDataPointer());
    }

    /**
     * @brief Returns a const reference to the element
     * at the element at the specified index of the
     * linked list
     * 
     * @return const reference to the element
     */
    const_reference_type at(uint32 index) const {
        // @TODO - return item at [index] of dll
        assert(index < m_size);

    }


    /**
     * @brief Finds and returns the index of the element 
     * if the element exists in the list. The search starts
     * from the head node.
     * 
     * @param element value to be searched
     * @return index of the element if the element is present, -1 otherwise
     */
    int32 find(const_reference_type element) const {
        if(m_head == nullptr && m_tail == nullptr) return -1;

        node_ptr node = m_head;
        uint32 index = 0;

        while(node != nullptr) {
            if(node->getDataValue() == element) return index;
            index++;
            node = (node_ptr)(node->getNextPtr());
        }

        return -1;
    }


    /**
     * @brief Finds and returns the index of the element 
     * if the element exists in the list. The search starts
     * from the tail node.
     * 
     * @param element value to be searched
     * @return index of the element if the element is present, -1 otherwise
     */
    int32 rfind(const_reference_type element) const {
        if(m_head == nullptr && m_tail == nullptr) return -1;

        node_ptr node = m_tail;
        uint32 index = m_size - 1;

        while(node != nullptr) {
            if(node->getDataValue() == element) return index;
            index++;
            node = (node_ptr)(node->getPrevPtr());
        }

        return -1;
    }







/**
 * Operators Implementation
 * 
 */
public:
    void operator = (const_list_reference_type list) {
        this->copy_list(list);
    }

    void operator = (list_type&& list) {
        m_head = list.m_head;
        m_tail = list.m_tail;
        m_size = list.m_size;

        list.m_head = list.m_tail = nullptr;
        list.m_size = nullptr;
    }









/**
 * Interface Implementation
 */
protected:

    /**
     * @brief Internal use only.
     * Creates and configures a tail node
     * 
     * @param item data value
     * @return node_ptr 
     */
    virtual node_ptr create_back_node(const_reference_type item) {
        node_ptr new_node = this->m_store.pop_node();

        // Configuring new tail node
        new_node->setNextPtr(nullptr);
        new_node->setPrevPtr(m_tail);
        new_node->setDataValue(item);

        return new_node;
    }
    virtual node_ptr create_back_node(value_type&& item) {
        node_ptr new_node = this->m_store.pop_node();

        // Configuring new tail node
        new_node->setNextPtr(nullptr);
        new_node->setPrevPtr(m_tail);
        new_node->setDataValue(static_cast<value_type&&>(item));

        return new_node;
    }

    /**
     * @brief Internal use only.
     * Creates and configures a head node
     * 
     * @param item data value
     * @return node_ptr 
     */
    virtual node_ptr create_front_node(const_reference_type item) {
        node_ptr new_node = this->m_store.pop_node();

        // Configuring new head node
        new_node->setNextPtr(m_head);
        new_node->setPrevPtr(nullptr);
        new_node->setDataValue(item);

        return new_node;
    }
    virtual node_ptr create_front_node(value_type&& item) {
        node_ptr new_node = this->m_store.pop_node();

        // Configuring new head node
        new_node->setNextPtr(m_head);
        new_node->setPrevPtr(nullptr);
        new_node->setDataValue(static_cast<value_type&&>(item));

        return new_node;
    }

    /**
     * @brief Internal Use Only.
     * Pulls and returns a node from the node store
     * 
     * @return node_ptr 
     */
    virtual node_ptr store_pop() {
        node_ptr t = this->m_store.pop_node();
        t->setPrevPtr(nullptr);
        t->setNextPtr(nullptr);

        return t;
    }








/**
 * Internal Methods
 * 
 */
private:

    /**
     * @brief Method to copy list
     * 
     * @param list List to be copied
     */
    void copy_list (const_list_reference_type list) {
        // Empty list edge case
        if(list.size() == 0) {
            m_head = nullptr;
            m_tail = nullptr;
            m_size = 0;
            return;
        }

        // Single node edge case
        if(list.size() == 1) {
            m_head = this->store_pop();
            m_head->setDataValue(list.m_head->getDataValue());
            m_tail = m_head;

            m_size = 1;
            return;
        }

        // Iteration counters
        uint32 curr_size = 1;
        node_ptr curr_list_node = (node_ptr)(list.m_head->getNextPtr());

        // Creating the head node
        m_head = this->create_front_node(list.m_head->getDataValue());
        node_ptr prev_node = m_head;


        // Copying each node of the list
        while(curr_size < list.size()) {
            node_ptr new_node = this->create_back_node(curr_list_node->getDataValue());
            
            prev_node->setNextPtr(new_node);
            new_node->setPrevPtr(prev_node);

            prev_node = new_node;
            
            curr_size++;
        }

        // Configuring tail node
        m_tail = prev_node;
        m_size = list.size();
    }



    
    void insert_from_start(const_reference_type element, const uint32& index) {
        assert(m_size != 0);
        assert(index < m_size && index != 0 && index != m_size - 1);


        // Extracting node
        node_ptr temp = m_head;
        uint32 next_index = 1; // index of the next element
        while(next_index < index) {
            temp = (node_ptr)temp->getNextPtr();
            next_index++;
        }

        // Insert the node at the calculated position
        node_ptr new_node = this->store_pop();
        new_node->setDataValue(element);
        new_node->setPrevPtr(temp);
        new_node->setNextPtr(temp->getNextPtr());

        ((node_ptr)temp->getNextPtr())->setPrevPtr(new_node);
        temp->setNextPtr(new_node);
        
        m_size++;
    }


    /**
     * @brief Inserts the element at the specified index
     * 
     * @param element value to be inserted
     * @param index index at which value is to be inserted.
     */
    void insert_from_back(const_reference_type element, const uint32& index) {
        assert(m_size != 0);
        assert(index < m_size && index != 0 && index != m_size - 1);


        // Extracting node
        node_ptr temp = m_tail;
        uint32 next_index = m_size - 2; // index of the next element
        while(next_index > index) {
            temp = (node_ptr)temp->getPrevPtr();
            next_index--;
        }

        // Insert the node at the calculated position
        node_ptr new_node = this->store_pop();
        new_node->setNextPtr(temp);
        new_node->setPrevPtr(temp->getPrevPtr());
        new_node->setDataValue(element);

        ((node_ptr)temp->getPrevPtr())->setNextPtr(new_node);
        temp->setPrevPtr(new_node);


        m_size++;
    }






/**
 * Data members
 * 
 */
private:
    node_ptr m_head;
    node_ptr m_tail;
    uint32 m_size;
};


}