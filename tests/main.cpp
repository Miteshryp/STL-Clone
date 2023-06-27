#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>


#include "containers/list.hpp"
#include "containers/queue.hpp"
// #include "containers/vector.hpp"

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
    pixel::queue<B> q;

    B a(2);
    B b(4);
    B c(6);

    q.push(a);
    q.push(b);
    q.push(c);

    std::cout << "Original size: " << q.size() << std::endl;

    const B& front = q.front();
    const B& back = q.back();

    std::cout << "Front value: " << front.k << std::endl;
    std::cout << "Back value: " << back.k << std::endl;

    q.pop();

    std::cout << "New size: " << q.size() << "\tCapacity: " << q.capacity() << std::endl;

    const B& new_front = q.front();
    const B& new_back = q.back();

    std::cout << "New front value: " << new_front.k << std::endl;
    std::cout << "New back value: " << new_back.k << std::endl;

    std::cout << q.empty() << '\t' << q.remaining_capacity() << std::endl;  
    std::cout << "---END---\n   ";
}