#pragma once

#include<cstdlib>
#include<assert.h>
#include<memory.h>

#include "containers/utils/iterator.hpp"
#include "containers/memory/list_nodes.hpp"
#include "containers/memory/node_store.hpp"

namespace pixel {

using namespace pixel::types;


template<typename T>
class doubly_list {

    using value_type = T;
    using ptr_type = T*;
    using reference_type = T&;
    using const_reference_type = T const&;

    using list_type = doubly_list<T>;
    using list_reference_type = doubly_list<T>&;
    using list_Rreference_type = doubly_list<T>&&;
    using list_ptr_type = doubly_list<T>*;

    using node_type = Pixel_DLL_Node<T>;
    using node_ptr = Pixel_DLL_Node<T>*;
    using node_reference = Pixel_DLL_Node<T>&;

public:
    doubly_list()
        :
        m_head(nullptr),
        m_tail(nullptr),
        m_size(0),
        m_store()
    {}

    doubly_list(const list_reference_type list)
    {
        // @TODO - copy linked list
    }

    doubly_list(list_type&& list)
        :
        m_head(list.m_head),
        m_tail(list.m_tail),
        m_size(list.m_size),
        m_store()
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

public:

    void push_back(const_reference_type element) {
        node_ptr new_node = this->create_back_node(element); // creating node to be added to tail
        
        m_tail->setNextPtr(new_node);
        m_tail = new_node;
    }

    void push_front(const_reference_type element) {
        node_ptr new_node = this->create_front_node(element);
        
        m_head->setPrevPtr(new_node);
        m_head = new_node;
    }

    void pop_back() {
        node_ptr removed_node = m_tail;

        // Configuring new tail pointer
        m_tail = (node_ptr)(m_tail->getPrevPtr());
        m_tail->setNextPtr(nullptr);

        // Pushing removed node to store
        removed_node->setPrevPtr(nullptr);
        removed_node->setNextPtr(nullptr);
        m_store.push_node(removed_node);
    }

    void pop_front() {
        node_ptr removed_node = m_head;
        
        // Configuring new head pointer
        m_head = (node_ptr)(m_head->getNextPtr());
        m_head->setPrevPtr(nullptr);

        // Pushing removed node to store
        removed_node->setNextPtr(nullptr);
        removed_node->setPrevPtr(nullptr);
        m_store.push_node(removed_node);
    }

    void delete_all_nodes() { 
        // @TODO - delete all nodes of the list
    }


// Access Methods
    const reference_type front() const {
        assert(m_head != nullptr);
        return *(m_head->getDataPointer());
    }

    const reference_type back() const {
        assert(m_tail != nullptr);
        return *(m_tail->getDataPointer());
    }

    const reference_type at(uint32 index) const {
        // @TODO - return item at [index] of dll
    }

    int find(const reference_type element) const {
        // @TODO - find element from beginning
        node_ptr node = m_head;
        uint32 index = 0;

        while(node != nullptr) {
            if(node->getDataValue() == element) return index;
            index++;
            node = (node_ptr)(node->getNextPtr());
        }
    }

    int rfind(const reference_type element) const {
        // @TODO - find element from ending
        node_ptr node = m_tail;
        uint32 index = m_size - 1;

        while(node != nullptr) {
            if(node->getDataValue() == element) return index;
            index++;
            node = (node_ptr)(node->getPrevPtr());
        }

        return -1;
    }

    



    void clear() {
        if(m_head == nullptr) return;

        node_ptr node = m_head;

        while(node != nullptr) {
            node_ptr t = node;
            node = node->next;
            free(t);
        }

        m_head = nullptr;
        m_tail = nullptr;

        m_size = 0;
    }



// Operators
public:
    void operator = (const list_reference_type list) {
        // @TODO - copy the linked list
    }

    void operator = (list_type&& list) {
        m_head = list.m_head;
        m_tail = list.m_tail;
        m_size = list.m_size;

        list.m_head = list.m_tail = nullptr;
        list.m_size = nullptr;
    }

private:

// Internal use functions 


    node_ptr create_back_node(const reference_type item) {
        node_ptr new_node = m_store.pop_node();
        new_node->setNextPtr(nullptr);
        new_node->setPrevPtr(m_tail);

        return new_node;
    }
    node_ptr create_back_node(value_type&& item) {
        node_ptr new_node = m_store.pop_node();
        new_node->setNextPtr(nullptr);
        new_node->setPrevPtr(m_tail);

        return new_node;
    }


    node_ptr create_front_node(const reference_type item) {
        node_ptr new_node = m_store.pop_node();
        new_node->setNextPtr(m_head);
        new_node->setPrevPtr(nullptr);

        return new_node;
    }
    node_ptr create_front_node(value_type&& item) {
        node_ptr new_node = m_store.pop_node();
        new_node->setNextPtr(m_head);
        new_node->setPrevPtr(nullptr);

        return new_node;
    }


private:
    node_ptr m_head;
    node_ptr m_tail;
    uint32 m_size;

    node_store<node_type> m_store;
};


}