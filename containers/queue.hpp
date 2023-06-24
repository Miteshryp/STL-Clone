#pragma once

#include "containers/list.hpp"
#include "containers/utils/types.hpp"

namespace pixel
{
using namespace pixel::types;



template<typename T>
class queue {

    private:
        using value_type = T;
        using ptr_type = T*;
        using reference_type = T&;
        
        using queue_type = queue<value_type>;
        using queue_ptr = queue<value_type>*;

    public:
        queue();
        ~queue();

        void push(const reference_type item) {
            m_list.push_back(item);
        }
        void push(value_type&& item) {
            m_list.push_back(item);
        }

        void pop() {
            m_list.pop_front();
        }

        const reference_type front() const {
            return m_list.front();
        };

        bool capacity() const { 
            return m_list.capacity();
        }
        bool remaining_capacity() const {
            return m_list.remaining_capacity();
        }
        bool size() const {
            return m_list.size();
        }
    
    private:
        pixel::list<T> m_list;
};


}