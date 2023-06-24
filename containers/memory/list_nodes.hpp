#pragma once

namespace pixel {


/**
 * @brief Wrapper class for nodes
 * 
 */
class __Pixel_Node {
public:
    // __Pixel_Node() = delete;
    __Pixel_Node()
    {}

    __Pixel_Node(void* data)
        :
        m_data(data) 
    {}
    
    ~__Pixel_Node()
    {}

protected:
    void* m_data;

    virtual void* getNextPtr() const = 0;
    virtual void setNextPtr(void* ptr) = 0;
};

    
template<typename T>
class Pixel_DLL_Node : public __Pixel_Node {
    using value_type = T;
    using reference_type = T&;
    using ptr_type = T*;

    using node_type = Pixel_DLL_Node<T>;
    using node_ptr = Pixel_DLL_Node<T>*;
    using node_reference = Pixel_DLL_Node<T>&;
    

public:
    void* getNextPtr() const {
        return (void*)m_next;
    }

    void setNextPtr(void* next_ptr) {
        m_next = next_ptr;
    }


    void* getPrevPtr() const {
        return (void*)m_prev;
    }

    void setPrevPtr(void* prev)  {
        m_prev = prev;
    }


    ptr_type getDataPointer() const {
        return (ptr_type)m_data;
    }


// data
public:
    node_ptr m_prev;
    node_ptr m_next;
};







template<typename T>
class Pixel_LL_Node : public __Pixel_Node {

    using value_type = T;
    using reference_type = T&;
    using ptr_type = T*;

    using node_type = Pixel_LL_Node<T>;
    using node_ptr = Pixel_LL_Node<T>*;
    using node_reference = Pixel_LL_Node<T>&;

public:
    
    Pixel_LL_Node()
        :
        __Pixel_Node((ptr_type)calloc(1, sizeof(value_type))),
        m_next(nullptr)
    {}

    Pixel_LL_Node(const value_type& value, node_ptr next = nullptr)
        :
        __Pixel_Node((ptr_type)calloc(1, sizeof(value_type))),
        m_next(next)
    {
        *((ptr_type)m_data) = value;
    }

    ~Pixel_LL_Node()
    {
        if(m_data != nullptr) 
            free(m_data);
    }


    ptr_type getDataPointer() const {
        return (ptr_type)m_data;
    }

    const reference_type getDataValue() const {
        return *((ptr_type)m_data);
    }

    void setDataValue(const reference_type item) {
        *(ptr_type(m_data)) = item;
    }
    void setDataValue(value_type&& item) {
        *(ptr_type(m_data)) = item;
    }



    virtual void* getNextPtr() const {
        return (void*)m_next;
    }

    virtual void setNextPtr(void* next_ptr) {
        m_next = (node_ptr)next_ptr;
    }


public:
    // data
    node_ptr m_next;
};




}