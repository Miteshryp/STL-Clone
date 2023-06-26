#pragma once

#include "containers/list.hpp"
#include "containers/utils/types.hpp"

namespace pixel
{
using namespace pixel::types;


template<typename Value_Type>
class queue {

    private:
        using value_type = Value_Type;
        using ptr_type = Value_Type*;
        using reference_type = Value_Type&;
        using const_reference_type = Value_Type const&;
        
        using queue_type = queue<value_type>;
        using queue_ptr = queue<value_type>*;
        using queue_reference_type = queue<value_type>&;
        using const_queue_reference_type = queue<value_type>&;

    public:
        queue()
            :
            m_list()
        {}

        queue(const_queue_reference_type q)
            :
            m_list(q.m_list)
        {}

        queue(queue_type&& q)
            :
            m_list(q.m_list)
        {}

        ~queue()
        {
            m_list.clear();
        }



        void push(const_reference_type item) {
            m_list.push_back(item);
        }
        void push(value_type&& item) {
            m_list.push_back(item);
        }

        void pop() {
            m_list.pop_front();
        }



        const_reference_type front() const {
            return m_list.front();
        };

        const_reference_type back() const {
            return m_list.back();
        }



        uint32 capacity() const { 
            return m_list.capacity();
        }
        uint32 remaining_capacity() const {
            return m_list.remaining_capacity();
        }

        /**
         * @brief Returns the size of the queue
         * 
         */
        uint32 size() const {
            return m_list.size();
        }

        bool empty() const {
            return m_list.empty();
        }
    
    private:
        pixel::list<value_type> m_list;
};


}