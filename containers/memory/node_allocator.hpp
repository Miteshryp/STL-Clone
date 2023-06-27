#pragma once
#include "./list_nodes.hpp"
#include "containers/utils/types.hpp"

#include <cstdlib>
#include <type_traits>

namespace pixel
{

    using namespace pixel::types;

    template <typename T>
    class node_store
    {
        static_assert(std::is_base_of<pixel::__Pixel_Node, T>::value, "Type not a child class of __Pixel_Node");

        using node_value = T;
        using node_ptr = T *;

        using store_ptr = node_store<T> *;
        using store_value = node_store<T>;

    public:
        node_store()
            : m_head(nullptr),
              m_tail(nullptr),
              m_size(0)
        {
        }

        /**
         * @note We can't really copy over a node store, since we are storing the pointers
         * to the nodes in the store, hence copying the store with just head and tail will
         * cause the middle nodes to overlap.
         */

        /**
         * @brief Move Constructor
         * @param store Store to be taken over
         */
        node_store(node_store<T> &&store)
            : m_head(store.m_head),
              m_tail(store.m_tail),
              m_size(store.m_size)
        {
            store.m_head = nullptr;
            store.m_tail = nullptr;
            store.m_size = 0;
        }

        ~node_store()
        {
            this->flush_nodes();
        }

    public:
        bool push_node(node_ptr node_ptr)
        {

            // Store empty case
            if (m_head == nullptr && m_tail == nullptr)
            {
                m_head = m_tail = node_ptr;  // First entry into the node store
                m_head->setNextPtr(nullptr); // Prevent access into store from outside of node store
                m_size = 1;

                return true;
            }

            // Adding the node to the tail
            m_tail->setNextPtr(node_ptr);
            m_tail = node_ptr;
            m_size++;

            return true;
        }

        /**
         * @brief Returns a node pointer pointing to an
         * allocated memory block
         *
         * @return pointer to the node block
         */
        node_ptr pop_node()
        {

            // Empty store case
            if (m_head == nullptr && m_tail == nullptr)
            {
                node_ptr new_node = new node_value;
                new_node->setNextPtr(nullptr);
                return new_node;
            }

            // Single node left. Removing node and configuring the store to empty
            if (m_head == m_tail)
            {
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

        bool flush_nodes()
        {
            // Empty store. No flush performed
            if (m_head == nullptr && m_tail == nullptr)
                return false;

            // Deleting nodes
            node_ptr iter = m_head;
            while (iter != nullptr)
            {
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

        uint32 size() const
        {
            return m_size;
        }

    public:
        /**
         * @brief Move operator
         * @todo
         * @param store
         */
        void operator=(store_value &&store)
        {
        }

    private:
        node_ptr m_head;
        node_ptr m_tail;
        uint32 m_size;
    };

    template <typename Node_Type, typename Value_Type>
    class node_allocator
    {

        static_assert(std::is_base_of<pixel::__Pixel_Node, Node_Type>::value, "type is not a child of __Pixel_Node");

        using node_type = Node_Type;
        using node_ptr = Node_Type *;

        using value_type = Value_Type;
        using ptr_type = Value_Type *;
        using reference_type = Value_Type &;
        using const_reference_type = Value_Type const&;

    public:
        node_allocator()
            : m_store()
        {
        }

        ~node_allocator()
        {
            m_store.flush_nodes();
        }

    protected:
        /**
         * @brief For internal use. Inserts a spare node block to the tail of the store
         *
         * @param node node_ptr to the node block
         * @returns true if insertion was successful, false otherwise
         */
        virtual bool store_push(node_ptr node)
        {
            node->destruct_data();
            return m_store.push_node(node);
        }

        /**
         * @brief For internal use. Returns a pointer to a spare block in the store
         *
         * @param node
         * @return node_ptr
         */
        virtual node_ptr store_pop()
        {
            node_ptr t = m_store.pop_node();
            return t;
        }

        /**
         * @brief Deletes all spare node blocks saved in the store
         *
         * @return true on successful deallocation
         * @return false if no nodes were flushed
         */
        virtual bool store_flush()
        {
            return m_store.flush_nodes();
        }

        // List and node specific implementation (Coupled implementation required)
        virtual node_ptr create_front_node(const_reference_type value) = 0;
        virtual node_ptr create_front_node(value_type &&value) = 0;

        virtual node_ptr create_back_node(const_reference_type value) = 0;
        virtual node_ptr create_back_node(value_type &&value) = 0;

    protected:
        node_store<node_type> m_store;
    };

}