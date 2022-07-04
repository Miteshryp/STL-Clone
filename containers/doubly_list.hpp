#include<cstdlib>
#include<assert.h>
#include<memory.h>


namespace pixel {

template<typename T>
class Pixel_DLL_Node {
    using value_type = T;
    using reference_type = T&;
    using ptr_type = T*;

    using node_type = Pixel_DLL_Node<T>;
    using node_ptr = Pixel_DLL_Node<T>*;
    using node_reference = Pixel_DLL_Node<T>&;

// data
public:
    value_type m_data;
    struct node_ptr prev;
    struct node_ptr next;
};




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
    {
    }

    doubly_list(const list_reference_type list) 
    {

    }

    doubly_list(list_type&& list)
    {
    }

//Getters
public:
    int size() const {
        return m_size;
    }

    const reference_type front() const {
        assert(m_head != nullptr);
        return m_head->m_data;
    }

    const reference_type back() const {
        assert(m_tail != nullptr);
        return m_tail->m_data;
    }


public:

    void add_to_tail(value_type m_data) {
        
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
        
    }

    void operator = (list_type&& list) {

    }

private:
    node_ptr m_head;
    node_ptr m_tail;
    int m_size;

};


}