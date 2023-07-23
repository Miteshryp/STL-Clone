#pragma once 


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

   bool operator == (const iterator& iter) const {
      return m_data == iter.m_data;
   }

   bool operator != (const iterator& iter) const {
      return ((*this) == iter);
   }

protected:
   ptr_type m_data;
};





}