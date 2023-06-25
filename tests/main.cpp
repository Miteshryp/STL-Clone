#include <iostream>
#include <vector>
#include <list>

// #include"containers/memory/node_store.hpp"

// #include "containers/vector.hpp"
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
    }

    B(int&& k) {
        this->k = k;
    }

    ~B() {
        std::cout << k << " destroyed\n";

    }

    void sample() {
        std::cout << "Called " << k << std::endl;
    }

    bool operator == (B const& b) {
        return b.k == k;
    }
};

int main() {
    pixel::list<B> new_list = { B(1), B(2), B(3) };
    std::cout << "\n\n";

    auto a = new_list.back();
    new_list.pop_back();

    std::cout << "Stop 1\n";

    auto b = new_list.front();
    new_list.pop_front();

    std::cout << "Stop 2\n";

    // not working 
    int k = new_list.find(B(3));
    int l = new_list.find(B(7));

    std::cout << k << "\t" << l << std::endl;

    a.sample();
    b.sample();

    // std::vector<B> vec = { B(1), B(2) };
    
    // vec.pop_back();
    // std::cout << "Here\n";

    std::cout << "Stop 3\n";

}