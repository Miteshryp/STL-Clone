#pragma once

#include<assert.h>

#include "containers/utils/types.hpp"
#include "containers/utils/iterator.hpp"
#include "containers/memory/node_store.hpp"
#include "containers/memory/list_nodes.hpp"

namespace pixel {

using namespace pixel::types;

template<typename T>
class list {
    using value_type = T;
    using reference_type = T&;
    using ptr_type = T*;

    using list_type = list<T>;
    using list_reference_type = list<T>&;
    using list_Rreference_type = list<T>&&;
    using list_ptr_type = list<T>*;


    using node_type = Pixel_LL_Node<value_type>;
    using node_ptr = Pixel_LL_Node<value_type>*;

    // using iterator = BasicIterator<T>;
    using iterator = LLNodeIterator<T>;

public:

/**
 * @brief Creates a linked list object with no nodes
 * 
 */
    list()
        :
        m_head(nullptr),
        m_tail(nullptr),
        m_size(0)
    {}


    /**
     * @brief Copy constructor
     * 
     * @param linkedList 
     */
    list(const list_type& linkedList) {

        // Allocating new memory
        uint32 curr_size = 0;

        while(curr_size < linkedList.size()) {
            node_ptr new_node = m_store.pop_node();

        }
        // m_head = (node_ptr)calloc(sizeof(node_type));
        // m_tail = (node_ptr)calloc(sizeof(node_type));
        // m_head = m_store.pop_node();
        // m_tail = m_store.pop_node();

        // // Copying node contents
        // memcpy(m_head, linkedList.m_head, sizeof(node_type));
        // memcpy(m_tail, linkedList.m_tail, sizeof(node_type));

        // m_size = linkedList.m_size;
    }

    list(list_type&& linkedList) {
        // Taking over resources
        m_head = linkedList.m_head;
        m_tail = linkedList.m_tail;
        m_size = linkedList.m_size;

        // Cleansing data from rvalue type
        linkedList.m_head = nullptr;
        linkedList.m_tail = nullptr;
        linkedList.m_size = 0;
    }



// ------------------------
// |   Methods
// ------------------------


// Modifiers

    /**
     * @brief Adds the item to the tail of the linked list. 
     * @param item The value which has to be added to the tail.
     * 
     * @note: All items have to be passed with a defined equals 
     * `=` operator definition
     */
    void push_back(const reference_type item) {

        // New node creation
        node_ptr new_node = this->create_back_node(item);

        // Empty list case
        if(m_size == 0) {
            m_head = new_node;
            m_tail = new_node;
            m_size = 1;
            return;
        }

        // Adding new node to the linked list
        m_tail->m_next = new_node;
        m_tail = new_node;
        m_size++;
    }
    void push_back(value_type&& item) {
        // Allocating a new node
        node_ptr new_node = this->create_back_node(item);

        // Empty List case
        if(m_size == 0) {
            m_head = new_node;
            m_tail = new_node;
            m_size = 1;

            return;
        }

        // Adding new node to the linked list
        m_tail->m_next = new_node;
        m_tail = new_node;
        m_size++;
    }


    /***
     * @brief Adds an item to the head of the linked list
     * @param item The item to be added to the head
     * @returns void
    */
    void push_front(const reference_type item) {

        // Creating new front node
        node_ptr new_node = this->create_front_node(item);
        m_head = new_node;
        m_size++;

    }


    /***
     * @brief Removes the item at the end of the list
     * @returns void
    */
    void pop_back() {
        assert(m_head != nullptr && m_tail != nullptr);

        // Special case - single node
        if(m_head == m_tail) {
            value_type ret = m_head->getDataValue();
            this->delete_all_nodes();
        }
        
        
        // Fetching the second last node
        node_ptr new_tail = m_head;
        while(new_tail->m_next != m_tail) {
            new_tail = new_tail->m_next;
        }


        // Removing the current tail
        free(m_tail);

        // Assigning new tail
        m_tail = new_tail;
        m_tail->setNextPtr(nullptr);
        m_size--;
    }

    /****
     * @brief Removes the item at the head of the linked list.
     * @returns void
    */
    void pop_front() {
        assert(m_head != nullptr && m_tail != nullptr);

        if(m_head == m_tail) {
            this->delete_all_nodes();
            return;
        }

        // Determining new head
        node_ptr new_head = (node_ptr)(m_head->getNextPtr());
        node_ptr old_head = m_head;
        old_head->setNextPtr(nullptr);

        // Deleting head node
        m_head = new_head;
        m_size--;

        m_store.push_node(old_head);
    }

    
    /**
     * @brief Removes the element at the specified index
     * 
     * @param index index to be deleted
     * @return void
     */
    void pop_at(const uint32& index) {
        assert(m_head != nullptr && m_tail != nullptr);
        assert(index < m_size);

        // Extracting node
        node_ptr temp = m_head;
        uint32 next_index = 1; // index of the next element
        while(next_index < index) {
            temp = temp->m_next;
            next_index++;
        }

        // Remove the node from the main list
        node_ptr removed_node = temp->m_next;
        temp->m_next = removed_node->m_next;
        m_size--;

        m_store.push_node(removed_node);
    }








// data operations

/**
 * @brief Deletes all the nodes allocated in the linked list
 * @returns void type
 * 
 * @warning The method deletes the data assigned to the node.
 * If the data type does not implement a destructor, the deletion 
 * of data will happen in an implicit manner (Just removing the
 * data assigned to the data type).
 * For User defined types, It is recommended that a destructor is
 * defined
 * 
 * If the linked list contains pointers as data type, then using 
 * this method without freeing the memory of the pointers will 
 * cause a memory leak.
 * 
 * 
 * 
 */
    void delete_all_nodes() {
        node_ptr node = m_head;
        if(node == nullptr) return;

        while(node != nullptr) {
            node_ptr temp = node->m_next;
            
            if(node != nullptr) 
                free(node);
            
            node = temp;
        }

        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;
    }



// Getters


    /**
     * @brief Used to get the head element object 
     * @return a const reference to the head element
     */
    const reference_type front() const {
        assert(m_head != nullptr);
        return m_head->getDataValue();
    }


    /***
     * @brief Can be used to fetch a constant reference of the item at the end of the linked list.
     * @returns A reference to the data value in the tail node.
    */
    const reference_type back() const {
        assert(m_tail != nullptr);
        return m_tail->getDataValue();
    }


    /**
     * @brief Used to get the element at a specific index
     * 
     * @param index index of the element in the list
     * @return a const reference to the element in the list
     */
    const reference_type at(const uint32& index) const {
        assert(index < m_size);

        // Fetching the indexed node
        node_ptr node = m_head;
        uint32 curr_index = 0;

        while(curr_index < index) {
            node = node->m_next;
            curr_index++;
        }

        return node->getDataValue();
    }
    
    /**
     * @brief Returns whether or not the linked list is empty
     * @return true if empty, false otherwise
     */
    bool empty() const noexcept {
        return m_size == 0;
    }
    
    /**
     * @brief Used to get the current size of the linked list
     * @return occupied size of the list
     */
    uint32 size() const noexcept {
        return m_size;
    }
    
    /**
     * @brief Returns the total nodes allocated for the list.
     * 
     * @return the number of allocated nodes
     */
    uint32 capacity() const noexcept {
        return m_size + m_store.size();
    }
    
    /**
     * @brief Returns the remaining capacity of the list before a 
     * block allocation is required.
     * 
     * @return the remaining number of nodes which can be inserted.
     */
    uint32 remaining_capacity() const noexcept {
        return m_store.size();
    }
    
    /**
     * @brief Returns the size of the node block created by the list
     * @returns size of node block
     */
    uint32 get_node_size() const {
        return sizeof(node_type);
    }








    /**
     * @brief Returns an iterator to the head element
     * @return iterator pointing to the start of the list
     */
    iterator begin() const {
        return iterator(m_head);
    }
    /**
     * @brief Returns an iterator to nullptr (end of the list)
     * @return iterator pointing to the end of the list
     */
    iterator end() const {
        return iterator(nullptr);
    }


    /**
     * @brief Used to find a specific value in the linked list
     * 
     * @returns The index of the value in the list
     */
    int32 find(const reference_type value) const {
        assert(m_head != nullptr && m_tail != nullptr);

        node_ptr node = m_head;
        uint32 curr_index = 0;

        while(node != nullptr) {
            if(node->getDataValue() == value) 
                return curr_index;
                
            curr_index++;
            node = node->m_next;
        }

        return -1;
    }
    int32 find(value_type&& value) const {
        assert(m_head != nullptr && m_tail != nullptr);

        node_ptr node = m_head;
        uint32 curr_index = 0;
        while(node != nullptr) {
            if(node->getDataValue() == value) return curr_index;
            curr_index++;
            node = node->m_next;
        }

        return -1;
    }


public:
    /**
     * @brief Copy operator
     * 
     * @param list List to be copied over
     */
    void operator = (const reference_type list) {
        
    }


    void operator = (value_type&& list) {

    }

private:

    /**
     * @brief For internal use.
     * Creates and configures a new node block to be added to the tail of the list
     * 
     * @param item data value to be inserted in the node
     * @return pointer to the created node
     */
    node_ptr create_back_node(value_type&& item) {
        node_ptr new_node = m_store.pop_node();

        // Configuring tail node
        new_node->setDataValue(item);
        new_node->setNextPtr(nullptr);

        return new_node;
    }
    node_ptr create_back_node(const reference_type item) {
        node_ptr new_node = m_store.pop_node();

        // Configuring tail node
        new_node->setDataValue(item);
        new_node->setNextPtr(nullptr);

        return new_node;
    }


    

    /**
     * @brief For internal use.
     * Creates and configures a new node block to be added to the front of the list
     * 
     * @param item data value to be added to the node block
     * @return pointer to the node block
     */
    node_ptr create_front_node(const reference_type item) const {
        node_ptr new_node = m_store.pop_node();

        // Configuring head node
        new_node->setDataValue(item);
        new_node->setNextPtr(m_head);
        
        return new_node;
    }
    node_ptr create_front_node(value_type&& item) const {
        node_ptr new_node = m_store.pop_node();

        // Configuring head node
        new_node->setDataValue(item);
        new_node->setNextPtr(m_head);

        return new_node;
    }






    /**
     * @brief For internal use. Inserts a spare node block to the tail of the store
     * 
     * @param node node_ptr to the node block
     * @returns true if insertion was successful, false otherwise
     */
    bool store_push(node_ptr node) {
        return m_store.push_node(node);
    }


    /**
     * @brief For internal use. Returns a pointer to a spare block in the store
     * 
     * @param node 
     * @return node_ptr 
     */
    node_ptr store_pop(node_ptr node) {
        node_ptr t = m_store.pop_node();
        return t;
    }

    /**
     * @brief Deletes all spare node blocks saved in the store
     * 
     * @return true on successful deallocation
     * @return false if no nodes were flushed
     */
    bool store_flush() {
        return m_store.flush_nodes();
    }

private:
    node_ptr m_head;
    node_ptr m_tail;
    uint32 m_size;

    pixel::node_store<node_type> m_store;
};

}
