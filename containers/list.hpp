#include<assert.h>
#include"iterator.hpp"

namespace pixel {

template<typename T>
class Pixel_LL_Node {
    using value_type = T;
    using reference_type = T&;
    using ptr_type = T*;

    // data
    value_type m_data;
    struct Pixel_LL_Node* m_next;
};


template<typename T>
class Pixel_DLL_Node {
    using value_type = T;
    using reference_type = T&;
    using ptr_type = T*;

    // data
    value_type m_data;
    struct Pixel_LL_Node* prev;
    struct Pixel_LL_Node* next;
};



template<typename T>
class LinkedList {
    using value_type = T;
    using reference_type = T&;
    using ptr_type = T*;

    using node_type = Pixel_LL_Node<value_type>;
    using node_ptr = node_type*;

    using iterator = BasicIterator<T>;

public:
    LinkedList()
        :
        m_head(nullptr),
        m_tail(nullptr),
        m_size(0)
    {}

    LinkedList(const LinkedList& linkedList) {
        m_head = calloc(sizeof(node_type));
        memcpy(m_head, linkedList.m_head);

        m_tail = m_head;
        m_size = linkedList.m_size;
    }

    LinkedList(LinkedList&& linkedList) {
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

    void add_to_tail(value_type item) {
        node_ptr new_node = calloc(sizeof(node_type));
        new_node->m_data = item;
        new_node->m_next = nullptr;

        m_tail->m_next = new_node;
        m_tail = new_node;
        m_size++;
    }

    void add_to_head(value_type item) {
        node_ptr new_node = calloc(sizeof(node_type));
        new_node->m_data = item;
        new_node->m_next = m_head;
        
        m_head = new_node;
        m_size++;
    }

    value_type remove_from_tail() {
        assert(m_head != nullptr && m_tail != nullptr);

        // Special case - single node
        if(m_head == m_tail) return this->delete_all_nodes();
        
        node_ptr new_tail = m_head;
        
        while(new_tail->next != m_tail) {
            new_tail = new_tail->next;
        }

        free(m_tail);
        m_tail = new_tail;
        m_size--;
    }

    value_type remove_from_head() {
        assert(m_head != nullptr && m_tail != nullptr);

        if(m_head == m_tail) return this->delete_all_nodes();

        node_ptr new_head = m_head->next;
        free(m_head);
        m_head = new_head;
        m_size--;
    }



// Getters

    const reference_type get_tail_item() const {
        assert(m_tail != nullptr);
        return m_tail != nullptr ? m_tail->data : NULL;
    }
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
    void delete_all_nodes() {
        node_ptr node = m_head;
        if(node == nullptr) return;

        while(node != m_tail) {
            free(node);
        }
        free(node); // freeing up tail

        m_head = nullptr;
        m_tail = nullptr;
    }


    // @TODO: Write Linked list iterator and implement begin and end functions.

private:
    node_ptr m_head;
    node_ptr m_tail;
    int m_size;
};


}
