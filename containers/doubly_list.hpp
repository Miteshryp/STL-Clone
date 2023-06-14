#pragma once

#include<cstdlib>
#include<assert.h>
#include<memory.h>

#include "containers/utils/list_nodes.hpp"
#include "containers/utils/iterator.hpp"

namespace pixel {


template<typename T>
class doubly_list {

    using value_type = T;
    using ptr_type = T*;
    using reference_type = T&;

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
        m_size(0)
    {
    }

    doubly_list(const list_reference_type list) 
    {
        // @TODO - copy linked list
    }

    doubly_list(list_type&& list)
    {
        m_head = list.m_head;
        m_tail = list.m_tail;
        m_size = list.m_size;

        list.m_head = nullptr;
        list.m_tail = nullptr;
        list.m_size = 0;
    }

//Getters
public:

    const reference_type front() const {
        assert(m_head != nullptr);
        return m_head->m_data;
    }

    const reference_type back() const {
        assert(m_tail != nullptr);
        return m_tail->m_data;
    }

    int size() const {
        return m_size;
    }

public:

    void add_to_tail(const reference_type element) {
        // @TODO - add element to the tail
    }

    void add_to_head(const reference_type element) {
        // @TODO - add element to the head
    }

    value_type remove_from_tail() {
        // @TODO - remove the tail node and return data
    }

    value_type remove_from_head() {
        // @TODO - remove the head node and return data
    }

    void delete_all_nodes() { 
        // @TODO - delete all nodes of the list
    }


// Access Methods

    const reference_type get_head_item() const {
        return m_head->m_data;
    }

    const reference_type get_tail_item() const {
        return m_tail->m_data;
    }

    const get_item_at(int index) const {
        // @TODO - return item at [index] of dll
    }

    int find(const reference_type element) const {
        // @TODO - find element from beginning
    }

    int find_end(const reference_type element) const {
        // @TODO - find element from ending
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
        // @TODO - shallow copy the linked list 
        //         and revoke pointers from list 
    }

private:
    node_ptr m_head;
    node_ptr m_tail;
    int m_size;

};


}