#pragma once
#include<cstdlib>

namespace pixel {


/**
 * @brief Parent class for all types of list node
 * This class acts as an interface which allows 
 * integration of the child node type with the 
 * node store class
 * 
 * @tparam T 
 */
class __Pixel_Node {
public:
    __Pixel_Node()
        :
        m_data(nullptr)
    {}

    __Pixel_Node(void* data)
        :
        m_data(data) 
    {}
    
    ~__Pixel_Node()
    {}


/**
 * Interface for child classes
 */
protected:
    virtual void* getNextPtr() const = 0;
    virtual void setNextPtr(void* ptr) = 0;

    virtual void destruct_data() = 0;


/**
 * Data members
 */
protected:
    void* m_data;
};

    









/**
 * @brief Node class describing the structure of 
 * a node in doubly linked list
 * 
 * @tparam T 
 */
template<typename Value_Type>
class Pixel_DLL_Node : public __Pixel_Node {
    using value_type = Value_Type;
    using ptr_type = Value_Type*;
    using reference_type = Value_Type&;
    using const_reference_type = Value_Type const&;

    using node_type = Pixel_DLL_Node<Value_Type>;
    using node_ptr = Pixel_DLL_Node<Value_Type>*;
    using node_reference = Pixel_DLL_Node<Value_Type>&;

public:
    Pixel_DLL_Node()
        :
        __Pixel_Node(calloc(1, sizeof(value_type))),
        m_prev(nullptr),
        m_next(nullptr)
    {}

    Pixel_DLL_Node(const_reference_type value, node_ptr prev = nullptr, node_ptr next = nullptr)
        :
        __Pixel_Node(calloc(1, sizeof(value_type))),
        m_prev(prev),
        m_next(next)
    {
        *((node_ptr)m_data) = value;
    }

    Pixel_DLL_Node(value_type&& value, node_ptr prev = nullptr, node_ptr next = nullptr)
        :
        __Pixel_Node(calloc(1, sizeof(value_type))),
        m_prev(prev),
        m_next(next)
    {
        *((node_ptr)m_data) = value;
    }
    

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

    void setDataValue(const_reference_type value) {
        *((ptr_type)m_data) = value;
    }
    void setDataValue(value_type&& value) {
        *((ptr_type)m_data) = value;
    }

    const_reference_type getDataValue() const {
        return *(ptr_type)m_data;
    }


    virtual void destruct_data() {
        ((ptr_type)m_data)->~value_type();
    }


// data
public:
    node_ptr m_prev;
    node_ptr m_next;
};







template<typename Value_Type>
class Pixel_LL_Node : public __Pixel_Node {

    using value_type = Value_Type;
    using reference_type = Value_Type&;
    using const_reference_type = Value_Type const&;
    using ptr_type = Value_Type*;

    using node_type = Pixel_LL_Node<Value_Type>;
    using node_ptr = Pixel_LL_Node<Value_Type>*;
    using node_reference = Pixel_LL_Node<Value_Type>&;

public:
    
    Pixel_LL_Node()
        :
        __Pixel_Node((ptr_type)calloc(1, sizeof(value_type))),
        m_next(nullptr)
    {}

    Pixel_LL_Node(const_reference_type value, node_ptr next = nullptr)
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

    const_reference_type getDataValue() const {
        return *((ptr_type)m_data);
    }

    void setDataValue(const_reference_type item) {
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

    virtual void destruct_data() {
        if(m_data != nullptr) {
            ((ptr_type)m_data)->~value_type();
        }
    }


public:
    // data
    node_ptr m_next;
};




}