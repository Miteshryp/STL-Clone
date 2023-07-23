#pragma once

#include "containers/memory/list_nodes.hpp"

namespace pixel {





template<typename T>
class DLLNodeIterator {

   using iterator = pixel::DLLNodeIterator<T>;

   using value_type = T;
   using ptr_type = T*;
   using reference_type = T&;

   using node_type = pixel::Pixel_DLL_Node<T>;
   using node_ptr = pixel::Pixel_DLL_Node<T>*;

public:

   DLLNodeIterator() = delete;

   DLLNodeIterator(const iterator& iter)
      :
      m_node(iter.m_node)
   {}

   ~DLLNodeIterator()
   {}

   void operator = (const iterator& iter) {
      m_node = iter.m_node;
   }

   void operator = (iterator&& iter) {
      m_node = iter.m_node;
      iter.m_node = nullptr;
   }

   bool operator == (const iterator& iter) const {
      return m_node == iter.m_node;
   }
   bool operator != (const iterator& iter) const {
      return ((*this) == iter);
   }

   reference_type operator * () {
      return *(m_node->getDataPointer());
   }




   iterator operator ++ (){
      m_node = (node_ptr)(m_node->getNextPtr());
   }

   iterator operator ++ (int) {
      iterator iter(m_node);
      m_node = (node_ptr)(m_node->getNextPtr());
      return iter;
   }

   iterator operator -- (){
      m_node = (node_ptr)(m_node->getPrevPtr());
      return *this;
   }

   iterator operator -- (int) {
      iterator iter(*this);
      m_node = (node_ptr)(m_node->getNextPtr());
      return iter;
   }

private:
   node_ptr m_node;
};



}