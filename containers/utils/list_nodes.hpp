#pragma once

namespace pixel {
    
template<typename T>
class Pixel_DLL_Node {
    using value_type = T;
    using reference_type = T&;
    using ptr_type = T*;

    using node_type = Pixel_DLL_Node<T>;
    using node_ptr = Pixel_DLL_Node<T>*;
    using node_reference = Pixel_DLL_Node<T>&;

// data
public:
    value_type m_data;
    node_ptr prev;
    node_ptr next;
};

template<typename T>
class Pixel_LL_Node {
    using value_type = T;
    using reference_type = T&;
    using ptr_type = T*;

    using node_type = Pixel_LL_Node<T>;
    using node_ptr = Pixel_LL_Node<T>*;
    using node_reference = Pixel_LL_Node<T>&;
public:
    Pixel_LL_Node()
    {
    }

    ~Pixel_LL_Node()
    {
    }

public:
    // data
    value_type m_data;
    node_ptr m_next;
};




}