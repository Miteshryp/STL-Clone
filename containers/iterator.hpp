namespace pixel {


template<typename T>
class BasicIterator {
   using ptr_type = T*;
   using value_type = T;
   using reference_type = T&;


public:

   BasicIterator()
      :
      m_ptr(nullptr)
   {}

   BasicIterator(ptr_type ptr)
      :
      m_ptr(ptr)
   {}

   BasicIterator(const BasicIterator& iterator)
      :
      m_ptr(iterator.m_ptr)
   {}

   BasicIterator(BasicIterator&& iterator)
   {
      m_ptr = iterator.m_ptr;
   }

   ~BasicIterator()
   {
      m_ptr = nullptr;
   }





   reference_type operator *() const {
      return *(m_ptr);
   }

   BasicIterator operator ++ () {
      m_ptr++;
      return *this;
   }

   BasicIterator operator ++ (int) {
      BasicIterator tmp = *this;
      m_ptr++;
      return tmp;
   }

   BasicIterator operator -- () {
      m_ptr--;
      return *this;
   }

   BasicIterator operator -- (int) {
      BasicIterator tmp = *this;
      m_ptr--;
      return tmp;
   }

   void operator = (const BasicIterator& iterator) {
      m_ptr = iterator.m_ptr;
   }


   friend bool operator != (const BasicIterator& i1, const BasicIterator& i2) const {
      return i1.m_ptr != i2.m_ptr;
   }
   
   friend bool operator == (const BasicIterator& i1, const BasicIterator& i2) const {
      return i1.m_ptr == i2.m_ptr;
   }

protected:
   ptr_type m_ptr;
};

// To be implemented later.
// template<typename T>
// class Iterator {
//    using ptr_type = T*;

// public:
//    Iterator(){

//    }

//    T& operator *() const {
//       return *(element);
//    }

// private:
//    ptr_type element;
// };





template<typename T>
class LLNodeIterator  {
   using value_type = T;
   using ptr_type = T*;
   using reference_type = T&;

public:

   LLNodeIterator()
   {}
private: 
   value_type m_data;
};


};