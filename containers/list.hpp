#pragma once

#include<assert.h>

#include "containers/utils/iterator.hpp"
#include "containers/utils/list_nodes.hpp"

namespace pixel {


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

    using iterator = BasicIterator<T>;

public:
    list()
        :
        m_head(nullptr),
        m_tail(nullptr),
        m_size(0)
    {}

    list(const list_type& linkedList) {
        m_head = calloc(sizeof(node_type));
        memcpy(m_head, linkedList.m_head);

        m_tail = m_head;
        m_size = linkedList.m_size;
    }

    list(list_type&& linkedList) {
        m_head = linkedList.m_head;
        m_tail = linkedList.m_tail;
        m_size = linkedList.m_size;

        // Cleansing data from rvalue type
        linkedList.m_head = nullptr;
        linkedList.m_tail = nullptr;
    }



// ------------------------
// |   Methods
// ------------------------


// Modifiers

    /**
     * @brief Adds the item to the tail of the linked list. 
     * A new node is created which stores the value passed
     * into the method as an argument.
     * 
     * @param item The value which has to be added to the tail.
     * @
     * @note: All items have to be passed with a defined equals 
     * `=` operator definition
     */
    void add_to_tail(value_type item) {
        node_ptr new_node = (node_ptr)calloc(sizeof(node_type));
        new_node->m_data = item;
        new_node->m_next = nullptr;

        m_tail->m_next = new_node;
        m_tail = new_node;
        m_size++;
    }


    /***
     * @brief Adds an item to the head of the linked list
     * @param item The item to be added to the head
     * @returns void return type.
    */
    void add_to_head(value_type item) {
        node_ptr new_node = calloc(sizeof(node_type));
        new_node->m_data = item;
        new_node->m_next = m_head;
        
        m_head = new_node;
        m_size++;
    }


    /***
     * @brief Removes the item at the end of the list
     * @returns The value of item at the end of the linked list
    */
    value_type remove_from_tail() {
        assert(m_head != nullptr && m_tail != nullptr);

        // Special case - single node
        if(m_head == m_tail) return this->delete_all_nodes();
        
        node_ptr new_tail = m_head;
        
        // Fetching the second last node
        while(new_tail->next != m_tail) {
            new_tail = new_tail->next;
        }

        // Removing the current tail
        free(m_tail);

        // assigning new tail
        m_tail = new_tail;
        m_size--;
    }

    /****
     * @brief Removes the item at the head of the linked list.
     * @returns The value of the item at the head of the linked list
    */
    value_type remove_from_head() {
        assert(m_head != nullptr && m_tail != nullptr);

        if(m_head == m_tail) return this->delete_all_nodes();

        node_ptr new_head = m_head->next;
        free(m_head);
        m_head = new_head;
        m_size--;
    }



// Getters

    /***
     * @brief Can be used to fetch a constant reference of the item at the end of the linked list.
     * @returns A reference to the data value in the tail node.
    */
    const reference_type get_tail_item() const {
        assert(m_tail != nullptr);
        return m_tail != nullptr ? m_tail->data : NULL;
    }

    /**
     * \brief Get the head item object
     * 
     * \return const reference_type 
     */
    const reference_type get_head_item() const {
        assert(m_head != nullptr);
        return m_head->m_data;
    }
    const reference_type get_item_at(const int& index) const {
        assert(index < m_size);
        node_ptr node = m_head;

        int curr_index = 0;
        while(curr_index < index) {
            node = node->m_next;
            curr_index++;
        }
        return node->m_data;
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

        // free(node); // freeing up tail

        m_head = nullptr;
        m_tail = nullptr;
    }

    /**
     * @todo Write Linked list iterator and implement begin and end functions.
     * 
     */

private:
    node_ptr m_head;
    node_ptr m_tail;
    int m_size;
};

}
