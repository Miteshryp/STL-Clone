#pragma once
#include "./non-pointers-structures.hpp"


class PointerStructure {
    TestStructure* t;
public:
    PointerStructure() = delete;
    PointerStructure(int a, int b) {
        t = new TestStructure(a, b);
    }

    ~PointerStructure() {
        delete t;
    }

    void operator = (const PointerStructure& s) {
        *(this->t) = *(s.t);
    }
    void operator = (PointerStructure&& s) {
        this->t = s.t;
        s.t = nullptr;
    }


    int getA() const  { return t->getA(); }
    int getB() const  { return t->getB(); }

};