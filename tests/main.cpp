#include <iostream>
#include <vector>
#include <list>

#include"containers/memory/node_store.hpp"

#include "containers/vector.hpp"
#include "containers/list.hpp"

// #include "containers/vector.hpp"
// #include "./types/non-pointers-structures.hpp"

class A {
public:
    A() {}

    virtual void sample() = 0;
};

class B : public A {
public:
int k;

    B() = delete;// {}
    B(const int& k) {
        this->k = k;
        std::cout << "Deletion element pushed\n";
    }

    B(int&& k) {
        this->k = k;
        std::cout << "Rvalue element pushed\n";
    }

    void sample() {
        std::cout << "Called " << k << std::endl;
    }

    bool operator == (const B& b) {
        std::cout << b.k << std::endl;
        return b.k == k;
    }
};

int main() {
    pixel::list<B> new_list;


    new_list.push_back(B(1));
    new_list.push_back(B(2));
    new_list.push_back(B(3));
    new_list.push_back(B(6));
    

    auto a = new_list.back();
    new_list.pop_back();

    auto b = new_list.front();
    new_list.pop_front();


    // not working 
    int k = new_list.find(B(3));
    int l = new_list.find(B(7));

    std::cout << k << "\t" << l << std::endl;

    a.sample();
    b.sample();

}