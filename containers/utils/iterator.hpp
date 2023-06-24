#pragma once

#include "containers/memory/list_nodes.hpp"


namespace pixel {


/**
 * @brief Iterator for contiguous memory block
 * 
 * @tparam T value type
 */
template<typename T>
class BasicIterator {
   using iterator = pixel::BasicIterator<T>;

   using ptr_type = T*;
   using value_type = T;
   using reference_type = T&;


public:

   BasicIterator()
      :
      m_data(nullptr)
   {}

   BasicIterator(ptr_type ptr)
      :
      m_data(ptr)
   {}

   BasicIterator(const iterator& iterator)
      :
      m_data(iterator.m_data)
   {}

   BasicIterator(iterator&& iterator)
   {
      m_data = iterator.m_data;
   }

   ~BasicIterator()
   {
      m_data = nullptr;
   }





   reference_type operator *() const {
      return *(m_data);
   }

   iterator operator ++ () {
      m_data++;
      return *this;
   }

   iterator operator ++ (int) {
      iterator tmp = *this;
      m_data++;
      return tmp;
   }

   iterator operator -- () {
      m_data--;
      return *this;
   }

   iterator operator -- (int) {
      iterator tmp = *this;
      m_data--;
      return tmp;
   }

   void operator = (const iterator& iterator) {
      m_data = iterator.m_data;
   }


   // friend bool operator != (const iterator& i1, const iterator& i2) {
   //    return i1.m_ptr != i2.m_ptr;
   // }
   
   // friend bool operator == (const iterator& i1, const iterator& i2) {
   //    return i1.m_ptr == i2.m_ptr;
   // }

   bool operator == (const iterator& iter) const {
      return m_data == iter.m_data;
   }

   bool operator != (const iterator& iter) const {
      return ((*this) == iter);
   }

protected:
   ptr_type m_data;
};






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

   void operator --() = delete;


private: 
   // value_type m_data;
   node_ptr m_node;
};






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


   bool operator == (const iterator& iter) const {
      return m_node == iter.m_node;
   }
   bool operator != (const iterator& iter) const {
      return ((*this) == iter);
   }

   reference_type operator * () {
      return *(m_node->m_data);
   }

   void operator ++ (){
      m_node = m_node->next();
   }
   void operator -- (){
      m_node = m_node->prev();
   }

private:
   node_ptr m_node;
};



}