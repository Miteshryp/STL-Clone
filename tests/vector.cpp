// #include "../containers/vector.hpp"
#include<list>
#include<iostream>
#include"containers/reallocater.hpp"

class A {
    int a, b;
    public:

    A() {
        std::cout << "Default\n";
    }
    A(int a, int b){ 
        std::cout << "WEELL";
        this->a = a;
        this->b = b;
    }

    ~A(){
        std::cout << "Deleted\n";
    }
};

// Points
/**
 * We cannot delete a pointer from in between an allocation done by new[]
 * 
 * @return int 
 */


int main() {
    {
        // A* a = (A*)::operator new[] (sizeof(A) * 4);
    }
    return 0;
}