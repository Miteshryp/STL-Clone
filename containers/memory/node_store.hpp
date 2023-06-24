#pragma once
#include "./list_nodes.hpp"
#include "containers/utils/types.hpp"

#include<cstdlib>


namespace pixel {



using namespace pixel::types;


template<typename T>
class node_store 
{
        static_assert(std::is_base_of<pixel::__Pixel_Node, T>::value, "Type not a child class of __Pixel_Node");

        using node_value = T;
        using node_ptr = T*;

        using store_ptr = node_store<T>*;
        using store_value = node_store<T>;
    public:

        node_store() 
            :
            m_head(nullptr),
            m_tail(nullptr),
            m_size(0)
        {}

        /**
         * @note We can't really copy over a node store, since we are storing the pointers
         * to the nodes in the store, hence copying the store with just head and tail will 
         * cause the middle nodes to overlap.
         */
            

        /**
         * @brief Move Constructor
         * @param store Store to be taken over
         */
        node_store(node_store<T>&& store) 
            :
            m_head(store.m_head),
            m_tail(store.m_tail),
            m_size(store.m_size)
        {
            store.m_head = nullptr;
            store.m_tail = nullptr;
            store.m_size = 0;
        }

        ~node_store() {
            this->flush_nodes();
        }


        void push_node(node_ptr node_ptr) {

            // Store empty case
            if(m_head == nullptr && m_tail == nullptr) {
                m_head = m_tail = node_ptr; // First entry into the node store
                m_head->setNextPtr(nullptr); // Prevent access into store from outside of node store
                m_size = 1;
                
                return;
            }

            // Adding the node to the tail
            m_tail->setNextPtr(node_ptr);
            m_tail = node_ptr;
            m_size++;
            
            return;


        }


        /**
         * @brief Returns a node pointer pointing to an
         * allocated memory block
         * 
         * @return pointer to the node block
         */
        node_ptr pop_node() {

            // Empty store case
            if(m_head == nullptr && m_tail == nullptr) {
                node_ptr new_node = new node_value;
                new_node->setNextPtr(nullptr);

                return new_node;
            }


            // Single node left. Removing node and configuring the store to empty
            if(m_head == m_tail) {
                node_ptr ret = m_head;
                ret->setNextPtr(nullptr); // Prevent access into store from outside of node store

                // Setting empty configurations
                m_head = nullptr;
                m_tail = nullptr;
                m_size = 0;

                return ret;
            }


            // Returning node from store
            node_ptr ret = m_head;
            m_head = (node_ptr)m_head->getNextPtr();
            m_size--;

            ret->setNextPtr(nullptr);
            return ret;
        }

        bool flush_nodes() {
            // Empty store. No flush performed
            if(m_head == nullptr && m_tail == nullptr) return false;


            // Deleting nodes
            node_ptr iter = m_head;
            while(iter != nullptr) {
                node_ptr next = (node_ptr)iter->getNextPtr();
                delete iter;
                // free(iter);
                iter = next;
            }

            // Setting empty configurations
            m_head = m_tail = nullptr;
            m_size = 0;

            return true;
        }

        uint32 size() const {
            return m_size;
        }
    
    private:
        node_ptr m_head;
        node_ptr m_tail;
        uint32 m_size;

};



}