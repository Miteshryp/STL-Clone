#pragma once
#include "containers/memory/list_nodes.hpp"


namespace pixel {



template<typename T>
class LLNodeIterator  {

   using iterator = LLNodeIterator<T>;

   using value_type = T;
   using ptr_type = T*;
   using reference_type = T&;

   using node_type = pixel::Pixel_LL_Node<T>;
   using node_ptr = pixel::Pixel_LL_Node<T>*;

public:

   LLNodeIterator() = delete;

   LLNodeIterator(node_ptr node)
      :
      m_node(node)
   {}

   LLNodeIterator(const iterator& iter)
      :
      m_node(iter.node) 
   {}

   LLNodeIterator(iterator&& iter)
      :
      m_node(iter.node)
   {}

   reference_type operator * () {
      return m_node != nullptr ? *(m_node->m_data) : NULL;
   }

   bool operator == (const iterator& iter) const {
      return m_node == iter.m_node;
   }

   bool operator != (const iterator& iter) const {
      return !((*this) == iter);
   }

   iterator operator ++ () {
      m_node = m_node->m_next;
      return *this;
   }

   iterator operator ++ (int) {
      node_ptr temp = m_node;
      m_node = m_node->m_next;

      return iterator(temp);
   }

   void operator -- () = delete;


private: 
   node_ptr m_node;
};





}